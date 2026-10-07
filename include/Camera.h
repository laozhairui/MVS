#ifndef CAMERA_H
#define CAMERA_H
#include <MVCameraControl.h>
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
private:
	MV_CC_DEVICE_INFO_LIST deviceList_;
	void* handle_;
	bool deviceOpened_;
	bool grabbing_;
	std::string lastError_;
};
#endif
