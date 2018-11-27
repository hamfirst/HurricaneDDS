#pragma once

#include <memory>
#include <unordered_map>

#include "DDSKey.h"
#include "DDSDataObjectAddress.h"
#include "DDSSharedLocalCopyData.h"
#include "DDSServerToServerMessages.refl.h"

class DDSNodeState;

class DDSSharedLocalCopy
{
public:

  DDSSharedLocalCopy(DDSNodeState & node_state, DDSDataObjectAddress target_addr, const std::string & data_path,
    DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData> && data_obj, int data_gen, bool data_subscription);

  void TerminateLocalCopy();

  DDSKey GetServerRequestId() const;

  void CreateSubscription(DDSKey subscription_id, DDSDataObjectAddress return_addr, int return_method, int error_method, 
    const std::string & responder_args, int data_gen, bool data_valid);
  void DestroySubscription(DDSKey subscription_id);

  void CreateDataVersion(int data_gen, std::string && data);

  bool HasSubscriptions() const;
  bool IsDataValid() const;
  int GetLatestDataGeneration() const;
  const std::string & GetDataPath() const;

  void HandleInitialSync(const std::string & change, int data_gen);
  void HandleChangePacket(const std::string & change, int data_gen);
  void HandleErrorPacket();
  void HandleFastForward(const DDSSharedLocalCopyFastForward & msg);

  void * GetVersion(int version);
  void AddRef(int version);
  void DecRef(int version);

  void Export(DDSSharedLocalCopyDatabaseElem & elem);

  void FinalizeLoad();

  std::string MemoryReport();

private:

  struct SubscriptionData
  {
    DDSDataObjectAddress m_ReturnAddr;
    int m_ReturnMethodId;
    int m_ErrorMethodId;
    std::string m_ResponderArgs;

    int m_DataGen;

    DDSKey m_SubscriptionId;
  };

  enum State
  {
    kRequesting,
    kPendingFastForward,
    kLoaded,
  };


  std::string GetInitialSubscriptionResponse(const SubscriptionData & data);
  std::string GetErrorResponse(const SubscriptionData & data);

private:

  State m_State;
  DDSNodeState & m_NodeState;

  DDSDataObjectAddress m_TargetAddr;
  std::string m_DataPath;

  DDSKey m_SharedLocalCopyKey;
  DDSKey m_ServerRequestId;

  int m_DataGen = 0;
  bool m_DataSub = false;
  bool m_DataValid = false;

  std::unique_ptr<DDSBaseSharedLocalCopyData> m_Data;
  std::unordered_map<DDSKey, SubscriptionData> m_Subscriptions;
};

