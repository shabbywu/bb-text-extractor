#pragma once

class UsageWindow
{
public:
    UsageWindow() {};
    void gui();

    std::string usage = R"(
Note: an online playground provided with this manual enables you to test ImGui without any installation:
* [see a demo](https://youtu.be/FJgObNNmuzo)
* [launch the playground](https://gitpod.io/#https://github.com/pthom/imgui_manual).

This interactive manual was developed using [Hello ImGui](https://github.com/pthom/hello_imgui), which provided the emscripten port, as well as the assets embedding and image loading. ImGuiManual.cpp gives a good overview of [Hello Imgui API](https://github.com/pthom/hello_imgui/blob/master/src/hello_imgui/hello_imgui_api.md).

See also a [related demo for Implot](https://traineq.org/implot_demo/src/implot_demo.html).

[I'd love to read your feedback!](https://github.com/pthom/imgui_manual/issues/1)
)";
};
