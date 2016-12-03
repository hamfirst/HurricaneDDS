#pragma once

class DDSNodeState;
class DDSCoordinatorState;

void DDSSetupShutdownSignalHandler();
bool DDSWantsShutdown();
void DDSShutdown();
void DDSShutdownRegisterNode(DDSNodeState * node);
void DDSShutdownUnregisterNode(DDSNodeState * node);

void DDSShutdownRegisterCoordinator(DDSCoordinatorState * coordinator);
void DDSShutdownUnregisterCoordinator(DDSCoordinatorState * coordinator);
