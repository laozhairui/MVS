#ifndef CAMERA_H
#define CAMERA_H
#include <string>
class Camera
{
public:
	Camera();
	~Camera();
	bool enumerateDevices();
	bool createHandle(int deviceId=0);
	bool open();
	bool startGrabbing();
	bool getFrame();
	void stopGrabbing();
	void close();
	bool isOpened() const;//const ai
	std::string lastError() const; 
};
#endif
