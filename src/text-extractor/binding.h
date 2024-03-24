#pragma once
#include <filesystem>
#include "../ui/AppState.h"


void start_python_daemon(AppState *state);
void dispatch_extractor(AppState *state);
void shutdown_python_daemon(AppState *state);
