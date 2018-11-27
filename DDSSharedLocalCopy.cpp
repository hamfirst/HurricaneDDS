
#include "DDSSharedLocalCopy.h"
#include "DDSRandom.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"

#include "DDSServerToServerMessages.refl.meta.h"


DDSSharedLocalCopy::DDSSharedLocalCopy(
  DDSNodeState & node_state, DDSDataObjectAddress target_addr, const std::string & data_path,
  DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData> && data_obj, int data_gen, bool data_subscription) :
  m_NodeState(node_state),
  m_TargetAddr(target_addr),
  m_DataPath(data_path),
  m_SharedLocalCopyKey(shared_local_copy_key),
  m_ServerRequestId(DDSGetRandomNumber64()),
  m_DataGen(data_gen),
  m_DataSub(data_subscription),
  m_Data(std::move(data_obj))
{
  DDSCreateSharedLocalCopySubscription msg;
  msg.m_Key = target_addr.m_ObjectKey;
  msg.m_ObjectType = target_addr.m_ObjectType;
  msg.m_SharedLocalCopyKey = shared_local_copy_key;
  msg.m_SubscriptionId = m_ServerRequestId;
  msg.m_DataPath = data_path;
  msg.m_DataGen = data_gen;
  msg.m_ReturnNode = m_NodeState.m_LocalNodeId.value();
  msg.m_DataSubscription = data_subscription;

  m_NodeState.SendTargetedMessage(target_addr, DDSServerToServerMessageType::kCreateSharedLocalCopySubscription, StormReflEncodeJson(msg));

  if (data_gen == 0)
  {
    m_State = kRequesting;
  }
  else
  {
    m_State = kPendingFastForward;
  }
}

void DDSSharedLocalCopy::TerminateLocalCopy()
{
  DDSDestroySharedLocalCopySubscription msg;
  msg.m_Key = m_TargetAddr.m_ObjectKey;
  msg.m_ObjectType = m_TargetAddr.m_ObjectType;
  msg.m_SubscriptionId = m_ServerRequestId;
  msg.m_SharedLocalCopyKey = m_SharedLocalCopyKey;

  m_NodeState.SendTargetedMessage(m_TargetAddr, DDSServerToServerMessageType::kDestroySharedLocalCopySubscription, StormReflEncodeJson(msg));
}

DDSKey DDSSharedLocalCopy::GetServerRequestId() const
{
  return m_ServerRequestId;
}

void DDSSharedLocalCopy::CreateSubscription(DDSKey subscription_id, 
  DDSDataObjectAddress return_addr, int return_method, int error_method, const std::string & responder_args, int data_gen, bool data_valid)
{
  SubscriptionData sub_data;
  sub_data.m_ReturnAddr = return_addr;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ReturnMethodId = return_method;
  sub_data.m_ErrorMethodId = error_method;
  sub_data.m_ResponderArgs = responder_args;

  if (m_State == kLoaded)
  {
    if (m_DataValid == false)
    {
      if (data_valid)
      {
        auto packet = GetErrorResponse(sub_data);
        m_NodeState.SendTargetedMessage(return_addr, DDSServerToServerMessageType::kResponderCall, std::move(packet));
      }
    }
    else if (data_gen < m_DataGen || data_valid == false)
    {
      sub_data.m_DataGen = m_DataGen;
      std::string packet = GetInitialSubscriptionResponse(sub_data);

      m_NodeState.SendTargetedMessage(return_addr, DDSServerToServerMessageType::kResponderCall, std::move(packet));
    }
    else
    {
      // Ahead of the game
      sub_data.m_DataGen = data_gen;
    }
  }

  m_Subscriptions.emplace(std::make_pair(subscription_id, sub_data));
}

void DDSSharedLocalCopy::DestroySubscription(DDSKey subscription_id)
{
  m_Subscriptions.erase(subscription_id);
}

void DDSSharedLocalCopy::CreateDataVersion(int data_gen, std::string && data)
{
  m_Data->ParseFull(data_gen, data.c_str());
}

bool DDSSharedLocalCopy::HasSubscriptions() const
{
  return m_Subscriptions.size() > 0;
}

bool DDSSharedLocalCopy::IsDataValid() const
{
  return m_DataValid;
}

int DDSSharedLocalCopy::GetLatestDataGeneration() const
{
  return m_DataGen;
}

const std::string & DDSSharedLocalCopy::GetDataPath() const
{
  return m_DataPath;
}

void DDSSharedLocalCopy::HandleInitialSync(const std::string & data, int data_gen)
{
  if (m_State == kLoaded || m_State == kPendingFastForward)
  {
    DDSLog::LogError("Invalid initial sync (wrong state - requesting)");
    return;
  }

  m_State = kLoaded;
  m_DataGen = data_gen;
  m_Data->ParseFull(data_gen, data.c_str());

  FinalizeLoad();
}

void DDSSharedLocalCopy::HandleChangePacket(const std::string & change, int data_gen)
{
  if (m_State == kRequesting || m_State == kPendingFastForward)
  {
    DDSLog::LogError("Invalid change packet (not loaded yet)");
    return;
  }

  if (m_DataValid == false)
  {
    FinalizeLoad();
    return;
  }

  ReflectionChangeNotification change_notification;
  StormDataParseChangePacket(change_notification, change.data());

  m_Data->ApplyChangePacket(change_notification, data_gen);
  m_DataGen = data_gen;

  std::string enc_change = StormReflEncodeJson(StormReflEncodeJson(std::make_pair(change, m_DataGen)));

  for (auto & sub : m_Subscriptions)
  {
    auto & data = sub.second;

    if (sub.second.m_DataGen == data_gen - 1)
    {
      sub.second.m_DataGen = data_gen;

      std::string packet;
      packet.reserve(200);

      packet += "{\"m_Key\":\"";
      packet += std::to_string(data.m_ReturnAddr.m_ObjectKey);
      packet += "\",\"m_ObjectType\":";
      packet += std::to_string(data.m_ReturnAddr.m_ObjectType);
      packet += ",\"m_MethodId\":";
      packet += std::to_string(data.m_ReturnMethodId);
      packet += ",\"m_ResponderArgs\":";
      packet += data.m_ResponderArgs;
      packet += ",\"m_MethodArgs\":";
      packet += enc_change;
      packet += '}';

      m_NodeState.SendTargetedMessage(data.m_ReturnAddr, DDSServerToServerMessageType::kResponderCall, std::move(packet));
    }
  }

  DDSSharedLocalCopyAck resp;
  resp.m_Key = m_TargetAddr.m_ObjectKey;
  resp.m_ObjectType = m_TargetAddr.m_ObjectType;
  resp.m_SharedLocalCopy = m_SharedLocalCopyKey;
  resp.m_SubscriptionId = m_ServerRequestId;
  resp.m_NodeId = m_NodeState.m_LocalNodeId.value();
  resp.m_DataGen = data_gen;
  resp.m_RoutingTableGen = m_NodeState.m_RoutingTable->m_TableGeneration;

  m_NodeState.SendTargetedMessage(m_TargetAddr, DDSServerToServerMessageType::kSharedLocalCopyAck, StormReflEncodeJson(resp));
}

void DDSSharedLocalCopy::HandleErrorPacket()
{
  for (auto & sub : m_Subscriptions)
  {
    auto & data = sub.second;
    auto packet = GetErrorResponse(data);

    m_NodeState.SendTargetedMessage(data.m_ReturnAddr, DDSServerToServerMessageType::kResponderCall, std::move(packet));
  }

  m_DataValid = false;
  m_State = kLoaded;
}

void DDSSharedLocalCopy::HandleFastForward(const DDSSharedLocalCopyFastForward & msg)
{
  if (m_State == kLoaded || m_State == kRequesting)
  {
    DDSLog::LogError("Invalid initial sync (wrong state - requesting)");
    return;
  }

  m_State = kLoaded;

  for (auto & change : msg.m_Changes)
  {
    HandleChangePacket(change.second, change.first);
  }
}

void DDSSharedLocalCopy::AddRef(int version)
{
  m_Data->AddRef(version);
}

void DDSSharedLocalCopy::DecRef(int version)
{
  m_Data->DecRef(version);
}

void DDSSharedLocalCopy::Export(DDSSharedLocalCopyDatabaseElem & elem)
{
  elem.m_DataGen = m_DataGen;
  m_Data->AppendFullJsonData(m_DataGen, elem.m_Data);
  elem.m_DataSub = m_DataSub;
  elem.m_DataValid = m_DataValid;

  elem.m_Key = m_TargetAddr.m_ObjectKey;
  elem.m_ObjectType = m_TargetAddr.m_ObjectType;
  elem.m_Path = m_DataPath;
}

void * DDSSharedLocalCopy::GetVersion(int version)
{
  return m_Data->GetVersion(version);
}

void DDSSharedLocalCopy::FinalizeLoad()
{
  std::string change_packet = "kSet  ";
  m_Data->AppendFullJsonData(m_DataGen, change_packet);

  std::string enc_change = StormReflEncodeJson(StormReflEncodeJson(std::make_pair(change_packet, m_DataGen)));

  for (auto & sub : m_Subscriptions)
  {
    auto & data = sub.second;
    data.m_DataGen = m_DataGen;

    std::string packet;
    packet.reserve(200);

    packet += "{\"m_Key\":\"";
    packet += std::to_string(data.m_ReturnAddr.m_ObjectKey);
    packet += "\",\"m_ObjectType\":";
    packet += std::to_string(data.m_ReturnAddr.m_ObjectType);
    packet += ",\"m_MethodId\":";
    packet += std::to_string(data.m_ReturnMethodId);
    packet += ",\"m_ResponderArgs\":";
    packet += data.m_ResponderArgs;
    packet += ",\"m_MethodArgs\":";
    packet += enc_change;
    packet += '}';

    m_NodeState.SendTargetedMessage(data.m_ReturnAddr, DDSServerToServerMessageType::kResponderCall, std::move(packet));
  }

  m_DataValid = true;
}


std::string DDSSharedLocalCopy::GetInitialSubscriptionResponse(const SubscriptionData & data)
{
  std::string packet;
  packet.reserve(200);

  std::string change_packet = "kSet  ";
  m_Data->AppendFullJsonData(m_DataGen, change_packet);

  std::string enc_change = StormReflEncodeJson(StormReflEncodeJson(std::make_pair(change_packet, m_DataGen)));

  packet += "{\"m_Key\":\"";
  packet += std::to_string(data.m_ReturnAddr.m_ObjectKey);
  packet += "\",\"m_ObjectType\":";
  packet += std::to_string(data.m_ReturnAddr.m_ObjectType);
  packet += ",\"m_MethodId\":";
  packet += std::to_string(data.m_ReturnMethodId);
  packet += ",\"m_ResponderArgs\":";
  packet += data.m_ResponderArgs;
  packet += ",\"m_MethodArgs\":";
  packet += enc_change;
  packet += '}';

  return packet;
}

std::string DDSSharedLocalCopy::GetErrorResponse(const SubscriptionData & data)
{
  std::string packet;
  packet.reserve(200);

  packet += "{\"m_Key\":\"";
  packet += std::to_string(data.m_ReturnAddr.m_ObjectKey);
  packet += "\",\"m_ObjectType\":";
  packet += std::to_string(data.m_ReturnAddr.m_ObjectType);
  packet += ",\"m_MethodId\":";
  packet += std::to_string(data.m_ReturnMethodId);
  packet += ",\"m_ResponderArgs\":";
  packet += data.m_ResponderArgs;
  packet += ",\"m_MethodArgs\":\"[]\"}";

  return packet;
}

std::string DDSSharedLocalCopy::MemoryReport()
{
  std::string report = "Subs: " + std::to_string(m_Subscriptions.size()) + " ";
  return report + m_Data->MemoryReport();
}