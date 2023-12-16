#include "CameraLerping.h"

CameraLerping::CameraLerping(Transform& camera)
{

	this->Camtransform = camera;
}

CameraLerping::~CameraLerping()
{
}

void CameraLerping::Start()
{
	

}

void CameraLerping::Update()
{

	lookat->CameraUpdate();
	

}

void CameraLerping::End()
{
}

void CameraLerping::PositionOne(Model* lookatModel)
{
	lookat = new LookAt(Camtransform, lookatModel);
	Camtransform.SetPosition(lookatModel->transform.position);
}

void CameraLerping::PositionTwo(Model* lookatModel)
{
	lookat = new LookAt(Camtransform, lookatModel);

}

void CameraLerping::PositionThree(Model* lookatModel)
{
	lookat = new LookAt(Camtransform, lookatModel);

}
