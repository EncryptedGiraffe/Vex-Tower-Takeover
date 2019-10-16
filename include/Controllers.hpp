#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP
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
    const int frontLeft = 0;
    const int frontRight = 0;
    const int backLeft = 0;
    const int backRight = 0;
  }
  namespace Deploy
  {
    const int deploy = 0;
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
  namespace Deploy
  {
    extern Motor deploy;
  }
}

namespace Chassis
{
  //extern std::shared_ptr<ChassisController> controller;
  const auto controller = ChassisControllerBuilder().withMotors(1, -10).build();
}

namespace Deploy
{

}

#endif
