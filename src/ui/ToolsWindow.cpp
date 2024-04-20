#include "hello_imgui/hello_imgui.h"
#include "imgui_utilities/imFileDialog.h"
#include "ToolsWindow.h"
#include "../text-extractor/binding.h"


void ToolsWindow::gui() {
    if (state->lang == "cn") {
        if (ImGui::Button(ICON_FA_FILE " 选择游戏根目录", ImVec2(0, 40)))
            ifd::FileDialog::Instance().Open("选择游戏根目录", "选择游戏根目录", "");

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
                dispatch_extractor(state);
            }
        } else {
            ImGui::BeginDisabled();
            ImGui::Button(ICON_FA_PLAY " 提取文本", ImVec2(0, 40));
            ImGui::SetItemTooltip("请先设置游戏根目录和输出目录");
            ImGui::EndDisabled();
        }

        if (ifd::FileDialog::Instance().IsDone("选择游戏根目录")) {
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

    } else {

        if (ImGui::Button(ICON_FA_FILE " Select game root directory", ImVec2(0, 40)))
            ifd::FileDialog::Instance().Open("Select game root directory", "Select game root directory", "");

        if (state->dataDir.string().length() > 0) {
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Game Root Directory: ");
            ImGui::SameLine();
            ImGui::TextWrapped(state->dataDir.string().c_str());
        }

        if (ImGui::Button(ICON_FA_FILE " Select output directory", ImVec2(0, 40)))
            ifd::FileDialog::Instance().Open("Select output directory", "Select output directory", "");

        if (state->destDir.string().length() > 0) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Output Directory: ");
            ImGui::SameLine();
            ImGui::TextWrapped(state->destDir.string().c_str());
        }

        if (state->dataDir.string().length() > 0 && state->destDir.string().length() > 0) {
            if (ImGui::Button(ICON_FA_PLAY " Extract text")) {
                dispatch_extractor(state);
            }
        } else {
            ImGui::BeginDisabled();
            ImGui::Button(ICON_FA_PLAY " Extract text", ImVec2(0, 40));
            ImGui::SetItemTooltip("Please set the game root directory and output directory first");
            ImGui::EndDisabled();
        }

        if (ifd::FileDialog::Instance().IsDone("Select game root directory")) {
            if (ifd::FileDialog::Instance().HasResult()) {
                state->dataDir = ifd::FileDialog::Instance().GetResult();
            }
            ifd::FileDialog::Instance().Close();
        }

        if (ifd::FileDialog::Instance().IsDone("Select output directory")) {
            if (ifd::FileDialog::Instance().HasResult()) {
                state->destDir = ifd::FileDialog::Instance().GetResult();
            }
            ifd::FileDialog::Instance().Close();
        }

    }

}
