#include <Camera.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <string>

int main()
{
    Camera camera;
    if(!camera.initialize())
    {
        std::cerr << camera.last_error() <<std::endl;
        return -1;
    }
    if (!camera.enumerate_devices())
    {
        std::cerr << camera.last_error() << std::endl;
        return -1;
    }

    if (!camera.create_handle(0))
    {
        std::cerr << camera.last_error() << std::endl;
        return -1;
    }

    if (!camera.open())
    {
        std::cerr << camera.last_error() << std::endl;
        return -1;
    }

    if (!camera.start_grabbing())
    {
        std::cerr << camera.last_error() << std::endl;
        return -1;
    }

    int save_count = 0;

    while (true)
    {
        cv::Mat image;

        if (!camera.get_frame(image))
        {
            std::cerr << camera.last_error() << std::endl;
            break;
        }

        cv::imshow("Camera", image);

        int key = cv::waitKey(1);

        if (key == 's' || key == 'S')
        {
            std::string filename =
                "test_" + std::to_string(save_count) + ".jpg";

            if (cv::imwrite(filename, image))
            {
                std::cout << "Image saved: "
                          << filename
                          << std::endl;

                ++save_count;
            }
            else
            {
                std::cerr << "Failed to save image: "
                          << filename
                          << std::endl;
            }
        }

        if (key == 27)
        {
            break;
        }
    }

    camera.finalize();
    cv::destroyAllWindows();

    return 0;
}