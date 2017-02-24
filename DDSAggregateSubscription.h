#pragma once

#include <string>
#include <vector>

#include "DDSNodeId.h"
#include "DDSDataObjectAddress.h"
#include "DDSServerToServerMessages.refl.h"

class DDSNodeState;

struct ReflectionChangeNotification;

class DDSAggregateSubscription 
{
public:
  DDSAggregateSubscription(DDSNodeState & node_state, const std::string & data_path, DDSKey shared_local_object_key, 
    bool data_subscription, void * object, bool (*GetDataAtPath)(void * obj, const char * path, std::string & data));

  DDSAggregateSubscription(DDSNodeState & node_state, DDSExportedAggregateSubscription & msg,
    void * object, bool(*GetDataAtPath)(void * obj, const char * path, std::string & data));

  DDSAggregateSubscription(const DDSAggregateSubscription & rhs) = default;
  DDSAggregateSubscription(DDSAggregateSubscription && rhs) = default;

  DDSAggregateSubscription & operator = (const DDSAggregateSubscription & rhs) = default;
  DDSAggregateSubscription & operator = (DDSAggregateSubscription && rhs) = default;

  void CreateSubscription(DDSNodeId node_id, DDSKey server_request_id, int data_gen);
  void DestroySubscription(DDSKey server_request_id);

  bool HasSubscriptions() const;
  bool IsDataSubscription() const;
  DDSKey GetSharedLocalCopyKey() const;
  const std::string & GetDataPath() const;

  void HandleChangePacket(const ReflectionChangeNotification & change_notification);
  void HandleAck(DDSNodeId node_id, DDSKey server_request_id, int data_gen, int routing_table_gen);
  void HandleObjectDestroyed();

  void GotAllClear(int table_gen);
  void ClearExpiredChanges();

  void Export(DDSExportedAggregateSubscription & msg);
  void Import(DDSExportedAggregateSubscription & msg);


private:

  DDSNodeState * m_NodeState;

  void * m_Object;
  bool(*m_GetDataAtPath)(void * obj, const char * path, std::string & data);

  DDSKey m_SharedLocalCopyKey;
  std::string m_DataPath;

  std::vector<DDSExportedAggregateSubscriptionChange> m_Changes;
  std::vector<std::pair<DDSNodeId, DDSKey>> m_SubscribedNodes;

  int m_DataGen;
  bool m_HasChangesWaiting = false;
  bool m_DataSubcription = false;
  bool m_Active = false;
};
