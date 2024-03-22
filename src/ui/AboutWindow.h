#pragma once

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
