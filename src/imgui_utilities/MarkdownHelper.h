#pragma once
#include "hello_imgui/icons_font_awesome_4.h"
#include <imgui.h>
#include <string>

namespace MarkdownHelper
{
    extern ImFont *fontH1, *fontH2, *fontH3;

    void LoadFonts();
    void Markdown(const std::string &markdown_);
}