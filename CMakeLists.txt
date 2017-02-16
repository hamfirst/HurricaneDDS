
cmake_minimum_required(VERSION 3.5)

include_directories(.. ../External)
add_definitions(-DUSE_MBED -D_LINUX)

set(CMAKE_CXX_STANDARD 14)


add_library(HurricaneDDS STATIC
            DDSConnectionInterface.cpp
            DDSCoordinatorClientProtocol.cpp
            DDSCoordinatorNetworkService.cpp
            DDSCoordinatorServerProtocol.cpp
            DDSCoordinatorState.cpp
            DDSCPUUsage.cpp
            DDSDatabaseBootstrap.cpp
            DDSDatabaseConnection.cpp
            DDSDatabaseConnectionPool.cpp
            DDSDatabaseSetup.cpp
            DDSDeferredCallback.cpp
            DDSEndpointFactoryBase.cpp
            DDSEndpointInterface.cpp
            DDSHttpClient.cpp
            DDSHttpRequest.cpp
            DDSIncomingKeyspaceTransfer.cpp
            DDSIncomingKeyspaceTransferManager.cpp
            DDSKey.cpp
            DDSLoadBalancer.cpp
            DDSLoadBalancerNetworkService.cpp
            DDSLog.cpp
            DDSNetworkBackend.cpp
            DDSNodeInterface.cpp
            DDSNodeNetworkService.cpp
            DDSNodeSharedObjectResolver.cpp
            DDSNodeState.cpp
            DDSOutgoingKeyspaceTransfer.cpp
            DDSOutgoingKeyspaceTransferManager.cpp
            DDSRandom.cpp
            DDSResolver.cpp
            DDSResolverBackend.cpp
            DDSResponder.cpp
            DDSRoutingTable.cpp
            DDSServerToServerReceiver.cpp
            DDSServerToServerSender.cpp
            DDSSharedObjectInterface.cpp
            DDSShutdown.cpp
            DDSTimerSystem.cpp
            DDSThrottle.refl.cpp
            DDSTokenBroker.cpp
            DDSTokenValidator.cpp
            DDSVersion.cpp
            DDSWebsiteFactoryBase.cpp
            DDSWebsiteFactoryStaticContent.cpp
            DDSWebsiteFilesystem.cpp
            DDSWebsiteFilesystemBuilder.cpp
            DDSWebsiteInterface.cpp)


