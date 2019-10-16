#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP
#include "main.h"

namespace Core
{
  extern Controller master;
  extern Controller partner;
}

namespace Motors
{
  namespace Ports
  {
    namespace Chassis
    {
      const int frontLeft = 0;
      const int frontRight = 0;
      const int backLeft = 0;
      const int backRight = 0;
    }
  }
  namespace Chassis
  {
    extern Motor frontLeft;
    extern Motor frontRight;
    extern Motor backLeft;
    extern Motor backRight;
  }
}

namespace Chassis
{

}

#endif
