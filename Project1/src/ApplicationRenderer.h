#pragma once
#include "Shader.h"
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
	void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");
	
	void Start();
	void Render();
	void Clear();

	void ProcessInput(GLFWwindow* window);
	



private:
	GLFWwindow* window;
	Camera camera;

	GraphicsRender render;
	LightManager lightManager;

	Shader* defaultShader;
	Shader* lightShader;

	 int windowWidth;
	 int  WindowHeight;


	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 bool firstMouse;

};

