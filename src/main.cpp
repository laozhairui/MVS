#include "Camera.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
int main()
{
    std::cout<<"start"<<std::endl;
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
    int saveCount=0;
    while(true)
    {
        cv::Mat image;
        if(!camera.getFrame(image))
        {
            std::cout<<camera.lastError();
            break;
        }
        if(camera.getFrame(image))
        {
            std::cout
            << "show channels="
            << image.channels()
            << " size="
            << image.cols
            << "x"
            << image.rows
            << std::endl;
        }
        cv::imshow("Camera",image);
        int key=cv::waitKey(1);
        if(key == 's')
        {
            std::string filename = "test_"+std::to_string(saveCount++)+".jpg";
            cv::imwrite(filename,image);
            std::cout<<"saved:"<<filename<<std::endl;
        }
        else
        {
            std::cout<<"save failed"<<std::endl;
        }
        if(key==27)
        {
            break;
        }
        
    }
    camera.stopGrabbing();
    camera.close();
    return 0;
    system("pause");
}