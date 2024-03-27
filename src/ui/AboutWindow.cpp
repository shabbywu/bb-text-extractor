#include "hello_imgui/hello_imgui.h"
#include "imgui_utilities/MarkdownHelper.h"
#include "imgui_utilities/HyperlinkHelper.h"
#include "AboutWindow.h"


void AboutWindow::gui()
{
    std::string help = R"(
本工具由战场兄弟中文本地化团队开发 - shabbywu

[如对本工具有任何建议, 欢迎反馈](https://github.com/shabbywu/Battle-Brothers-CN/issues)

)";
    MarkdownHelper::Markdown(help.c_str());
    if (ImGui::Button(ICON_FA_INFO " 查看使用说明")) {
        HelloImGui::DockableWindow *usageWindow =
            runnerParams->dockingParams.dockableWindowOfName("使用说明");
        usageWindow->isVisible = true;
    }
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_THUMBS_UP " Github 关注")) {
        HyperlinkHelper::OpenUrl("https://github.com/shabbywu/Battle-Brothers-CN");
    }
}
