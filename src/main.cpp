#include <Camera.h>

#include <opencv2/highgui.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    Camera detector;

    if (!detector.initialize())
    {
        std::cerr << detector.last_error() << std::endl;
        return -1;
    }

    if (!detector.enumerate_devices())
    {
        std::cerr << detector.last_error() << std::endl;
        return -1;
    }

    std::vector<std::unique_ptr<Camera>> cameras;

    int device_count = 1;

    for (int i = 0; i < device_count; ++i)
    {
        auto camera = std::make_unique<Camera>();

        if (!camera->initialize())
        {
            std::cerr << camera->last_error() << std::endl;
            return -1;
        }

        if (!camera->enumerate_devices())
        {
            std::cerr << camera->last_error() << std::endl;
            return -1;
        }

        if (!camera->create_handle(i))
        {
            std::cerr << camera->last_error() << std::endl;
            return -1;
        }

        if (!camera->open())
        {
            std::cerr << camera->last_error() << std::endl;
            return -1;
        }

        if (!camera->start_grabbing())
        {
            std::cerr << camera->last_error() << std::endl;
            return -1;
        }

        cameras.push_back(std::move(camera));
    }


    while (true)
    {
        for (size_t i = 0; i < cameras.size(); ++i)
        {
            cv::Mat image;

            if (!cameras[i]->get_frame(image))
            {
                std::cerr
                    << cameras[i]->last_error()
                    << std::endl;

                continue;
            }

            std::string window_name =
                "Camera_" + std::to_string(i);

            cv::imshow(window_name, image);
        }

        int key = cv::waitKey(1);

        if (key == 27)
        {
            break;
        }
    }


    for (auto& camera : cameras)
    {
        camera->close();
        camera->finalize();
    }


    cv::destroyAllWindows();

    return 0;
}