#include <Renderer.hpp>
#include<buffers/IndexBuffer.hpp>
#include<VertexArray.hpp>
#include<shader/Shader.hpp>
#include<texture/Texture.hpp>
#include<vendor/glm/glm.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>
#include<vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw.h>
#include<vendor/imgui/imgui_impl_opengl3.h>
#include <test/Test.hpp>
#include<test/ClearColor.hpp>
#include<test/TestMenu.hpp>
#include<test/Texture2D.hpp>
#include<test/Cube.hpp>

// #include <vendor/imgui/backends/imgui_impl_opengl3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

 //   glDisable(GL_LIGHTING);

    GLuint result = glewInit();
    if (result != GLEW_OK) {
        std::cout << "Error! Occured: Glew Cannot be Initialized..." << std::endl;
        return -1;
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

/*
    GLfloat positions[32] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
       
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLfloat vp[6] = {
        -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f,  -0.5f,
    };

    glm::mat4 proj_mat = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
 */   
/*
    std::string fileName = "res/Shaders/Basic.shader";
    Shader* shader = new Shader(fileName);

    VertexArray* va = new VertexArray();
    va->Bind();
    VertexArrayAttribute* vaa = new VertexArrayAttribute{
        0, 3, GL_FLOAT, GL_FALSE, "Position"
    };
    VertexArrayAttribute* vaa1 = new VertexArrayAttribute{
       1, 3, GL_FLOAT, GL_FALSE, "Color"
    };
    VertexArrayAttribute* vaa2 = new VertexArrayAttribute{
        2, 2, GL_FLOAT, GL_FALSE, "Texture_Coord"
    };
    VertexBuffer* vb = new VertexBuffer(positions, sizeof(GLfloat) * 32);


    VertexBufferLayout* vbl = new VertexBufferLayout();
    vbl->Add(vaa);
    vbl->Add(vaa1);
    vbl->Add(vaa2);

    va->AddLayout(vbl, vb);


    IndexBuffer* ib = new IndexBuffer(indices, 6);

    shader->Bind();

    GLfloat rColor[4] = {0.2f, 0.3f, 0.8f, 1.0f};
    GLfloat position[] = {0.0f, 0.0f, 0.0f};
    shader->SetUniform3fv("shift_Pos", position);
//    shader->SetUniform4fv("rect_Color", rColor);

    Texture* texture = new Texture("res/textures/Camo.png");
    texture->Bind(0);
   shader->SetUniform1i("u_Texture", 0);
 */

    Renderer* renderer = new Renderer();


//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    Test::TestMenu* testMenu = new Test::TestMenu();
    testMenu->AddTest<Test::ClearColor>("Clear Color");
    testMenu->AddTest<Test::Texture2D>("Texture");
    testMenu->AddTest<Test::Cube>("Cube");
    



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
       

   //     test->OnUpdate(0.0f);
  //      test->OnRender();
        /* Poll for and process events */
        glfwPollEvents();

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        testMenu->OnRender(*renderer);
  //      test->OnImGuiRender();


 /*           glm::mat4 view_mat = glm::mat4(1.0f);// , glm::vec3(cod[0], cod[1], cod[2]));
            glm::mat4 mvp_mat = proj_mat * view_mat;
            shader->SetUniformMat4f("u_MVP", mvp_mat);
            renderer->Draw(va, ib, shader);
*/
        


            
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
     //   ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        
    }
 //   delete vb;
 //   delete ib;
 //   delete vaa;
//    delete vaa1;
 //   delete shader;
//    delete va;
    delete renderer;
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
//    free(ss->fragmentShader);
//    free(ss->vertexShader);
 //   free(ss);
    glfwTerminate();




    return 0;
}