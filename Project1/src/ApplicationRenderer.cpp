#include"ApplicationRenderer.h"



ApplicationRenderer::ApplicationRenderer()
{
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
    
    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }




  
    defaultShader = new Shader("Shaders/Light_VertexShader.vert", "Shaders/Light_FragmentShader.frag");
    lightShader = new Shader("Shaders/lighting.vert", "Shaders/lighting.frag");
    StencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag");
   
    SkyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");


    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");
    render.AssignStencilShader(StencilShader);
    camera.transform.position = glm::vec3(0, 0, - 1.0f);
}



std::vector<ModelData> ApplicationRenderer::loadModelDataFromFile(const std::string& filePath)
{

    std::ifstream file(filePath);
    std::vector<ModelData> modelData;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return modelData;
    }
    else
    {
        std::cerr << "File Opened >>>>>>>>>>>>>>>>>>>>>>>>>>>: " << filePath << std::endl;

    }

    std::string line;
    ModelData currentModel;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "ModelPath:") 
        {
            iss >> currentModel.path;
        }
        else if (token == "ModelPosition:") {
            iss >> currentModel.position.x >> currentModel.position.y >> currentModel.position.z;
        }       
        else if (token == "ModelRotation:") {

            iss >> currentModel.rotation.x >> currentModel.rotation.y >> currentModel.rotation.z;

        }
      
        else if (token == "TexturePath:") 
        {

            iss >> currentModel.texturePath;

        }
        else if (token == "Transperency:")
        {

            iss >> currentModel.isTrans;

        }
        
        else if (token == "Cutoff:")
        {

            iss >> currentModel.isCutoff;

        }
      
        else if (token == "ModelScale:") {
            iss >> currentModel.scale.x >> currentModel.scale.y >> currentModel.scale.z;
            modelData.push_back(currentModel);
        }
    }

    file.close();
    return modelData;
}


void ApplicationRenderer::Start()
{
    // GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glDepthFunc(GL_LESS));
    GLCALL(glEnable(GL_STENCIL_TEST));
    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    skybox = new Skybox();

    skybox->AssignSkyboxShader(SkyboxShader);
    skybox->SkyboxPrerender();


    render.AssignCamera(&camera);

    Model* Sphere = new Model((char*)"Models/DefaultSphere/Sphere_1_unit_Radius.ply", true);

    Model* Pokeball = new Model((char*)"Models/Pokeball/pokeball.obj", true);
    Model* Pokeball2 = new Model((char*)"Models/Pokeball/pokeball.obj", true);



    Sphere->transform.position.x += 2;
    Pokeball->transform.position.x -= 2;



    Pokeball2->transform.position.x -= 5;
    Pokeball2->transform.position.y -= 0.3f;
    Pokeball2->transform.SetScale(glm::vec3(1.2f));
    Pokeball2->transform.position = Pokeball->transform.position;
    Pokeball2->transform.SetScale(glm::vec3(0.5f));




   


#pragma region MODELS


    modelData = loadModelDataFromFile("Model.txt");

    Model* Walls = new Model(modelData[0].path);
    Walls->transform.SetPosition(glm::vec3(modelData[0].position));
    Walls->transform.SetRotation(glm::vec3(modelData[0].rotation));
    Walls->transform.SetScale(glm::vec3(modelData[0].scale));
    render.AddModelsAndShader(Walls, defaultShader);

    Model* TableSofa = new Model(modelData[1].path);
    TableSofa->transform.SetPosition(glm::vec3(modelData[1].position));
    TableSofa->transform.SetRotation(glm::vec3(modelData[1].rotation));
    TableSofa->transform.SetScale(glm::vec3(modelData[1].scale));
    render.AddModelsAndShader(TableSofa, defaultShader);

    Model* Sofas = new Model(modelData[2].path);
    Sofas->transform.SetPosition(glm::vec3(modelData[2].position));
    Sofas->transform.SetRotation(glm::vec3(modelData[2].rotation));
    Sofas->transform.SetScale(glm::vec3(modelData[2].scale));
    render.AddModelsAndShader(Sofas, defaultShader);

    Model* Floor = new Model(modelData[3].path);
    Floor->transform.SetPosition(glm::vec3(modelData[3].position));
    Floor->transform.SetRotation(glm::vec3(modelData[3].rotation));
    Floor->transform.SetScale(glm::vec3(modelData[3].scale));
    render.AddModelsAndShader(Floor, defaultShader);

    Model* Deco = new Model(modelData[4].path);
    Deco->transform.SetPosition(glm::vec3(modelData[4].position));
    Deco->transform.SetRotation(glm::vec3(modelData[4].rotation));
    Deco->transform.SetScale(glm::vec3(modelData[4].scale));
    render.AddModelsAndShader(Deco, defaultShader);

    Model* Door = new Model(modelData[5].path);
    Door->transform.SetPosition(glm::vec3(modelData[5].position));
    Door->transform.SetRotation(glm::vec3(modelData[5].rotation));
    Door->transform.SetScale(glm::vec3(modelData[5].scale));
    render.AddModelsAndShader(Door, defaultShader);

    Model* Deco2 = new Model(modelData[6].path);
    Deco2->transform.SetPosition(glm::vec3(modelData[6].position));
    Deco2->transform.SetRotation(glm::vec3(modelData[6].rotation));
    Deco2->transform.SetScale(glm::vec3(modelData[6].scale));
    render.AddModelsAndShader(Deco2, defaultShader);

    Model* Desk = new Model(modelData[7].path);
    Desk->transform.SetPosition(glm::vec3(modelData[7].position));
    Desk->transform.SetRotation(glm::vec3(modelData[7].rotation));
    Desk->transform.SetScale(glm::vec3(modelData[7].scale));
    Desk->meshes[0]->textures[0]->LoadTexture(modelData[7].texturePath.c_str(), "diffuse");
    render.AddModelsAndShader(Desk, defaultShader);

    Model* Desk2 = new Model(modelData[8].path);
    Desk2->transform.SetPosition(glm::vec3(modelData[8].position));
    Desk2->transform.SetRotation(glm::vec3(modelData[8].rotation));
    Desk2->transform.SetScale(glm::vec3(modelData[8].scale));
    render.AddModelsAndShader(Desk2, defaultShader);

    Model* TeaTable = new Model(modelData[9].path);
    TeaTable->transform.SetPosition(glm::vec3(modelData[9].position));
    TeaTable->transform.SetRotation(glm::vec3(modelData[9].rotation));
    TeaTable->transform.SetScale(glm::vec3(modelData[9].scale));
    render.AddModelsAndShader(TeaTable, defaultShader);

    Model* FloorMat = new Model(modelData[10].path);
    FloorMat->transform.SetPosition(glm::vec3(modelData[10].position));
    FloorMat->transform.SetRotation(glm::vec3(modelData[10].rotation));
    FloorMat->transform.SetScale(glm::vec3(modelData[10].scale));
    render.AddModelsAndShader(FloorMat, defaultShader);

    Model* Fireplace = new Model(modelData[11].path);
    Fireplace->transform.SetPosition(glm::vec3(modelData[11].position));
    Fireplace->transform.SetRotation(glm::vec3(modelData[11].rotation));
    Fireplace->transform.SetScale(glm::vec3(modelData[11].scale));
    render.AddModelsAndShader(Fireplace, defaultShader);

    Model* Photos = new Model(modelData[12].path);
    Photos->transform.SetPosition(glm::vec3(modelData[12].position));
    Photos->transform.SetRotation(glm::vec3(modelData[12].rotation));
    Photos->transform.SetScale(glm::vec3(modelData[12].scale));
    render.AddModelsAndShader(Photos, defaultShader);

    Model* Music = new Model(modelData[13].path);
    Music->transform.SetPosition(glm::vec3(modelData[13].position));
    Music->transform.SetRotation(glm::vec3(modelData[13].rotation));
    Music->transform.SetScale(glm::vec3(modelData[13].scale));
    render.AddModelsAndShader(Music, defaultShader);

    Model* CD = new Model(modelData[14].path);
    CD->transform.SetPosition(glm::vec3(modelData[14].position));
    CD->transform.SetRotation(glm::vec3(modelData[14].rotation));
    CD->transform.SetScale(glm::vec3(modelData[14].scale));
    render.AddModelsAndShader(CD, defaultShader);

    Model* Roof = new Model();
    Texture* starTexture = new Texture();
    starTexture->LoadTexture(modelData[15].texturePath.c_str(), "starAlpha");
    Roof->loadModel(modelData[15].path);
    Roof->meshes[0]->textures.push_back(starTexture);
    Roof->meshes[0]->SetColorAlpha(true);
    Roof->transform.SetPosition(glm::vec3(modelData[15].position));
    Roof->transform.SetRotation(glm::vec3(modelData[15].rotation));
    Roof->transform.SetScale(glm::vec3(modelData[15].scale));
    render.AddModelsAndShader(Roof, defaultShader);

    Model* Symbols = new Model(modelData[16].path);
    Symbols->transform.SetPosition(glm::vec3(modelData[16].position));
    Symbols->transform.SetRotation(glm::vec3(modelData[16].rotation));
    Symbols->transform.SetScale(glm::vec3(modelData[16].scale));
    render.AddModelsAndShader(Symbols, defaultShader);

    Model* WallLights = new Model();
    //Texture* starTexture1 = new Texture();
    //starTexture1->LoadTexture(modelData[17].texturePath.c_str(), "starAlpha");
    WallLights->loadModel(modelData[17].path);
    //WallLights->meshes[0]->textures.push_back(starTexture1);
    //WallLights->meshes[0]->SetColorAlpha(true);
    WallLights->transform.SetPosition(glm::vec3(modelData[17].position));
    WallLights->transform.SetRotation(glm::vec3(modelData[17].rotation));
    WallLights->transform.SetScale(glm::vec3(modelData[17].scale));
    render.AddModelsAndShader(WallLights, defaultShader);

    Model* Grass = new Model(modelData[18].path, true, modelData[18].isTrans, modelData[18].isCutoff);
    Grass->transform.SetPosition(glm::vec3(modelData[18].position));
    Grass->transform.SetRotation(glm::vec3(modelData[18].rotation));
    Grass->transform.SetScale(glm::vec3(modelData[18].scale));
    render.AddModelsAndShader(Grass, defaultShader);

    Model* Window = new Model();
    Window->alphaMask = new Texture();
    Window->isTransparant = modelData[19].isTrans;
    Window->isCutOut = modelData[19].isCutoff;
    Window->alphaMask->LoadTexture(modelData[19].texturePath.c_str(), "alphaMask");
    Window->loadModel(modelData[19].path);
    Window->transform.SetPosition(glm::vec3(modelData[19].position));
    Window->transform.SetRotation(glm::vec3(modelData[19].rotation));
    Window->transform.SetScale(glm::vec3(modelData[19].scale));
    render.AddTransparentModels(Window, defaultShader);

    Model* Window2 = new Model();
    Window2->alphaMask = new Texture();
    Window2->isTransparant = modelData[20].isTrans;
    Window2->isCutOut = modelData[20].isCutoff;
    Window2->alphaMask->LoadTexture(modelData[20].texturePath.c_str(), "alphaMask");
    Window2->loadModel(modelData[20].path);
    Window2->transform.SetPosition(glm::vec3(modelData[20].position));
    Window2->transform.SetRotation(glm::vec3(modelData[20].rotation));
    Window2->transform.SetScale(glm::vec3(modelData[20].scale));
    render.AddTransparentModels(Window2, defaultShader);

    Model* scroll = new Model(modelData[21].path);
    scroll->transform.SetPosition(glm::vec3(modelData[21].position));
    scroll->transform.SetRotation(glm::vec3(modelData[21].rotation));
    scroll->transform.SetScale(glm::vec3(modelData[21].scale));
    scroll->meshes[0]->TextureScrolling(true);
    render.AddModelsAndShader(scroll, defaultShader);

    Model* plant = new Model(modelData[22].path);
    plant->alphaMask = new Texture();
    plant->meshes[0]->SetCutOff(modelData[22].isCutoff);
    plant->alphaMask->LoadTexture(modelData[22].texturePath.c_str(), "alphaMask");
    plant->meshes[0]->textures.push_back(plant->alphaMask);
    plant->meshes[1]->textures.clear();
    Texture* mesh2Tex = new Texture();
    mesh2Tex->LoadTexture(modelData[23].texturePath.c_str(), "diffuse");
    plant->meshes[1]->textures.push_back(mesh2Tex);
    plant->transform.SetPosition(glm::vec3(modelData[22].position));
    plant->transform.SetRotation(glm::vec3(modelData[22].rotation));
    render.AddModelsAndShader(plant, defaultShader);

    plant2 = new Model(modelData[24].path);
    plant2->alphaMask = new Texture();
    plant2->meshes[0]->SetCutOff(modelData[24].isCutoff);
    plant2->alphaMask->LoadTexture(modelData[24].texturePath.c_str(), "alphaMask");
    plant2->meshes[0]->textures.push_back(plant2->alphaMask);
    plant2->meshes[1]->textures.clear();
    Texture* mesh3Tex = new Texture();
    mesh3Tex->LoadTexture(modelData[25].texturePath.c_str(), "diffuse");
    plant2->meshes[1]->textures.push_back(mesh3Tex);
    plant2->transform.SetPosition(glm::vec3(modelData[24].position));
    plant2->transform.SetRotation(glm::vec3(modelData[24].rotation));
    render.AddModelsAndShader(plant2, defaultShader);


    Model* Jar = new Model(modelData[38].path);
    Jar->alphaMask = new Texture();
    Jar->meshes[1]->SetTransparency(true);
    Jar->alphaMask->LoadTexture(modelData[38].texturePath.c_str(), "alphaMask");
    Jar->meshes[1]->textures.push_back(Jar->alphaMask); 
    Texture* mesh3Tex2 = new Texture();
    mesh3Tex2->LoadTexture(modelData[38].texturePath.c_str(), "diffuse");
    Jar->meshes[1]->textures.push_back(mesh3Tex2);
    Jar->transform.SetPosition(glm::vec3(modelData[38].position));
    Jar->transform.SetRotation(glm::vec3(modelData[38].rotation));
    Jar->transform.SetScale(glm::vec3(modelData[38].scale));
    render.AddTransparentModels(Jar, defaultShader);

    Model* Jar2 = new Model(*Jar);
    Jar2->transform.SetPosition(glm::vec3(modelData[39].position));
    Jar2->transform.SetRotation(glm::vec3(modelData[39].rotation));
    Jar2->transform.SetScale(glm::vec3(modelData[39].scale));
    render.AddTransparentModels(Jar2, defaultShader);

    Model* Jar3 = new Model(*Jar);
    Jar3->transform.SetPosition(glm::vec3(modelData[40].position));
    Jar3->transform.SetRotation(glm::vec3(modelData[40].rotation));
    Jar3->transform.SetScale(glm::vec3(modelData[40].scale));
    render.AddTransparentModels(Jar3, defaultShader);
    
#pragma endregion


#pragma region LIGHT MODELS


    Model* dir = new Model();
    Model* spotlight = new Model(*Sphere);
    spotlight->transform.SetPosition(glm::vec3(modelData[26].position));
    spotlight->transform.SetRotation(glm::vec3(modelData[26].rotation));
    spotlight->transform.SetScale(glm::vec3(modelData[26].scale));

    Model* spotlight2 = new Model(*Sphere);
    spotlight2->transform.SetPosition(glm::vec3(modelData[27].position));
    spotlight2->transform.SetRotation(glm::vec3(modelData[27].rotation));
    spotlight2->transform.SetScale(glm::vec3(modelData[27].scale));

    Model* spotlight3 = new Model(*Sphere);
    spotlight3->transform.SetPosition(glm::vec3(modelData[28].position));
    spotlight3->transform.SetRotation(glm::vec3(modelData[28].rotation));
    spotlight3->transform.SetScale(glm::vec3(modelData[28].scale));

    Model* spotlight4 = new Model(*Sphere);
    spotlight4->transform.SetPosition(glm::vec3(modelData[29].position));
    spotlight4->transform.SetRotation(glm::vec3(modelData[29].rotation));
    spotlight4->transform.SetScale(glm::vec3(modelData[29].scale));

    Model* spotlight5 = new Model(*Sphere);
    spotlight5->transform.SetPosition(glm::vec3(modelData[30].position));
    spotlight5->transform.SetRotation(glm::vec3(modelData[30].rotation));
    spotlight5->transform.SetScale(glm::vec3(modelData[30].scale));

    Model* spotlight6 = new Model(*Sphere);
    spotlight6->transform.SetPosition(glm::vec3(modelData[31].position));
    spotlight6->transform.SetRotation(glm::vec3(modelData[31].rotation));
    spotlight6->transform.SetScale(glm::vec3(modelData[31].scale));

#pragma endregion



#pragma region LOOKAT TRANSFORMS

    CamPlaceholder = new Model(modelData[32].path);
    CamPlaceholder->transform.SetPosition(glm::vec3(modelData[32].position));

    plantLookat = new Model(*CamPlaceholder);
    plantLookat->transform.SetPosition(glm::vec3(modelData[33].position));

    firePlaceLookat = new Model(*CamPlaceholder);
    firePlaceLookat->transform.SetPosition(glm::vec3(modelData[34].position));

    CamPlaceholder2 = new Model(*CamPlaceholder);
    CamPlaceholder2->transform.SetPosition(glm::vec3(modelData[35].position));

    CamPlaceholder3 = new Model(*CamPlaceholder);
    CamPlaceholder3->transform.SetPosition(glm::vec3(modelData[36].position));

    RoofPlaceLookat = new Model(*CamPlaceholder);
    RoofPlaceLookat->transform.SetPosition(glm::vec3(modelData[37].position));

#pragma endregion




#pragma region LIGHTS

    Light directionLight;
    directionLight.lightType = LightType::DIRECTION_LIGHT;
    directionLight.lightModel = dir;
    directionLight.ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    directionLight.diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    directionLight.specular = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);



    Light spot;
    spot.lightType = LightType::SPOT_LIGHT;
    spot.lightModel = spotlight;
    spot.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot.cutOffAngle = 15;
    spot.outerCutOffAngle = 35;

    Light spot2;
    spot2.lightType = LightType::SPOT_LIGHT;
    spot2.lightModel = spotlight2;
    spot2.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot2.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot2.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot2.cutOffAngle = 15;
    spot2.outerCutOffAngle = 35;

    Light spot3;
    spot3.lightType = LightType::SPOT_LIGHT;
    spot3.lightModel = spotlight3;
    spot3.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot3.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot3.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot3.cutOffAngle = 15;
    spot3.outerCutOffAngle = 35;

    Light spot4;
    spot4.lightType = LightType::SPOT_LIGHT;
    spot4.lightModel = spotlight4;
    spot4.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot4.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot4.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot4.cutOffAngle = 15;
    spot4.outerCutOffAngle = 35;

    Light spot5;
    spot5.lightType = LightType::SPOT_LIGHT;
    spot5.lightModel = spotlight5;
    spot5.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot5.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot5.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot5.cutOffAngle = 15;
    spot5.outerCutOffAngle = 35;

    Light spot6;
    spot6.lightType = LightType::SPOT_LIGHT;
    spot6.lightModel = spotlight6;
    spot6.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot6.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot6.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    spot6.cutOffAngle = 15;
    spot6.outerCutOffAngle = 35;


#pragma endregion


  

#pragma region RENDERER

    render.selectedModel = nullptr;

    render.AddModelsAndShader(dir, lightShader);
    render.AddModelsAndShader(spotlight, lightShader);
    render.AddModelsAndShader(spotlight2, lightShader);
    render.AddModelsAndShader(spotlight3, lightShader);
    render.AddModelsAndShader(spotlight4, lightShader);
    render.AddModelsAndShader(spotlight5, lightShader);
    render.AddModelsAndShader(spotlight6, lightShader);



    //LightRenderer
    lightManager.AddNewLight(directionLight);
    lightManager.AddNewLight(spot);
    lightManager.AddNewLight(spot2);
    lightManager.AddNewLight(spot3);
    lightManager.AddNewLight(spot4);
    lightManager.AddNewLight(spot5);
    lightManager.AddNewLight(spot6);
    lightManager.SetUniforms(defaultShader->ID);


    defaultShader->Bind();
    defaultShader->setInt("skybox", 0);

#pragma endregion

#pragma region ASSIGNING

    moveCam.AssignCam(&camera);

    lookAt = new LookAt(camera.transform, plantLookat);
    lookAtFirePlace = new LookAt(camera.transform, firePlaceLookat);
    lookAtRoof = new LookAt(camera.transform, RoofPlaceLookat);
    lookAtJar = new LookAt(camera.transform, Jar3);

#pragma endregion

   

    
}

void ApplicationRenderer::PreRender()
{

}

void ApplicationRenderer::Render()
{
    Start();
    Material material(128.0f);
    glm::vec3 pos(5, 0, 0);
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window))
    {
        Clear();


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        scrollTime += deltaTime;

        ProcessInput(window);

        glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)WindowHeight, 0.1f, 100.0f);
        glm::mat4 _view = camera.GetViewMatrix();
        glm::mat4 _skyboxview = glm::mat4(glm::mat3(camera.GetViewMatrix()));


        PreRender(); //Update call BEFORE  DRAW

        glDepthFunc(GL_LEQUAL);
        SkyboxShader->Bind();
        SkyboxShader->setMat4("view", _skyboxview);
        SkyboxShader->setMat4("projection", _projection);

        skybox->Skyboxrender();
        glDepthFunc(GL_LESS); 


        defaultShader->Bind();
       // material.SetMaterialProperties(*defaultShader);
     //   lightManager.UpdateUniformValuesToShader(defaultShader);
        lightManager.UpdateUniformValues(defaultShader->ID);
       

         defaultShader->setMat4("projection", _projection);
         defaultShader->setMat4("view", _view);
         defaultShader->setVec3("viewPos", camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
         defaultShader->setFloat("time", scrollTime);

         if (isRenderchange)
         {
             defaultShader->setBool("isDepthBuffer", true);

         }
         else
         {
             defaultShader->setBool("isDepthBuffer", false);

         }

         lightShader->Bind();
         lightShader->setVec3("objectColor", glm::vec3(1, 1, 1));
         lightShader->setMat4("projection", _projection);
         lightShader->setMat4("view", _view);

         StencilShader->Bind();
         StencilShader->setMat4("projection", _projection);
         StencilShader->setMat4("view", _view);

       
         
        
         render.Draw();

         if (plantCam)
         {
             timeStep += deltaTime / time;
            
             camera.transform.SetPosition(Lerp(camera.transform.position, CamPlaceholder->transform.position, timeStep));

             lookAt->CameraUpdate();

         }

         if (firePlaceCam)
         {
             timeStep += deltaTime / time;

             camera.transform.SetPosition(Lerp(camera.transform.position, CamPlaceholder2->transform.position, timeStep));

             lookAtFirePlace->CameraUpdate();

         }

         if (roofCam)
         {
             timeStep += deltaTime / time;

             camera.transform.SetPosition(Lerp(camera.transform.position, CamPlaceholder3->transform.position, timeStep));

             lookAtRoof->CameraUpdate();

         }


         if (jarCam)
         {
             timeStep += deltaTime / time;

             camera.transform.SetPosition(Lerp(camera.transform.position, glm::vec3(modelData[41].position), timeStep));

             lookAtJar->CameraUpdate();

         }
       
        std::cout << "camera Pos : " << camera.transform.position.x << " , " << camera.transform.position.y << " , " << camera.transform.position.z << std::endl;



         PostRender(); // Update Call AFTER  DRAW

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void ApplicationRenderer::PostRender()
{
   // glDisable(GL_BLEND);

 //   PhysicsEngine.UpdatePhysics(deltaTime);


  

}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed= 14;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime * cameraSpeed);

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime * cameraSpeed);

    }


}

 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {

            
             std::cout << "V pressed" << std::endl;

             std::vector<Model*> listOfModels = render.GetModelList();
            


             selectedModelCount++;

             if (selectedModelCount > listOfModels.size()-1)
             {
                 selectedModelCount = 0;
             }

            
             render.selectedModel = listOfModels[selectedModelCount];


         }

         if (key == GLFW_KEY_X && action == GLFW_PRESS)
         {
             render.selectedModel = nullptr;

         }
         if (key == GLFW_KEY_1 && action == GLFW_PRESS)
         {
              lerpValue = 0;
                timeStep = 0;
             plantCam = !plantCam;
             firePlaceCam = false;
             roofCam = false;
             jarCam = false;
         }
         if (key == GLFW_KEY_2 && action == GLFW_PRESS)
         {

             lerpValue = 0;
             timeStep = 0;

             plantCam = false;
             roofCam = false;
             jarCam = false;
             firePlaceCam = !firePlaceCam;
           

              
         }
         if (key == GLFW_KEY_3 && action == GLFW_PRESS)
         {

             lerpValue = 0;
             timeStep = 0;

             plantCam = false;
             firePlaceCam = false;
             jarCam = false;
             roofCam = !roofCam;

             
         }

         if (key == GLFW_KEY_4 && action == GLFW_PRESS)
         {

             lerpValue = 0;
             timeStep = 0;

             plantCam = false;
             firePlaceCam = false;;
             roofCam = false;
             jarCam = !jarCam;
            
         }

         if (key == GLFW_KEY_UP && action == GLFW_PRESS)
         {
             changeUVy += 1;
             defaultShader->setFloat("uvControly", changeUVy);


         }
         if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
         {


             changeUVy -= 1;
             defaultShader->setFloat("uvControly", changeUVy);

         }
         if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
         {

             changeUVx -= 1;
             defaultShader->setFloat("uvControlx", changeUVx);


         }
         if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
         {


             changeUVx += 1;
             defaultShader->setFloat("uvControlx", changeUVx);

         }

         if (key == GLFW_KEY_R && action == GLFW_PRESS)
         {

             defaultShader->Bind();
             changeUVx = 1;
             changeUVy = 1;
             defaultShader->setFloat("uvControlx", changeUVx);
             defaultShader->setFloat("uvControly", changeUVy);

         }

         if (key == GLFW_KEY_F && action == GLFW_PRESS)
         {

             isRenderchange = !isRenderchange;


         }



         
         
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
        if (firstMouse)
        {

        }

         if (firstMouse)
         {
             lastX = xpos;
             lastY = ypos;
             firstMouse = false;
         }
     
         float xoffset = xpos - lastX;
         float yoffset = lastY - ypos;
     
         lastX = xpos;
         lastY = ypos;
     
         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
         {
             camera.ProcessMouseMovement(xoffset, yoffset);
         }
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     camera.ProcessMouseScroll(static_cast<float>(yoffset));
 }
