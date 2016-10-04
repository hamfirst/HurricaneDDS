
#include "DDSNodeInterface.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>

DDSNodeInterface::DDSNodeInterface(DDSNodeState & node_state, DDSKey key) :
  m_NodeState(node_state), m_Key(key)
{

}

int DDSNodeInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDataObjectTypeIdForNameHash(object_type_name_hash);
}

void DDSNodeInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  DDSTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToObjectWithResponder(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message)
{
  DDSTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg, std::string && message)
{
  DDSTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ReturnArg = return_arg;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, StormReflEncodeJson(packet));
}

