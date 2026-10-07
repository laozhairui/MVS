#include "Camera.h"
Camera::Camera
{
	handle_=nullptr;
	deviceOpened_=false;
	grabbing_=false;	
}
/*ai Member Initializer List
Camera::camera
	: handle_(nullptr)
	  deviceOpened_(false)
	  grabbing_(false)
{
}
*/
Camera::~Camera()
{
	close();
}
bool Camera::enumerateDevices()
{
	lastError_.clear(); 
	int ret=MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE,&deviceList_);
	if(ret!=MV_OK)
	{
		lastError_="wrong on enumerateDevices";
		return false;
	}
	if(deviceList_.nDeviceNum==0)//nDeviceNum
	{
		lastError_="can't find camera";
		return false;
	}
	return true;
}
bool Camera::creatHandle(int deviceId)
{
	lastError_.clear();
	if(deviceId<0 || deviced>=static_cast<int>(deviceList_.nDeviceNum))//static
	{
		lastError_="wrong camera id";
		return false;
	}
	MV_CC_DEVICE_INFO* deviceInfo=deviceList_.pDeviceInfo[deviceId];
	if(deviceInfo==nullptr)
	{
		lastError_="infomation is null";
		return false;
	} 
	int ret=MV_CC_CreateHandle(&handle_,deviceInfo);
	if(ret!=MV_OK)
	{
		lastError_="can't creat handle";
		return false;
	}
	return true;
}
bool Camera::open()
{
	lastError_.clear();
	if(handle_==nullptr)
	{
		lastError_="don't create handle";
		return false;
	}
	int ret =MV_CC_OpenDevice(handle_);
	if(ret!=MV_OK)
	{
		lastError_="open failed";
		return false;
	}
	deviceOpened_=true;
	return true;
}
bool Camera::startGrabbing()
{
	lastError_.clear();
	if (!deviceOpened_)
	{
		lastError_="camera is close";
		return false;
	}
	int ret =MV_CC_StartGrabbing(handle_);
	if(ret!=MV_OK)
	{
		lastError_="grabbing failed";
		return false;
	}
	grabbing_=true;
	return true;
}
void Camera::stopGrabbing()
{
	lastError_.clear();
	if(!grabbing_)	return;
	int ret =MV_CC_StopGrabbing();
	if(ret!=MV_OK)
	{
		lastError_="stop grabbing failed";
		return;
	}
	grabbing_=false;
}
void Camera::close()
{
	if(grabbing_)	stopGrabbing();
	if(deviceOpened_)
	{
		MV_CC_CloseDevice(handle_);
		deviceOpened=false;
	}
	if(handle_!=nullptr)
	{
		MV_CC_DestoryHandle(handle_);
		handle_=nullptr;
	}
}
bool Camera::isOpened()const	return deviceOpened_;
bool Camera::lastError()const	return lastError_;




