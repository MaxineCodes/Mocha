//
// Created by maxin on 04/12/2025.
//

#include "gui.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "logger.h"

void Mocha::GUI::setup(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Mocha::GUI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Mocha::GUI::createGuiElements()
{
    //ImGui::ShowDemoWindow();
    DrawLogWindow();
}

void Mocha::GUI::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Mocha::GUI::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Mocha::GUI::DrawLogWindow()
{
    ImGui::Begin("DebugLog");
    ImGui::BeginChild("ScrollingRegion", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);

    // Get all the log messages onto the log window
    const auto& logMessages = logger::getLogMessages();
    for (const auto& message : logMessages)
    {
        if      (message.rfind("[ERROR]", 0) == 0)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 80, 80, 255));   // red
        else if (message.rfind("[WARN]", 0) == 0)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 200, 0, 255)); // yellow
        else if (message.rfind("[INFO]", 0) == 0)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255)); // white
        else if (message.rfind("[GL_ERROR]", 0) == 0)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 20, 20, 255)); // dark red
        else if (message.rfind("[DEBUG]", 0) == 0)
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 100, 255)); // dark grey
        else
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(200, 200, 200, 255)); // default grey


        ImGui::TextUnformatted(message.c_str());
        ImGui::PopStyleColor();
    }

    // Scroll to bottom by default
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();

    ImGui::End();
}
