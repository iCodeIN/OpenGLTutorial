#include <iostream>
#include <string>
#include "gl.h"
#include "logger.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* gl_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mockcraft", NULL, NULL);
    if (window == NULL) {
        logger_write("Failed to create GLFW window!");
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logger_write("Failed to initialize GLAD!");
        return nullptr;
    }

    return window;
}

int gl_create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source)
{
    // Set up vertex shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, log);
        logger_write("Error compiling vertex shader: ");
        logger_write(log);
        return -1;
    }

    // Set up fragment shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    success = false;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, log);
        logger_write("Error compiling fragment shader: ");
        logger_write(log);
        return -1;
    }

    // Link vertex and fragment shaders
    int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    success = false;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, log);
        logger_write("Error linking shader program: ");
        logger_write(log);
        return -1;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}

VertexBuffer gl_create_vertex_buffer(std::vector<float> vertices, unsigned int shader)
{
    VertexBuffer buffer;
    unsigned int vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    buffer.vao = vao;
    buffer.shader = shader;
    buffer.size = vertices.size();

    return buffer;
}

void gl_draw_vertex_buffer(const VertexBuffer* buffer)
{
    glUseProgram(buffer->shader);
    glBindVertexArray(buffer->vao);
    glDrawArrays(GL_TRIANGLES, 0, buffer->size);
}