//
// Created by Lado on 13/7/20.
//

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../../panda-engine-windows/Lotos/imgui/imgui.h"
#include "../../panda-engine-windows/Lotos/imgui/imgui_impl_opengl3.h"
#include "../../panda-engine-windows/Lotos/imgui/imgui_impl_glfw.h"
#include "../../panda-engine-windows/Lotos/imgui/ImGuiFileBrowser.h"
#include "../3D/Entity/Shader.h"
#include "../../panda-engine-windows/Lotos/Camera.h"
#include "Entity/Light.h"
#include "Entity/Mesh.h"
#include "Entity/Model.h"
#include "Entity/Audio.h"
#include "Entity/Singleton.h"
#include "Entity/Skybox.h"
#include <iostream>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../../panda-engine-windows/Lotos/stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// model pos
glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

//TODO:skybox size 
float skyboxSize = 50.0f;
//TODO:skybox textures
std::vector<std::string> skyboxFiles = { "D:/Projects/Programming/MyGameEngine/3Dresources/back.tga",
                                        "D:/Projects/Programming/MyGameEngine/3Dresources/down.tga",
                                        "D:/Projects/Programming/MyGameEngine/3Dresources/front.tga",
                                        "D:/Projects/Programming/MyGameEngine/3Dresources/left.tga",
                                        "D:/Projects/Programming/MyGameEngine/3Dresources/right.tga",
                                        "D:/Projects/Programming/MyGameEngine/3Dresources/up.tga" };

Model ourModel;

Singleton* singleton = Singleton::getInstance();

imgui_addons::ImGuiFileBrowser fileDialog;
void init(std::string name)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    //uiengine.Init(window);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
    
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("D:/Projects/Programming/MyGameEngine/panda-engine-windows/Lotos/src/engine/3D/model_loading.vs", "D:/Projects/Programming/MyGameEngine/panda-engine-windows/Lotos/src/engine/3D/model_loading.fs");
    
    // load models
    // -----------
    ourModel.setModel("D:/Projects/Programming/GameDesign/Santa/santa_house/source/mesh_Model_4.obj");

    std::cout << singleton->getModel() << std::endl;

    /*
    * //TODO:Skybox
    */
    Skybox* skybox = new Skybox(skyboxFiles, skyboxSize);
    skybox->loadCube();
    Shader skyShader("D:/Projects/Programming/MyGameEngine/panda-engine-windows/Lotos/src/engine/3D/skyshader.vs", "D:/Projects/Programming/MyGameEngine/panda-engine-windows/Lotos/src/engine/3D/skyshader.fs");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //TODO:audio
    //Audio* audio = new Audio();
    //audio->play("D:/Projects/Programming/MyGames/GodotGames/Einsiedler/audio/Ominous-Pursuit.ogg");

    // render loop
    // -----------
    //uiengine.file_dialogue();

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Content Browser", (bool*)true, ImGuiWindowFlags_MenuBar);
            ImGui::SetWindowSize(ImVec2(450, 400));
            bool open = false;
            bool anim = false;
            bool audio = false;
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Import 3D Model", NULL))
                    {
                        open = true;
                    }
                    if (ImGui::MenuItem("Close"))
                    {
                        exit(0);
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Developer Tools"))
                {
                    if (ImGui::MenuItem("Output Log"))
                    {
                        ImGui::LogToClipboard();
                        ImGui::LogText("Hello...");
                        ImGui::LogFinish();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            if (ImGui::CollapsingHeader("Object", ImGuiTreeNodeFlags_CollapsingHeader))
            {
                if (ImGui::TreeNode("Transform"))
                {
                    ImGui::SliderFloat3("Scale", (float*)&scale, 0.0f, 1.0f);
                    ImGui::SliderFloat3("Position", (float*)&position, 0.0f, 1000.0f);
                    ImGui::SliderFloat3("Rotation", (float*)&rotation, 0.0f, 360.0f);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Light"))
                {
                    ImGui::Text("Point, Directional");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Camera"))
                {
                    ImGui::Text("Camera aperture, shutter speed, iso");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Post process"))
                {
                    ImGui::Text("Post process");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Animation"))
                {
                    ImGui::Checkbox("Animation", &anim);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Environment map"))
                {
                    ImGui::Text("Environment map");
                    ImGui::TreePop();
                }        
                if (ImGui::TreeNode("Audio"))
                {
                    ImGui::Checkbox("Audio", &audio);
                    ImGui::TreePop();
                }
            }
            if (ImGui::CollapsingHeader("Application Info", ImGuiTreeNodeFlags_CollapsingHeader))
            {
                char* glInfos = (char*)glGetString(GL_VERSION);
                char* hardwareInfos = (char*)glGetString(GL_RENDERER);

                ImGui::Text("OpenGL Version :");
                ImGui::Text(glInfos);
                ImGui::Text("Hardware Informations :");
                ImGui::Text(hardwareInfos);
                ImGui::Text("\nFramerate %.2f FPS / Frametime %.4f ms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
            }
            if (ImGui::CollapsingHeader("About", ImGuiTreeNodeFlags_CollapsingHeader))
            {
                ImGui::Text("Panda Engine by Volodymyr Kadzhaia(ladroid)\n\nEmail: vkadzhaia@gmail.com\nTwitter: @ladroider");
            }
            if (open)
            {
                ImGui::OpenPopup("Open File");
            }
            if (fileDialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".obj"))
            {
                std::cout << fileDialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
                std::cout << fileDialog.selected_path << std::endl;    // The absolute path to the selected file
                ourModel.~Model();
                ourModel.setModel(fileDialog.selected_path);
            }
            if (anim)
            {
                std::cout << "Animation play" << std::endl;
            }
            ImGui::End();
        }

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position); // translate it down so it's at the center of the scene
        model = glm::scale(model, scale);	// it's a bit too big for our scene, so scale it down
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ourShader.setMat4("model", model);
        ourModel.draw(ourShader);

        //TODO:use sky shader
        glDepthFunc(GL_LEQUAL);
        skyShader.use();
        skyShader.setInt("skybox", 0);
        skyShader.setMat4("projection", projection);
        skyShader.setMat4("view", view);
        skybox->buildSkybox();
        skybox->renderSkybox();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.InputHandlerKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.InputHandlerKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.InputHandlerKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.InputHandlerKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.InputHandlerMouse(xoffset, yoffset);
    }
    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.InputHandlerMouseZoom(yoffset);
}

int main()
{
    init("example");
    return 0;
}