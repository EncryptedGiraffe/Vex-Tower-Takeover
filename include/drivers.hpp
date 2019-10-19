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
  extern std::shared_ptr<ChassisController> controller;
  //const auto controller = ChassisControllerBuilder().withMotors(1, -10).build();
}

namespace Intake
{
 
}

namespace Deploy
{

}

#endif
