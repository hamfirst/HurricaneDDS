#pragma once

#include <map>

#include "DDSDeferredCallback.h"

class DDSDeferredCallbackSystemBase
{
public:
  virtual void MoveCallback(uint32_t id, DDSDeferredCallback * callback) = 0;
  virtual void DestroyCallback(uint32_t id) = 0;
};

template <typename CreationData, typename CallbackData, typename ... Args>
class DDSDeferredCallbackSystem : DDSDeferredCallbackSystemBase
{
public:
  ~DDSDeferredCallbackSystem()
  {
    for (auto & callback : m_PendingCallbacks)
    {
      callback.second.m_Container->Unlink();
    }
  }

  virtual void Update()
  {
    m_Iterating = true;
    for(auto & elem : m_PendingCallbacks)
    {
      if (elem.second.m_Destroyed == false && CompleteCallback(elem.second.m_CallbackData, elem.second.m_Callback))
      {
        elem.second.m_Destroyed = true;
      }
    }

    m_Iterating = false;

    auto itr = m_PendingCallbacks.begin();
    while (itr != m_PendingCallbacks.end())
    {
      if (itr->second.m_Destroyed)
      {
        auto dead_itr = itr;
        ++itr;

        m_PendingCallbacks.erase(dead_itr);
      }
      else
      {
        ++itr;
      }
    }
  }

  void CancelCallback(int callback_id)
  {
    auto itr = m_PendingCallbacks.begin();
    while (itr != m_PendingCallbacks.end())
    {
      if(itr->m_Id == callback_id)
      {
        m_PendingCallbacks.erase(itr);
        return;
      }
    }
  }

  const CallbackData & CreateCallback(CreationData creation_data, DDSDeferredCallback & callback, std::function<void(Args...)> && function)
  {
    callback.m_Id = m_NextId;
    callback.m_System = this;

    auto result = m_PendingCallbacks.emplace(std::make_pair(m_NextId, Callback{ m_NextId, GetCallbackData(creation_data), &callback, std::move(function), false }));
    m_NextId++;

    return result.first->second.m_CallbackData;
  }

  bool AreAllCallbacksComplete()
  {
    return m_PendingCallbacks.size() == 0;
  }

protected:

  void MoveCallback(uint32_t id, DDSDeferredCallback * deferred)
  {
    auto itr = m_PendingCallbacks.find(id);
    if (itr == m_PendingCallbacks.end())
    {
      return;
    }

    itr->second.m_Container = deferred;
  }

  void DestroyCallback(uint32_t id)
  {
    if (m_Iterating)
    {
      auto itr = m_PendingCallbacks.find(id);
      if (itr == m_PendingCallbacks.end())
      {
        return;
      }

      itr->second.m_Destroyed = true;
    }
    else
    {
      m_PendingCallbacks.erase(id);
    }
  }

  virtual bool CompleteCallback(const CallbackData & callback_data, const std::function<void(Args...)> & callback) = 0;
  virtual CallbackData GetCallbackData(CreationData creation_data) = 0;

protected:

  friend class DDSDeferredCallback;

  struct Callback
  {
    uint32_t m_Id;
    CallbackData m_CallbackData;
    DDSDeferredCallback * m_Container;
    std::function<void(Args...)> m_Callback;
    bool m_Destroyed;
  };

  std::map<uint32_t, Callback> m_PendingCallbacks;
  uint32_t m_NextId = 0;
  bool m_Iterating = false;
};

