#pragma once

#include <memory>

#include "DDSResolverRequest.h"
#include "DDSDeferredCallbackSystem.h"

class DDSResolverBackend;

class DDSResolver : public DDSDeferredCallbackSystem<std::pair<const char *, bool>, std::unique_ptr<DDSResolverRequest>, const DDSResolverRequest &>
{
public:
  DDSResolver();
  ~DDSResolver();

  void Update() override;

protected:
  bool CompleteCallback(const std::unique_ptr<DDSResolverRequest> & callback_data, const std::function<void(const DDSResolverRequest &)> & callback) override;
  std::unique_ptr<DDSResolverRequest> GetCallbackData(std::pair<const char *, bool> creation_data) override;

private:
  std::unique_ptr<DDSResolverBackend> m_Backend;
};
