#include "imgui_utilities/MarkdownHelper.h"
#include "UsageWindow.h"


void UsageWindow::gui(AppState& state)
{
    if (state.lang == "cn") {
        MarkdownHelper::Markdown(usageCN.c_str());
    } else {
        MarkdownHelper::Markdown(usageEN.c_str());
    }
}
