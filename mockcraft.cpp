#include <iostream>
#include <vector>
#include "gl.h"
#include "logger.h"

const char* VERTEX_SHADER_SOURCE =
    "#version 330 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main() {\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\0";

const char* FRAGMENT_SHADER_SOURCE_ORANGE =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char* FRAGMENT_SHADER_SOURCE_YELLOW =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.5f, 1.0f);\n"
    "}\0";

const char* FRAGMENT_SHADER_SOURCE_BLUE =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(0.1f, 0.5f, 1.0f, 1.0f);\n"
    "}\0";

int main()
{
    logger_init();
    GLFWwindow* window = gl_init();
    if (window == nullptr) {
        return -1;
    }

    int shader_program_orange = gl_create_shader_program(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE_ORANGE);
    if (shader_program_orange < 0) {
        return -1;
    }

    int shader_program_yellow = gl_create_shader_program(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE_YELLOW);
    if (shader_program_yellow < 0) {
        return -1;
    }

    int shader_program_blue = gl_create_shader_program(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE_BLUE);
    if (shader_program_blue < 0) {
        return -1;
    }

    // Set up vertex buffers
    std::vector<float> vertices1 = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f,  0.5f, 0.0f,  // top left
    };

    std::vector<float> vertices2 = {
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<float> vertices3 = {
        0.25f, -0.25f, 0.0f,  // bottom right
       -0.25f, -0.25f, 0.0f,  // bottom left
       -0.25f,  0.25f, 0.0f,  // top left
        0.25f,  0.25f, 0.0f,  // top right
        0.25f, -0.25f, 0.0f,  // bottom right
       -0.25f,  0.25f, 0.0f   // top left
    };

    VertexBuffer buffer1 = gl_create_vertex_buffer(vertices1, shader_program_orange);
    VertexBuffer buffer2 = gl_create_vertex_buffer(vertices2, shader_program_yellow);
    VertexBuffer buffer3 = gl_create_vertex_buffer(vertices3, shader_program_blue);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        gl_draw_vertex_buffer(&buffer1);
        gl_draw_vertex_buffer(&buffer2);
        gl_draw_vertex_buffer(&buffer3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //glDeleteVertexArrays(2, vaos);
    //glDeleteBuffers(2, vbos);

    glfwTerminate();
    return 0;
}