#include "CameraManager.h"

CameraManager& CameraManager::GetInstance()
{
	static CameraManager instance;
	return instance;
}

void CameraManager::AddCamera(Camera* camera)
{
	listOfCameras.push_back(camera);
}

void CameraManager::RemoveCamera(Camera* camera)
{
	std::vector<Camera*> ::iterator it = std::remove(listOfCameras.begin(), listOfCameras.end(), camera);
	listOfCameras.erase(it, listOfCameras.end());
}
