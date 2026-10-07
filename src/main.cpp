#include "Camera.h"
#include <iostream>
#include <opencv2/highgui.hpp>
int main()
{
    Camera camera;
    if(!camera.enumerateDevices())
    {
       std::cout<<camera.lastError();
       return -1;
    }
    if(!camera.creatHandle(0))
    {
        std::cout<<camera.lastError();
        return -1;
    }
    if(!camera.open())
    {
        std::cout<<camera.lastError();
        return -1;
    }
    if(!camera.startGrabbing())
    {
        std::cout<<camera.lastError();
        return -1;
    }
    while(true)
    {
        cv::Mat image;
        if(!camera.getFrame())
        {
            std::cout<<camera.lastError();
            break;
        }
        cv::imshow("Camera",image);
        int key=cv::waitkey(1);
        if(key==27)
        {
            break;
        }
        
    }
    camera.stopGrabbing();
    camera.close();
    return 0;
    
}