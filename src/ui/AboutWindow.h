#pragma once
#include "AppState.h"

class AboutWindow
{
public:
    HelloImGui::RunnerParams* runnerParams;
    AboutWindow(HelloImGui::RunnerParams* runnerParams)
    {
        this->runnerParams = runnerParams;
    }
    void gui(AppState&);

    std::string helpCN = R"(
本工具由战场兄弟中文本地化团队开发

[如对本工具有任何建议, 欢迎反馈](https://github.com/shabbywu/bb-text-extractor/issues)

)";

    std::string helpEN = R"(
This tool is developed by the Battlefield Brothers Chinese localization team

[FeedBack](https://github.com/shabbywu/bb-text-extractor/issues)

)";
};
