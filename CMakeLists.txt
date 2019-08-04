cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech)
set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_HurricaneDDS 
            DDSRandom.cpp
            DDSNodeNetworkService.cpp
            DDSOutgoingKeyspaceTransfer.cpp
            DDSResponder.cpp
            DDSCoordinatorServerProtocol.cpp
            DDSResolver.cpp
            DDSWebsiteFactoryStaticContent.cpp
            DDSCPUUsage.cpp
            DDSResolverBackend.cpp
            DDSCoordinatorState.cpp
            DDSNetworkBackend.cpp
            DDSShutdown.cpp
            DDSOutgoingKeyspaceTransferManager.cpp
            DDSKey.cpp
            DDSConnectionInterface.cpp
            DDSLoadBalancer.cpp
            DDSDatabaseBootstrap.cpp
            DDSTokenValidator.cpp
            DDSDatabaseSetup.cpp
            DDSServerToServerSender.cpp
            DDSDatabaseConnectionPool.cpp
            DDSVersion.cpp
            DDSTimerSystem.cpp
            DDSIncomingKeyspaceTransferManager.cpp
            DDSCoordinatorClientProtocol.cpp
            DDSWebsiteFilesystem.cpp
            DDSIncomingKeyspaceTransfer.cpp
            DDSLog.cpp
            DDSNodeState.cpp
            DDSWebsiteFilesystemBuilder.cpp
            DDSAggregateSubscription.cpp
            DDSSharedLocalCopyData.cpp
            DDSDatabaseConnection.cpp
            DDSRoutingTable.cpp
            DDSNodeInterface.cpp
            DDSThrottle.refl.cpp
            DDSWebsiteFactoryBase.cpp
            DDSEndpointInterface.cpp
            DDSSharedLocalCopyDatabase.cpp
            DDSLoadBalancerNetworkService.cpp
            DDSDeferredCallback.cpp
            DDSSharedLocalCopy.cpp
            DDSCoordinatorNetworkService.cpp
            DDSServerToServerReceiver.cpp
            DDSNodeSharedObjectResolver.cpp
            DDSWebsiteInterface.cpp
            DDSHttpClient.cpp
            DDSEndpointFactoryBase.cpp
            DDSSharedObjectInterface.cpp
            DDSTokenBroker.cpp
            DDSSharedLocalCopyPtr.cpp
            DDSHttpRequest.cpp
            DDSEncoding.cpp
            )

set(GENERIC_HEADER_HurricaneDDS 
            DDSCoordinatorProtocolMessages.refl.h
            DDSDataObjectStoreBase.h
            DDSCoordinatorProtocolMessages.refl.meta.h
            DDSServerToServerMessages.refl.h
            DDSThrottle.refl.h
            DDSWebsiteFilesystemBuilder.h
            DDSResolverBackend.h
            DDSSharedMessages.refl.meta.h
            DDSSharedMessages.refl.h
            DDSNodeInterface.h
            DDSSharedLocalCopyData.h
            DDSSharedObjectBase.h
            DDSNodeNetworkService.h
            DDSDataObjectName.h
            DDSNodeSharedObjectResolver.h
            DDSResponder.refl.h
            DDSResolver.h
            DDSDatabaseConnection.h
            DDSDatabaseTypes.h
            DDSServerToServerMessages.refl.meta.h
            DDSObjectInterface.h
            DDSEndpointFactoryList.h
            DDSWebsiteFactoryStaticContent.h
            DDSEndpointInterface.h
            DDSEndpointFactory.h
            DDSDataObject.h
            DDSServerToServerReceiver.h
            DDSConnectionFactoryBase.h
            DDSCall.h
            DDSResponder.h
            DDSLoadBalancerNetworkService.h
            DDSResponderCall.h
            DDSDeferredCallbackSystem.h
            DDSSharedLocalCopyDatabase.h
            DDSWebsiteFilesystem.h
            DDSServerMessage.h
            DDSAggregateSubscription.h
            DDSServerToServerSender.h
            DDSDatabaseConnectionPool.h
            DDSLoadBalancerMessages.refl.h
            DDSCoordinatorState.h
            DDSSharedLocalCopy.h
            DDSEndpointFactoryBase.h
            DDSDeferredCallback.h
            DDSRandom.h
            DDSCoordinatorNetworkService.h
            DDSDataObjectAddress.h
            DDSDataObjectStore.h
            DDSThrottle.refl.meta.h
            DDSLoadBalancerMessages.refl.meta.h
            DDSResponder.refl.meta.h
            DDSHttpRequest.h
            DDSDataObjectStoreHelpers.h
            DDSConnectionId.h
            DDSLoadBalancer.h
            DDSSharedObject.h
            DDSTokenValidator.h
            DDSCPUUsage.h
            DDSIncomingKeyspaceTransferManager.h
            DDSSharedObjectList.h
            DDSWebsiteFactory.h
            DDSSharedLocalCopyPtr.h
            DDSRoutingTable.refl.meta.h
            DDSResolverRequest.h
            DDSWebsiteFactoryBase.h
            DDSCoordinatorServerProtocol.h
            DDSNodeId.h
            DDSSharedObjectInterface.h
            DDSRoutingTable.h
            DDSDataObjectStoreTemporary.h
            DDSNetworkBackend.h
            DDSOutgoingKeyspaceTransferManager.h
            DDSKey.h
            DDSTokenBroker.h
            DDSVersion.h
            DDSHttpClient.h
            DDSWebsiteInterface.h
            DDSNodeState.h
            DDSDatabaseSetup.h
            DDSChallenge.h
            DDSWebsiteFactoryList.h
            DDSOutgoingKeyspaceTransfer.h
            DDSRoutingTable.refl.h
            DDSShutdown.h
            DDSDataObjectTypeList.h
            DDSTimerSystem.h
            DDSConnectionInterface.h
            DDSDatabaseBootstrap.h
            DDSLog.h
            DDSIncomingKeyspaceTransfer.h
            DDSCoordinatorClientProtocol.h
            DDSEncoding.h
            )

set(GENERIC_REFL_HurricaneDDS 
            DDSCoordinatorProtocolMessages.refl.h
            DDSServerToServerMessages.refl.h
            DDSThrottle.refl.h
            DDSSharedMessages.refl.h
            DDSResponder.refl.h
            DDSLoadBalancerMessages.refl.h
            DDSRoutingTable.refl.h
            )

foreach(REFL_FILE ${GENERIC_REFL_HurricaneDDS})
  string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
endforeach()


add_library(HurricaneDDS STATIC ${GENERIC_SRC_HurricaneDDS} ${GENERIC_HEADER_HurricaneDDS})


