#pragma once
#include "Shader.h"
#include <glad/glad.h>


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Application.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "VertexArray.h"
#include  "model.h"

#include "material.h"
#include "Light.h"

#include "Transform.h"
#include"LightManager.h"
#include "Random.h"


#include "GraphicsRender.h"
class ApplicationRenderer
{
public:
	ApplicationRenderer();
	~ApplicationRenderer();

	static void SetViewPort(GLFWwindow* window, int width, int height);
	void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");
	
	void Start();
	void Render();
	void Clear();

	void ProcessInput(GLFWwindow* window);
	



private:
	GLFWwindow* window;
	GraphicsRender render;
	Camera camera;

	Shader* defaultShader;

	 int windowWidth;
	 int  WindowHeight;


	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 bool firstMouse;

};

