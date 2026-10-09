
#pragma once

#include <MvCameraControl.h>
#include <opencv2/core.hpp>

#include <string>

class Camera
{
public:
    Camera();

    ~Camera();

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    bool initialize();

    bool finalize();

    bool enumerate_devices();

    bool create_handle(int device_id = 0);

    bool open();

    bool set_camera_parameters();

    bool start_grabbing();

    bool get_frame(cv::Mat& image);

    void stop_grabbing();

    void close();

    bool is_opened() const;

    std::string last_error() const;

private:
    bool convert_to_bgr(
        MV_FRAME_OUT& frame_info,
        cv::Mat& image
    );

    MV_CC_DEVICE_INFO_LIST m_device_list{};

    void* m_handle;

    bool m_sdk_initialized;

    bool m_device_opened;

    bool m_grabbing;

    std::string m_last_error;
};
