#include <Renderer.hpp>
#include<buffers/IndexBuffer.hpp>
#include<VertexArray.hpp>
#include<shader/Shader.hpp>
#include<texture/Texture.hpp>
#include<vendor/glm/glm.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>

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
    GLuint result = glewInit();
    if (result != GLEW_OK) {
        std::cout << "Error! Occured: Glew Cannot be Initialized..." << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

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



    std::string fileName = "res/Shaders/Basic.shader";
    Shader* shader = new Shader(fileName);

/*
    VertexShader vertexShader(fileName);
    FragmentShader fragmentShader(fileName);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader.GetID());
    glAttachShader(program, fragmentShader.GetID());
    GLint linked;
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        int infoLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar* msg = (GLchar*)malloc(sizeof(GLchar) * infoLength);
        glGetProgramInfoLog(program, infoLength, NULL, msg);
        std::cout << "Error " << msg << std::endl;
        free(msg);
        glDeleteProgram(program);
    }
 */  

 /*/

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
*/
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

 //   va->LinkAttribute(vaa, vb);
 //   va->LinkAttribute(vaa1, vb);

    VertexBufferLayout* vbl = new VertexBufferLayout();
    vbl->Add(*vaa);
    vbl->Add(*vaa1);
    vbl->Add(*vaa2);

    va->AddLayout(*vbl, vb);


    IndexBuffer* ib = new IndexBuffer(indices, 6);

 //   glUseProgram(program);
    shader->Bind();

    GLfloat rColor[4] = {0.2f, 0.3f, 0.8f, 1.0f};
    GLfloat position[] = {0.15f, -0.25f, 0.0f};
    shader->SetUniform3fv("shift_Pos", position);
    shader->SetUniform4fv("rect_Color", rColor);
    shader->SetUniformMat4f("u_MVP", proj_mat);
 //   GLtry(int uLocation = glGetUniformLocation(shader.GetID(), "rect_Color"));
 //   ASSERT(uLocation != -1);
 //   GLtry(glUniform4fv(uLocation, 1, rColor));
 //   ".\res\textures\Camouflage.jpg"
    Texture* texture = new Texture("res/textures/Camo.png");
    texture->Bind(0);
    shader->SetUniform1i("u_Texture", 0);


    Renderer* renderer = new Renderer();


/*
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, vp);
*/    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        renderer->Draw(va, ib, shader);
 //       glDrawArrays(GL_TRIANGLES, 0, 6);
 //       GLtry(
 //           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)
 //       );
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    delete vb;
    delete ib;
    delete vaa;
    delete vaa1;
    delete shader;
    delete va;
    delete renderer;
//    free(ss->fragmentShader);
//    free(ss->vertexShader);
 //   free(ss);
    glfwTerminate();




    return 0;
}