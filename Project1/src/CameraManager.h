#pragma once
#include "Camera.h"


class CameraManager
{
public:
	
	static CameraManager& GetInstance();

	void AddCamera(Camera* camera);
	void RemoveCamera(Camera* camera);



private:

	std::vector<Camera*> listOfCameras;;

};

