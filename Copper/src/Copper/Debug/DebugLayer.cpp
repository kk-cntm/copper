#include "DebugLayer.h"
#include "Copper/Core.h"
#include "Copper/Application.h"
#include "Copper/Log.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Copper
{

DebugLayer::DebugLayer()
    : Layer("DebugLayer") {}

DebugLayer::~DebugLayer()
{
}

void DebugLayer::OnAttach()
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGuiIO& io = ImGui::GetIO();
    
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    
    ImGui_ImplOpenGL3_Init("#version 410");
}

void DebugLayer::OnDetach()
{
    
}

void DebugLayer::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    
    dispatcher.Dispatch<MouseMovedEvent>(CPR_EVENT_FN(DebugLayer::OnMouseMoveEvent));
    dispatcher.Dispatch<MouseScrollEvent>(CPR_EVENT_FN(DebugLayer::OnMouseScrollEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(CPR_EVENT_FN(DebugLayer::OnMouseButtonPressEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(CPR_EVENT_FN(DebugLayer::OnMouseButtonReleaseEvent));
    dispatcher.Dispatch<KeyPressedEvent>(CPR_EVENT_FN(DebugLayer::OnKeyPressEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(CPR_EVENT_FN(DebugLayer::OnKeyReleaseEvent));
    dispatcher.Dispatch<WindowResizeEvent>(CPR_EVENT_FN(DebugLayer::OnWindowResizeEvent));
}

void DebugLayer::OnUpdate()
{
    const Application& app = Application::Get();
    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    const auto dpi = app.GetWindow().GetDPI();
    io.DisplayFramebufferScale = ImVec2(dpi.first, dpi.second);

    float time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_Time > 0 ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool DebugLayer::OnMouseMoveEvent(MouseMovedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(event.GetX(), event.GetY());

    return false;
}

bool DebugLayer::OnMouseButtonPressEvent(MouseButtonPressedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetMouseButton()] = true;

    return false;
}

bool DebugLayer::OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetMouseButton()] = false;

    return false;
}

bool DebugLayer::OnMouseScrollEvent(MouseScrollEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.GetOffsetX();
    io.MouseWheel += event.GetOffsetY();

    return false;
}

bool DebugLayer::OnKeyPressEvent(KeyPressedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.GetKeyCode()] = true;

    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    return false;
}

bool DebugLayer::OnKeyReleaseEvent(KeyReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.GetKeyCode()] = false;

    return false;
}

bool DebugLayer::OnWindowResizeEvent(WindowResizeEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());

    return false;
}

}
