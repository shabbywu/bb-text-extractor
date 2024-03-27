#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

#include "hello_imgui/hello_imgui.h"
#include "hello_imgui/hello_imgui_include_opengl.h"
#include "ui/imgui_utilities/HyperlinkHelper.h"
#include "ui/imgui_utilities/MarkdownHelper.h"
#include "ui/imgui_utilities/FontLoader.h"
#include "ui/imgui_utilities/imFileDialog.h"

#include "ui/AppState.h"
#include "ui/AboutWindow.h"
#include "ui/UsageWindow.h"
#include "ui/ToolsWindow.h"
#include "ui/ConsoleWindow.h"
#include "text-extractor/binding.h"
#include "assets/fonts/font.h"
#include "assets/fonts/fontawesome-webfont.h"
#include "assets/backgrounds/loading_screen_02.h"

using namespace std::chrono_literals;
HelloImGui::RunnerParams runnerParams;
AppState state;

int main(int , char *[])
{
    AboutWindow aboutWindow(&runnerParams);
    UsageWindow usageWindow;
    ToolsWindow toolsWindow(&state);
    ConsoleWindow consoleWindow(&state);

    // App window params
    runnerParams.appWindowParams.windowTitle = "战场兄弟文本提取器";
    runnerParams.appWindowParams.windowGeometry.size = {600, 480};

    // ini file params
    runnerParams.iniFilename_useAppWindowTitle = true;
    runnerParams.iniFolderType = HelloImGui::IniFolderType::AppUserConfigFolder;

    //
    // Below, we will define all our application parameters and callbacks
    // before starting it.
    //
    runnerParams.imGuiWindowParams.tweakedTheme.Theme = ImGuiTheme::ImGuiTheme_ImGuiColorsClassic;
    runnerParams.imGuiWindowParams.tweakedTheme.Tweaks.AlphaMultiplier = 0.75f;

    // ImGui window params
    runnerParams.imGuiWindowParams.defaultImGuiWindowType =
            HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    runnerParams.imGuiWindowParams.showMenu_View = false;
    runnerParams.imGuiWindowParams.showMenuBar = true;
    runnerParams.imGuiWindowParams.showStatusBar = true;
    runnerParams.imGuiWindowParams.showStatus_Fps = false;
    runnerParams.imGuiWindowParams.enableViewports = true;

    runnerParams.dockingParams.dockingSplits = {
        { "MainDockSpace", "ConsoleSpace", ImGuiDir_Down, 0.4f,
        ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoDockingSplit
        },
        { "MainDockSpace", "CodeSpace", ImGuiDir_Right, 0.60f, ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoUndocking},
    };
    runnerParams.dockingParams.mainDockSpaceNodeFlags = ImGuiWindowFlags_DockNodeHost;

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
            dock_tools.callBeginEnd = true;
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
            dock_console.callBeginEnd = true;
        };

        HelloImGui::DockableWindow dock_usage;
        {
            dock_usage.label = "使用说明";
            dock_usage.dockSpaceName = "CodeSpace";
            dock_usage.isVisible = false;
            dock_usage.includeInViewMenu = false;
            dock_usage.GuiFunction = [&usageWindow] { usageWindow.gui(); };
            dock_usage.callBeginEnd = true;
        };

        HelloImGui::DockableWindow dock_about;
        {
            dock_about.label = "关于";
            dock_about.dockSpaceName = "CodeSpace";
            dock_about.isVisible = true;
            dock_about.includeInViewMenu = false;
            dock_about.GuiFunction = [&aboutWindow] { aboutWindow.gui(); };
            dock_about.callBeginEnd = true;
        };

        //
        // Set our app dockable windows list
        //
        runnerParams.dockingParams.dockableWindows = {
            dock_tools,
            dock_console,
            dock_usage,
            dock_about,
        };
    }

    runnerParams.dockingParams.mainDockSpaceNodeFlags = ImGuiDockNodeFlags_NoDockingSplit;

    // Set the custom fonts
    runnerParams.callbacks.LoadAdditionalFonts = []() {
        FontLoader::LoadDefaultFont();
        MarkdownHelper::LoadFonts();
    };

    // Set the app menu
    runnerParams.callbacks.ShowAppMenuItems = []{
        HelloImGui::DockableWindow *consoleWindow =
            runnerParams.dockingParams.dockableWindowOfName("终端");
        if (!consoleWindow->isVisible) {
            if (ImGui::MenuItem("打开终端"))
                consoleWindow->isVisible = true;
        }
    };

    // set menus
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
        MarkdownHelper::Markdown("战场兄弟文本提取器 - [shabbywu](https://github.com/shabbywu/) - [参与汉化](https://paratranz.cn/projects/7032)");
    };

    // disable dark style
    runnerParams.callbacks.SetupImGuiStyle = HelloImGui::EmptyVoidFunction;

    // setup background image
    runnerParams.callbacks.BeforeImGuiRender = [] {
        auto viewport = ImGui::GetMainViewport();
        auto pos = viewport->Pos;
        auto size = viewport->Size;
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowPos(ImVec2(pos[0] - 10, pos[1] - 10));
        ImGui::SetNextWindowSize(ImVec2(size[0] + 20, size[1] + 20));
        ImGui::Begin("Background", NULL, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);
        HelloImGui::ImageFromAsset("background.jpeg", ImVec2(size[0] + 20, size[1] + 20));
        ImGui::End();
        // glClear(GL_COLOR_BUFFER_BIT);
    };

    // start python daemon after init
    runnerParams.callbacks.PostInit = [](){
        std::filesystem::path userConfigFolder = HelloImGui::IniFolderLocation(HelloImGui::IniFolderType::AppUserConfigFolder);

        auto appFolder = userConfigFolder / "bb-text-extractor";
        state.assetsDir = appFolder / "assets";
        state.pythonRootDir = appFolder / "binary";

        {
            auto fontsFolder = state.assetsDir / "fonts";
            if (!std::filesystem::exists(fontsFolder) ) {
                std::filesystem::create_directories(fontsFolder);

                auto & font = bin2cpp::getFontTtfFile();
                auto fontFilename = fontsFolder/font.getFileName();
                std::ofstream f(fontFilename, std::ios::out | std::ios::binary | std::ios::trunc);
                if (f.fail()) return;
                f.write((const char*)font.getBuffer(), font.getSize());
                f.close();
            }

            auto backgroundFilename = state.assetsDir / "background.jpeg";
            if (!std::filesystem::exists(backgroundFilename)) {
                auto & file = bin2cpp::getLoading_screen_02JpegFile();
                std::ofstream f(backgroundFilename, std::ios::out | std::ios::binary | std::ios::trunc);
                if (f.fail()) return;
                f.write((const char*)file.getBuffer(), file.getSize());
                f.close();
            }
        }

        HelloImGui::SetAssetsFolder(state.assetsDir.string());
        start_python_daemon(&state);
    };
    // notice python daemon to stop
    runnerParams.callbacks.BeforeExit = []() {
        state.appShallExit = true;
        state.addLog = [](std::string message) {
            std::cout << message << std::endl;
        };
    };
    runnerParams.callbacks.BeforeExit_PostCleanup = [](){
        shutdown_python_daemon(&state);
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
