#include <serial.h>

#include <chrono>
#include <iostream>
#include <thread>

struct IMUMessage {
  double roll;
  double ang_vel;
};

struct MotorMessage {
  double left_torque;
  double right_torque;
};

int main() {
  SerialPort port("/dev/ttyUSB0");

  if (!port.isOpen()) {
    std::cerr << "Failed to open port: " << port << std::endl;
    return 1;
  }

  MotorMessage msg = {-1.0, -2.0};
  IMUMessage res;

  std::cout << "Sending: " << msg.left_torque << " " << msg.right_torque << std::endl;

  char res2[1024];

  while (true) {
    port.receive(&res2, 1024);
    port.send(&msg, sizeof(msg));

    std::cout << res2 << std::endl;
    // std::cout << "Received: " << res.roll << " " << res.ang_vel << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}