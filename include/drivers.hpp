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
  namespace Deploy
  {
    const int deploy = 12;
  }
}

namespace Motors
{
  namespace Deploy
  {
    extern Motor deploy;
  }
}

namespace Chassis
{
  void Initialize();
  //the controller
  extern std::shared_ptr<ChassisController> controller;
}

namespace Deploy
{

}

#endif
