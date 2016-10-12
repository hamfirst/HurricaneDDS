#pragma once

#include <functional>

class DDSDeferredCallbackSystemBase;

class DDSDeferredCallback
{
public:
  DDSDeferredCallback();
  DDSDeferredCallback(const DDSDeferredCallback & rhs) = delete;
  DDSDeferredCallback(DDSDeferredCallback && rhs);

  DDSDeferredCallback & operator = (const DDSDeferredCallback & rhs) = delete;
  DDSDeferredCallback & operator = (DDSDeferredCallback && rhs);

  ~DDSDeferredCallback();

  void Cancel();

private:

  template <typename CreationData, typename CallbackData, typename ... Args>
  friend class DDSDeferredCallbackSystem;

  void Unlink();

private:

  unsigned m_Id;
  DDSDeferredCallbackSystemBase * m_System;

};
