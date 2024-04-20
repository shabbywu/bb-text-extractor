#include "hello_imgui/hello_imgui.h"
#include "imgui_utilities/MarkdownHelper.h"
#include "imgui_utilities/HyperlinkHelper.h"
#include "AboutWindow.h"


void AboutWindow::gui(AppState& state)
{
    if (state.lang == "cn") {
        MarkdownHelper::Markdown(helpCN.c_str());
        if (ImGui::Button(ICON_FA_INFO " 查看使用说明")) {
            HelloImGui::DockableWindow *usageWindow =
                runnerParams->dockingParams.dockableWindowOfName("使用说明");
            usageWindow->isVisible = true;
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_THUMBS_UP " Github 关注")) {
            HyperlinkHelper::OpenUrl("https://github.com/shabbywu/bb-text-extractor");
        }
    } else {
        MarkdownHelper::Markdown(helpEN.c_str());
        if (ImGui::Button(ICON_FA_INFO " Usage")) {
            HelloImGui::DockableWindow *usageWindow =
                runnerParams->dockingParams.dockableWindowOfName("使用说明");
            usageWindow->isVisible = true;
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_THUMBS_UP " Github Star")) {
            HyperlinkHelper::OpenUrl("https://github.com/shabbywu/bb-text-extractor");
        }
    }
}
