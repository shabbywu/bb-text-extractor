#pragma once
#include "hello_imgui/hello_imgui.h"

class UsageWindow
{
public:
    UsageWindow() {};
    void gui();

    std::string usage = R"(
使用说明:
1. 设置游戏数据目录 (通常是 X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\data 目录)
2. 设置文本提取的输出路径 (例如 X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\localization\)
3. 点击「提取文本」

[)" ICON_FA_BELL R"(遇到使用问题, 欢迎反馈!](https://github.com/shabbywu/bb-text-extractor/)

)";
};
