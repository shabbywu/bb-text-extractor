#include "hello_imgui/hello_imgui.h"
#include "hello_imgui/hello_imgui_include_opengl.h"
#include "imgui_utilities/HyperlinkHelper.h"
#include "imgui_utilities/MarkdownHelper.h"
#include "imgui_utilities/FontLoader.h"
#include "imgui_utilities/imFileDialog.h"

#include "AppState.h"
#include "AboutWindow.h"
#include "UsageWindow.h"
#include "ToolsWindow.h"
#include "ConsoleWindow.h"

HelloImGui::RunnerParams runnerParams;
AppState state;

int main(int , char *[])
{
    AboutWindow aboutWindow(&runnerParams);
    UsageWindow usageWindow;
    ToolsWindow toolsWindow(&state);
    ConsoleWindow consoleWindow;

    // App window params
    runnerParams.appWindowParams.windowTitle = "战场兄弟文本提取器";
    runnerParams.appWindowParams.windowGeometry.size = {600, 480};

    //
    // Below, we will define all our application parameters and callbacks
    // before starting it.
    //
    runnerParams.imGuiWindowParams.tweakedTheme.Theme = ImGuiTheme::ImGuiTheme_ImGuiColorsLight;
    // ImGui window params
    runnerParams.imGuiWindowParams.defaultImGuiWindowType =
            HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    runnerParams.imGuiWindowParams.showMenu_View = false;
    runnerParams.imGuiWindowParams.showMenuBar = true;
    runnerParams.imGuiWindowParams.showStatusBar = true;
    runnerParams.imGuiWindowParams.showStatus_Fps = false;
    runnerParams.imGuiWindowParams.enableViewports = true;

    // Split the screen in two parts (two "DockSpaces")
    // This will split the preexisting default dockspace "MainDockSpace"
    // in two parts:
    // "MainDockSpace" will be on the left, "CodeSpace" will be on the right
    // and occupy 65% of the app width.
    runnerParams.dockingParams.dockingSplits = {
        { "MainDockSpace", "ConsoleSpace", ImGuiDir_Down, 0.4f, ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoDockingSplit},
        { "MainDockSpace", "CodeSpace", ImGuiDir_Right, 0.60f },

    };

    // Set the custom fonts
    runnerParams.callbacks.LoadAdditionalFonts = []() {
      FontLoader::LoadDefaultFont();
      MarkdownHelper::LoadFonts();
    };

    //
    // Dockable windows definitions
    //
    {

        HelloImGui::DockableWindow dock_tools;
        {
            dock_tools.label = "操作面板";
            dock_tools.dockSpaceName = "MainDockSpace";
            dock_tools.isVisible = true;
            dock_tools.includeInViewMenu = false;
            dock_tools.canBeClosed = false;
            dock_tools.rememberIsVisible = false;
            dock_tools.GuiFunction = [&toolsWindow] { toolsWindow.gui(); };
        };

        HelloImGui::DockableWindow dock_console;
        {
            dock_console.label = "终端";
            dock_console.dockSpaceName = "ConsoleSpace";
            dock_console.isVisible = true;
            dock_console.includeInViewMenu = false;
            dock_console.canBeClosed = false;
            dock_console.rememberIsVisible = false;
            dock_console.GuiFunction = [&consoleWindow, &dock_console] { consoleWindow.gui("终端", &dock_console.isVisible); };
        };

        HelloImGui::DockableWindow dock_usage;
        {
            dock_usage.label = "使用说明";
            dock_usage.dockSpaceName = "CodeSpace";
            dock_usage.isVisible = false;
            dock_usage.includeInViewMenu = false;
            dock_usage.GuiFunction = [&usageWindow] { usageWindow.gui(); };
        };

        HelloImGui::DockableWindow dock_about;
        {
            dock_about.label = "关于";
            dock_about.dockSpaceName = "CodeSpace";
            dock_about.isVisible = true;
            dock_about.includeInViewMenu = false;
            dock_about.GuiFunction = [&aboutWindow] { aboutWindow.gui(); };
        };


        //
        // Set our app dockable windows list
        //
        runnerParams.dockingParams.dockableWindows = {
            dock_tools,
            dock_console,
            dock_usage,
            dock_about
        };
    }

    // Set the app menu
    runnerParams.callbacks.ShowAppMenuItems = []{
        HelloImGui::DockableWindow *consoleWindow =
            runnerParams.dockingParams.dockableWindowOfName("终端");
        if (ImGui::MenuItem("打开终端"))
            consoleWindow->isVisible = true;
    };

    runnerParams.callbacks.ShowMenus = []{
        HelloImGui::DockableWindow *aboutWindow =
            runnerParams.dockingParams.dockableWindowOfName("关于");

        HelloImGui::DockableWindow *usageWindow =
            runnerParams.dockingParams.dockableWindowOfName("使用说明");

        if (ImGui::BeginMenu("链接"))
        {
            ImGui::TextDisabled("链接");
            if (ImGui::MenuItem("汉化项目主仓库"))
                HyperlinkHelper::OpenUrl("https://github.com/shabbywu/Battle-Brothers-CN");
            if (ImGui::MenuItem("汉化项目协同网站"))
                HyperlinkHelper::OpenUrl("https://paratranz.cn/projects/7032");
            if (ImGui::MenuItem("战场兄弟汉化发布"))
                HyperlinkHelper::OpenUrl("https://battle-brothers-cn.shabbywu.cn/");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("关于")) {
            if (ImGui::MenuItem("关于本工具"))
                aboutWindow->isVisible = true;
            if (ImGui::MenuItem("使用说明"))
                usageWindow->isVisible = true;
            if (ImGui::MenuItem("作者"))
                HyperlinkHelper::OpenUrl("https://github.com/shabbywu/");
            // if (ImGui::MenuItem("致谢"))
            //     acknowledgmentWindow->isVisible = true;
            ImGui::EndMenu();
        }
    };

    // Add some widgets in the status bar
    runnerParams.callbacks.ShowStatus = [] {
        //MarkdownHelper::Markdown("Dear ImGui Manual - [Repository](https://github.com/pthom/imgui_manual)");
        MarkdownHelper::Markdown("战场兄弟文本提取器 - [shabbywu](https://github.com/shabbywu/) - [让战团从拾荣光](https://paratranz.cn/projects/7032)");
    };

    ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void* {
        GLuint tex;

        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, 0);

        return (void*)tex;
    };

    ifd::FileDialog::Instance().DeleteTexture = [](void* tex) {
        GLuint texID = (GLuint)(size_t)(tex);
        glDeleteTextures(1, &texID);
    };

    HelloImGui::Run(runnerParams);
    return 0;
}
