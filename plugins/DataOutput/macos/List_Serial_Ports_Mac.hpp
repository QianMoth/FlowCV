//
// Platform Serial Device Enumerator
// MacOS
//

#ifndef FLOWCV_SERIAL_PORTS_MAC_HPP_
#define FLOWCV_SERIAL_PORTS_MAC_HPP_
#include <serial/serial.h>
#include <unistd.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace SerialDeviceEnum {

struct SerialPortInfo
{
    std::string port;
    std::string description;
    std::string hardware_id;
};

class DeviceEnumerator
{
  public:
    std::vector<SerialPortInfo> GetSerialPortList();
};

}  // End Namespace SerialDeviceEnum

#endif  // FLOWCV_SERIAL_PORTS_MAC_HPP_
