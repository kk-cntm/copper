#include "ExampleLayer.h"
#include "Copper/Log.h"
#include "Copper/Application.h"
#include "imgui/imgui.h"

void ExampleLayer::OnEvent(Copper::Event& event)
{
}

void ExampleLayer::OnUpdate()
{
}

void ExampleLayer::OnImGuiUpdate()
{
    static bool show = true;
    if (show)
        ImGui::ShowDemoWindow(&show);
}
