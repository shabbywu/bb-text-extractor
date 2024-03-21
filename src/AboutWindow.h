#pragma once
#include "hello_imgui/icons_font_awesome_4.h"

class AboutWindow
{
public:
    HelloImGui::RunnerParams* runnerParams;
    AboutWindow(HelloImGui::RunnerParams* runnerParams)
    {
        this->runnerParams = runnerParams;
    }
    void gui();
};

