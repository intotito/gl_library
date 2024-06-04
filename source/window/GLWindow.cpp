#include <window/GLWindow.hpp>

GLWindow::GLWindow(std::string title, int width, int height) : initialized(false), window(nullptr), title(title), 
renderer(new Renderer()), lastTime(0)
{
	Initialize(width, height);
}

GLWindow::~GLWindow()
{
    if (menu)
        delete menu;
    if (renderer)
        delete renderer;

}

void GLWindow::Initialize(int width, int height)
{
    /* Initialize the library */
    if (!glfwInit())
        assert(false, "GLEW Could not be initialized!");

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        assert(false, "Window could not be created!");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    //   glDisable(GL_LIGHTING);

    GLuint result = glewInit();
    if (result != GLEW_OK) {
        assert(false, "Error! Occured: Glew Cannot be Initialized...");
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    const char* glsl_version = "#version 130";
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //   ImGui_ImplG_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glfwSetWindowUserPointer(window, this);

    auto func = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            ((GLWindow*)glfwGetWindowUserPointer(window))->OnKeyPressed(window, key, scancode, action, mods);
        };
    glfwSetKeyCallback(window, func);

	initialized = true;
}

void GLWindow::OnStart()
{
    menu = new Test::TestMenu();
    menu->AddTest<Test::ClearColor>("Clear Color");
    menu->AddTest<Test::Scenery>("Scenery");
    menu->AddTest<Test::Texture2D>("Texture");
    menu->AddTest<Test::Cube>("Cube");
}

void GLWindow::Show()
{
    assert(initialized, "GLFW Not initialized, exiting ....");
    OnStart();
    lastTime = glfwGetTime() * 1000.0;
    double deltaTime = 0.0;
    int target_frame = 60;
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime() * 1000.0;
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        /* Poll for and process events */
        glfwPollEvents();

       

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        menu->OnRender(*renderer, deltaTime);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

           /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Update Event System*/
        menu->UpdateEvent(currentTime);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void GLWindow::OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {
 //       menu->FireKeyPressedEvent(key);
        menu->RegisterKeyEvent(key);
    } 
    else if (action == GLFW_RELEASE)
    {
        menu->UnRegisterKeyEvent(key);
        std::cout << "I Just released it" << std::endl;
    }
}


