//
// Created by Richard Wardlow
//

#ifndef FLOWCV_CAMERA_MACOS_HPP_
#define FLOWCV_CAMERA_MACOS_HPP_
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

namespace cam_macos {

struct Device
{
    int id;                  // This can be used to open the device in OpenCV
    std::string deviceName;  // This can be used to show the devices to the user
};

class Camera_MacOS_Enumerator
{
  public:
    std::map<int, Device> getVideoDevicesMap();

  private:
};
}  // namespace cam_macos
#endif  // FLOWCV_CAMERA_MACOS_HPP_
