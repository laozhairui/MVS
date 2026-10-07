#ifndef CAMERA_H
#define CAMERA_H
#include <MVCameraControl.h>
#include <string>
#include <opencv2/core.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	bool enumerateDevices();
	bool createHandle(int deviceId=0);
	bool open();
	bool startGrabbing();
	bool getFrame(cv::Mat& image);
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
