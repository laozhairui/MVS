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
Camera::open()
{
	lastError_.clear()
	if(handle_=nullptr)
	{
		lastError_="creat handle failed";
		return false;
	}
	int ret=MV_CC_OpenDevice(handle_);
	if(ret!=MV_OK)
	{
		lastError_="handle is null";
		return false;
	}
	deviceOpened_=true;
	return true;
}


