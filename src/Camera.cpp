#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Camera.h"
Camera::Camera()
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
	if(deviceId<0 || deviceId>=static_cast<int>(deviceList_.nDeviceNum))//static
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
	MV_CC_SetEnumValue(
    	handle_,
    	"ExposureAuto",
    	0
	);


	MV_CC_SetFloatValue(
    	handle_,
    	"ExposureTime",
    	30000
	);


	MV_CC_SetFloatValue(
    	handle_,
    	"Gain",
    	15
	);
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
bool Camera::getFrame(cv::Mat& image)
{
	lastError_.clear();
	if(!grabbing_)
	{
		lastError_="don't grab";
		return false;
	}
	MV_FRAME_OUT frameInfo={};
	int ret =MV_CC_GetImageBuffer(handle_,&frameInfo,1000);
	if(ret == MV_OK)
	{
    	std::cout 
        << "width="
        << frameInfo.stFrameInfo.nWidth
        << " height="
        << frameInfo.stFrameInfo.nHeight
        << std::endl;
		std::cout 
		<< "pixel type="
		<< frameInfo.stFrameInfo.enPixelType
		<< std::endl;
	}
	if(ret !=MV_OK)
	{
		lastError_="GetImageBuffer failed";
		return false;
	}
	if(!Camera::convertToBGR(frameInfo,image))
	{
		MV_CC_FreeImageBuffer(handle_,&frameInfo);
		return false;
	}
	MV_CC_FreeImageBuffer(handle_,&frameInfo);
	return true;
}
bool Camera::convertToBGR(MV_FRAME_OUT& frameInfo, cv::Mat& image)
{
    if(frameInfo.pBufAddr == nullptr)
    {
        return false;
    }


    cv::Mat raw(
        frameInfo.stFrameInfo.nHeight,
        frameInfo.stFrameInfo.nWidth,
        CV_8UC1,
        frameInfo.pBufAddr
    );
	double minValue;
	double maxValue;

	cv::minMaxLoc(
    	raw,
    	&minValue,
    	&maxValue
	);

	std::cout
	<< "raw min="
	<< minValue
	<< " max="
	<< maxValue
	<< std::endl;

    cv::cvtColor(
        raw,
        image,
        cv::COLOR_BayerBG2BGR
    );
	std::cout
	<< "BGR channels="
	<< image.channels()
	<< " size="
	<< image.cols
	<< "x"
	<< image.rows
	<< std::endl;

    return true;
}//ai
void Camera::stopGrabbing()
{
	lastError_.clear();
	if(!grabbing_)
	{
		return;
	}
	int ret =MV_CC_StopGrabbing(handle_);
	if(ret!=MV_OK)
	{
		lastError_="stop grabbing failed";
		return;
	}
	grabbing_=false;
}
void Camera::close()
{
	if(grabbing_)
	{
		stopGrabbing();
	}
	if(deviceOpened_)
	{
		MV_CC_CloseDevice(handle_);
		deviceOpened_=false;
	}
	if(handle_!=nullptr)
	{
		MV_CC_DestroyHandle(handle_);
		handle_=nullptr;
	}
}
bool Camera::isOpened()const
{
	return deviceOpened_;
}
std::string Camera::lastError()const
{
	return lastError_;
}




