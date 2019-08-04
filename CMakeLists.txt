cmake_minimum_required(VERSION 3.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/External
                    ${PROJECT_SOURCE_DIR}/StormTech
                    ${PROJECT_SOURCE_DIR}/Tools
                    ${PROJECT_SOURCE_DIR}/Shared
                    ${PROJECT_SOURCE_DIR}/Project
                    ${PROJECT_SOURCE_DIR}/Lobby)

set(CMAKE_CXX_STANDARD 17)

set(GENERIC_SRC_HurricaneDDS 
            DDSAggregateSubscription.cpp
            DDSCPUUsage.cpp
            DDSConnectionInterface.cpp
            DDSCoordinatorClientProtocol.cpp
            DDSCoordinatorNetworkService.cpp
            DDSCoordinatorServerProtocol.cpp
            DDSCoordinatorState.cpp
            DDSDatabaseBootstrap.cpp
            DDSDatabaseConnection.cpp
            DDSDatabaseConnectionPool.cpp
            DDSDatabaseSetup.cpp
            DDSDeferredCallback.cpp
            DDSEncoding.cpp
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
            DDSSharedLocalCopy.cpp
            DDSSharedLocalCopyData.cpp
            DDSSharedLocalCopyDatabase.cpp
            DDSSharedLocalCopyPtr.cpp
            DDSSharedObjectInterface.cpp
            DDSShutdown.cpp
            DDSThrottle.refl.cpp
            DDSTimerSystem.cpp
            DDSTokenBroker.cpp
            DDSTokenValidator.cpp
            DDSVersion.cpp
            DDSWebsiteFactoryBase.cpp
            DDSWebsiteFactoryStaticContent.cpp
            DDSWebsiteFilesystem.cpp
            DDSWebsiteFilesystemBuilder.cpp
            DDSWebsiteInterface.cpp
            )

set(GENERIC_HEADER_HurricaneDDS 
            DDSAggregateSubscription.h
            DDSCPUUsage.h
            DDSCall.h
            DDSChallenge.h
            DDSConnectionFactoryBase.h
            DDSConnectionId.h
            DDSConnectionInterface.h
            DDSCoordinatorClientProtocol.h
            DDSCoordinatorNetworkService.h
            DDSCoordinatorProtocolMessages.refl.h
            DDSCoordinatorProtocolMessages.refl.meta.h
            DDSCoordinatorServerProtocol.h
            DDSCoordinatorState.h
            DDSDataObject.h
            DDSDataObjectAddress.h
            DDSDataObjectName.h
            DDSDataObjectStore.h
            DDSDataObjectStoreBase.h
            DDSDataObjectStoreHelpers.h
            DDSDataObjectStoreTemporary.h
            DDSDataObjectTypeList.h
            DDSDatabaseBootstrap.h
            DDSDatabaseConnection.h
            DDSDatabaseConnectionPool.h
            DDSDatabaseSetup.h
            DDSDatabaseTypes.h
            DDSDeferredCallback.h
            DDSDeferredCallbackSystem.h
            DDSEncoding.h
            DDSEndpointFactory.h
            DDSEndpointFactoryBase.h
            DDSEndpointFactoryList.h
            DDSEndpointInterface.h
            DDSHttpClient.h
            DDSHttpRequest.h
            DDSIncomingKeyspaceTransfer.h
            DDSIncomingKeyspaceTransferManager.h
            DDSKey.h
            DDSLoadBalancer.h
            DDSLoadBalancerMessages.refl.h
            DDSLoadBalancerMessages.refl.meta.h
            DDSLoadBalancerNetworkService.h
            DDSLog.h
            DDSNetworkBackend.h
            DDSNodeId.h
            DDSNodeInterface.h
            DDSNodeNetworkService.h
            DDSNodeSharedObjectResolver.h
            DDSNodeState.h
            DDSObjectInterface.h
            DDSOutgoingKeyspaceTransfer.h
            DDSOutgoingKeyspaceTransferManager.h
            DDSRandom.h
            DDSResolver.h
            DDSResolverBackend.h
            DDSResolverRequest.h
            DDSResponder.h
            DDSResponder.refl.h
            DDSResponder.refl.meta.h
            DDSResponderCall.h
            DDSRoutingTable.h
            DDSRoutingTable.refl.h
            DDSRoutingTable.refl.meta.h
            DDSServerMessage.h
            DDSServerToServerMessages.refl.h
            DDSServerToServerMessages.refl.meta.h
            DDSServerToServerReceiver.h
            DDSServerToServerSender.h
            DDSSharedLocalCopy.h
            DDSSharedLocalCopyData.h
            DDSSharedLocalCopyDatabase.h
            DDSSharedLocalCopyPtr.h
            DDSSharedMessages.refl.h
            DDSSharedMessages.refl.meta.h
            DDSSharedObject.h
            DDSSharedObjectBase.h
            DDSSharedObjectInterface.h
            DDSSharedObjectList.h
            DDSShutdown.h
            DDSThrottle.refl.h
            DDSThrottle.refl.meta.h
            DDSTimerSystem.h
            DDSTokenBroker.h
            DDSTokenValidator.h
            DDSVersion.h
            DDSWebsiteFactory.h
            DDSWebsiteFactoryBase.h
            DDSWebsiteFactoryList.h
            DDSWebsiteFactoryStaticContent.h
            DDSWebsiteFilesystem.h
            DDSWebsiteFilesystemBuilder.h
            DDSWebsiteInterface.h
            )

set(GENERIC_REFL_HurricaneDDS 
            DDSCoordinatorProtocolMessages.refl.h
            DDSLoadBalancerMessages.refl.h
            DDSResponder.refl.h
            DDSRoutingTable.refl.h
            DDSServerToServerMessages.refl.h
            DDSSharedMessages.refl.h
            DDSThrottle.refl.h
            )

if(GENERATE_REFL)
  foreach(REFL_FILE ${GENERIC_REFL_HurricaneDDS})
    string(REPLACE ".refl.h" ".refl.meta.h" META_FILE ${REFL_FILE})
    add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}
                       COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/Lobby -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
                       MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}
                       IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})
  endforeach()
endif()

add_library(HurricaneDDS STATIC ${GENERIC_SRC_HurricaneDDS} ${GENERIC_HEADER_HurricaneDDS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GENERIC_SRC_HurricaneDDS} ${GENERIC_HEADER_HurricaneDDS})

