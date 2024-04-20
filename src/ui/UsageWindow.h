#pragma once
#include "hello_imgui/hello_imgui.h"
#include "AppState.h"

class UsageWindow
{
public:
    UsageWindow() {};
    void gui(AppState&);

    std::string usageCN = R"(# 使用说明
1. 设置游戏数据目录 (通常是 X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\data 目录)
2. 设置文本提取的输出路径 (例如 X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\localization\)
3. 点击「提取文本」

# 导出结果说明
文本使用 json 格式的存储导出结果, 每个词条为一个 JSON 对象, 具体字段含义如下:
  * key: 唯一键, 等同于 po format 的 msgid
  * original: 原文
  * translation: 译文
  * context: 原文在游戏代码中的上下文

## 1. 无上下文的简单文本
{

    "key": "Encountered another caravan slaughtered by greenskins",
    "original": "Encountered another caravan slaughtered by greenskins",
    "translation": "",
    "context": ""
}

## 2. 具有简单上下文的文本
{
    "key": "Trading Caravan",
    "original": "Trading Caravan",
    "translation": "",
    "context": "this.m.Name = \"Trading Caravan\""
}

## 3. 具有复杂上下文的文本
{
    "key": " points",
    "original": " points",
    "translation": "",
    "context": "this.Const.UI.getColorizedEntityName(actor) + \" heals for \" + healthAdded + \" points\""
}

___
[)" ICON_FA_BELL R"(如遇到使用问题, 欢迎反馈!](https://github.com/shabbywu/bb-text-extractor/issues) | [)" ICON_FA_THUMBS_UP R"( Github 关注](https://github.com/shabbywu/bb-text-extractor)
)";

    std::string usageEN = R"(# Usage
1. Set the game data directory (usually the X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\data directory)
2. Set the output path for text extraction (for example, X:\Program Files (x86)\Steam\steamapps\common\Battle Brothers\localization\)
3. Click "Extract text"

# Export result description
The text is stored and exported in json format. Each entry is a JSON object. The specific field meanings are as follows:
   * key: unique key, equivalent to msgid of po format
   * original: original text
   * translation: translation
   * context: the context of the original text in the game code

## 1. Simple text without context
{

    "key": "Encountered another caravan slaughtered by greenskins",
    "original": "Encountered another caravan slaughtered by greenskins",
    "translation": "",
    "context": ""
}

## 2. Text with simple context
{
    "key": "Trading Caravan",
    "original": "Trading Caravan",
    "translation": "",
    "context": "this.m.Name = \"Trading Caravan\""
}

## 3. Text with complex context
{
    "key": " points",
    "original": " points",
    "translation": "",
    "context": "this.Const.UI.getColorizedEntityName(actor) + \" heals for \" + healthAdded + \" points\""
}

___
[)" ICON_FA_BELL R"(Feedback](https://github.com/shabbywu/bb-text-extractor/issues) | [)" ICON_FA_THUMBS_UP R"( Github Star](https://github.com/shabbywu/bb-text-extractor)
)";
};
