#pragma once

#include <set>

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
      auto & crappy_hack = const_cast<Callback &>(callback);
      crappy_hack.m_Container->Unlink();
    }
  }

  virtual void Update()
  {
    auto itr = m_PendingCallbacks.begin();
    while(itr != m_PendingCallbacks.end())
    {
      if (CompleteCallback(itr->m_CallbackData, itr->m_Callback))
      {
        auto dead_itr = itr;
        itr++;
        m_PendingCallbacks.erase(dead_itr);
      }
      else
      {
        itr++;
      }
    }
  }

  void CreateCallback(CreationData creation_data, DDSDeferredCallback & callback, std::function<void(Args...)> && function)
  {
    callback.m_Id = m_NextId;
    callback.m_System = this;

    m_PendingCallbacks.emplace(Callback{ m_NextId, GetCallbackData(creation_data), &callback, std::move(function) });
  }

  bool AreAllCallbacksComplete()
  {
    return m_PendingCallbacks.size() == 0;
  }

protected:

  void MoveCallback(uint32_t id, DDSDeferredCallback * deferred)
  {
    for (auto & callback : m_PendingCallbacks)
    {
      if (callback.m_Id == id)
      {
        auto & crappy_hack = const_cast<Callback &>(callback);
        crappy_hack.m_Container = deferred;
        return;
      }
    }
  }

  void DestroyCallback(uint32_t id)
  {
    for (auto itr = m_PendingCallbacks.begin(); itr != m_PendingCallbacks.end(); itr++)
    {
      if (itr->m_Id == id)
      {
        m_PendingCallbacks.erase(itr);
        return;
      }
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

    bool operator < (const Callback & rhs) const
    {
      return m_CallbackData < rhs.m_CallbackData;
    }
  };

  std::set<Callback> m_PendingCallbacks;
  uint32_t m_NextId = 0;
};

