#pragma once
#include "../Utilities/LookAt.h"
#include "../src/GraphicsRender.h"
#include "../Utilities/Lerp.h"

class CameraLerping
{

public:

	CameraLerping(Transform& camera);
	~CameraLerping();

	void Start();
	void Update();
	void End();


	void PositionOne(Model* lookatModel);
	void PositionTwo(Model* lookatModel);
	void PositionThree(Model* lookatModel);

private:

	LookAt* lookat;
	Transform Camtransform;
	



};

