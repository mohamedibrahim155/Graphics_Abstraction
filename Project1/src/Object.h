#pragma once
#include <string>
class Object
{
public :
	Object();
  //  ~Object();

	static unsigned int ID;
	


	bool isSelected = false;
	bool isEnabled = true;

	virtual void OnPropertyDraw() = 0;
	virtual void OnSceneDraw() = 0;
};

