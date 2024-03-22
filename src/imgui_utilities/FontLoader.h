#pragma once
#include <fplus/fplus.hpp>


namespace FontLoader {
    ImFont * gDefaultFont = nullptr;

    void LoadDefaultFont()
    {
        float fontSize = 14.f;
        std::string fontFilename = "fonts/font.ttf";
        gDefaultFont = HelloImGui::LoadFontTTF_WithFontAwesomeIcons(fontFilename, fontSize, true);
    }
}
