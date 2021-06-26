#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct VertexBuffer {
	unsigned int vao;
	unsigned int shader;
	int size;
};

GLFWwindow* gl_init();
int gl_create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source);
VertexBuffer gl_create_vertex_buffer(std::vector<float> vertices, unsigned int shader);
void gl_draw_vertex_buffer(const VertexBuffer* buffer);