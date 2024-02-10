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
#include "PhysicsEngine.h"
#include "Skybox.h"
#include "Time.h"
#include "SkyboxMaterial.h"
#include "GraphicsRender.h"
#include "ImGui/PanelManager.h" 
#include "ImGui/EditorLayout.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "FrameBuffer.h"
#include "DebugModels.h"

#include "EntityManager/EntityManager.h"


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
	void PreRender();
	void Render();
	void PostRender();
	void Clear();

	void ProcessInput(GLFWwindow* window);
	

	FrameBuffer* frameBuffer;
	Camera* camera;
	bool isPlayMode = false;
private:
	GLFWwindow* window;
	
	

	//GraphicsRender render;

	Shader* defaultShader;
	Shader* solidColorShader;
	Shader* alphaBlendShader;
	Shader* alphaCutoutShader;

	Shader* stencilShader;
	Shader* skyboxShader;

	Skybox* skybox;

	PhysicsEngine PhysicsEngine;
	PanelManager* panelManager;

	 int windowWidth;
	 int  WindowHeight;
	 int selectedModelCount = 0;

	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 float scrollTime;

	 bool firstMouse;
	 bool isImguiPanelsEnable = false;

};

