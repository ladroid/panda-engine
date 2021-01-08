#define imgui_impl_opengl_loader_glad
#if defined(imgui_impl_opengl_loader_glew)
#include "glew.h"
#elif defined(imgui_impl_opengl_loader_glad)
#include "glad/glad.h"
#else
#include imgui_impl_opengl_loader_custom
#endif

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../../../../../imgui/imgui.h"
#include "../../../../../imgui/imgui_impl_opengl3.h"
#include "../../../../../imgui/imgui_impl_glfw.h"
#include "../../../../../imgui/imfilebrowser.h"
#include "../Singleton.h"
#include <iostream>

class UIEngine
{
private:
	ImGui::FileBrowser fileDialog;
	Singleton* singleton = Singleton::getInstance();
public:
	UIEngine()
	{

	}

	void Init(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui::StyleColorsDark();
	}

	void frame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void file_dialogue()
	{
		//file dialog
		fileDialog.SetTitle("File Browser");
		fileDialog.SetTypeFilters({ ".obj" });
	}

	void toolbar(glm::vec3 scale_model = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 translate = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		//render gui
		ImGui::Begin("Content Browser",(bool *) true, ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(350, 200));
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Import 3D Model", NULL))
				{
					fileDialog.Open();
				}
				if (ImGui::MenuItem("Close"))
				{
					exit(0);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (ImGui::CollapsingHeader("Rendering"), 0, true, true)
		{
			if (ImGui::TreeNode("Material"))
			{
				ImGui::SliderFloat3("Scale", (float *)&scale_model, 0.0f, 1.0f);
				ImGui::SliderFloat3("Translate", (float*)&translate, 0.0f, 1.0f);
				//ImGui::Text("Hello");
				ImGui::TreePop();
			}
		}
		
		ImGui::End();

		fileDialog.Display();

		if (fileDialog.HasSelected())
		{
			std::cout << "Selected filename " << fileDialog.GetSelected().string() << std::endl;
			fileDialog.ClearSelected();
			singleton->setModel("D:/Projects/Programming/GameDesign/Santa/cube/untitled.obj");
		}
	}

	void render()
	{
		// render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	~UIEngine()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};



