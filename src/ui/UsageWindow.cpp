#include "imgui_utilities/MarkdownHelper.h"
#include "UsageWindow.h"


void UsageWindow::gui()
{
    MarkdownHelper::Markdown(usage.c_str());
}
