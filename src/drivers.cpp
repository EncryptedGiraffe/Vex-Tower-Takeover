#include "drivers.hpp"

namespace Core
{
  //create the controllers
  Controller master(ControllerId::master);
  Controller partner(ControllerId::partner);
}

namespace Motors
{
  namespace Deploy
  {
    Motor deploy(Ports::Deploy::deploy);
  }
}

namespace Chassis
{
  /*
  std::shared_ptr<ChassisController> controller = ChassisControllerBuilder()
  .withMotors(Ports::Chassis::frontLeft, -Ports::Chassis::frontRight, Ports::Chassis::backLeft, -Ports::Chassis::backRight)
  .withGearset(AbstractMotor::gearset::green)
  .withDimensions({{4_in, 14.25_in}, imev5GreenTPR})
  .build();
  */
}

namespace Deploy
{

}
