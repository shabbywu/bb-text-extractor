#pragma once
#include "AppState.h"


class ToolsWindow {
    public:
        ToolsWindow(AppState* state) {
            this->state = state;
            dataDir = state->dataDir.string();
            destDir = state->destDir.string();
        };
        void gui();

        AppState* state;
        std::string dataDir;
        std::string destDir;
};