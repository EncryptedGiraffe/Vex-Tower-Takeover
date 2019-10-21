#ifndef DRIVERS_HPP
#define DRIVERS_HPP
#include "main.h"

namespace Core
{
  extern Controller master;
  extern Controller partner;
}

namespace Ports
{
  namespace Chassis
  {
    const int frontLeft = 11;
    const int frontRight = 13;
    const int backLeft = 14;
    const int backRight = 15;
  }
  const int deploy = 12;
  namespace Intake
  {
    const int left = 5;
    const int right = 4;
  }
}

namespace Motors
{
  namespace Chassis
  {
    extern Motor frontLeft;
    extern Motor frontRight;
    extern Motor backLeft;
    extern Motor backRight;
  }
  extern Motor deploy;
  extern MotorGroup intake;
}

namespace Chassis
{
  void Initialize();
  //the controller
  extern std::shared_ptr<ChassisController> controller;
}

namespace Intake
{
  void Start();
  void Stop();
  void SetForwards();
  void SetBackwards();
  //speed is a decimal percentage from 0.00 to 1.00
  void SetSpeed(float value);
}

namespace Deploy
{

}

#endif
