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
		lastError="wrong on enumerateDevices";
		return false;
	}
	if(deviceList_.nDeviceNum==0)//nDeviceNum
	{
		lastError="can't find camera";
		return false;
	}
	return true;
}

