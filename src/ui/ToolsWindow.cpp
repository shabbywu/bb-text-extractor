#include "hello_imgui/hello_imgui.h"
#include "imgui_utilities/imFileDialog.h"
#include "ToolsWindow.h"
#include "../text-extractor/binding.h"


void ToolsWindow::gui() {
    if (ImGui::Button(ICON_FA_FILE " 选择游戏目录", ImVec2(0, 40)))
        ifd::FileDialog::Instance().Open("选择游戏目录", "选择游戏目录", "");

    if (state->dataDir.string().length() > 0) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "游戏目录: ");
        ImGui::SameLine();
        ImGui::TextWrapped(state->dataDir.string().c_str());
    }

    if (ImGui::Button(ICON_FA_FILE " 选择输出目录", ImVec2(0, 40)))
        ifd::FileDialog::Instance().Open("选择输出目录", "选择输出目录", "");

    if (state->destDir.string().length() > 0) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "输出目录: ");
        ImGui::SameLine();
        ImGui::TextWrapped(state->destDir.string().c_str());
    }

    if (state->dataDir.string().length() > 0 && state->destDir.string().length() > 0) {
        if (ImGui::Button(ICON_FA_PLAY " 提取文本")) {
            run_python();
        }
    } else {
        ImGui::BeginDisabled();
        ImGui::Button(ICON_FA_PLAY " 提取文本", ImVec2(0, 40));
        ImGui::SetItemTooltip("请先设置游戏目录和输出目录");
        ImGui::EndDisabled();
    }

    if (ifd::FileDialog::Instance().IsDone("选择游戏目录")) {
        if (ifd::FileDialog::Instance().HasResult()) {
            state->dataDir = ifd::FileDialog::Instance().GetResult();
        }
        ifd::FileDialog::Instance().Close();
    }

    if (ifd::FileDialog::Instance().IsDone("选择输出目录")) {
        if (ifd::FileDialog::Instance().HasResult()) {
            state->destDir = ifd::FileDialog::Instance().GetResult();
        }
        ifd::FileDialog::Instance().Close();
    }
}
