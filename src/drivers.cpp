#include "drivers.hpp"

namespace Core
{
  //create the controllers
  Controller master(ControllerId::master);
  Controller partner(ControllerId::partner);
}

namespace Motors
{
  namespace Chassis
  {
    Motor frontLeft(Ports::Chassis::frontLeft);
    Motor frontRight(Ports::Chassis::frontRight);
    Motor backLeft(Ports::Chassis::backLeft);
    Motor backRight(Ports::Chassis::backRight);
  }
  namespace Deploy
  {
    Motor deploy(Ports::Deploy::deploy);
  }
}

namespace Chassis
{
  //the controller
  std::shared_ptr<ChassisController> controller;
  //init
  void Initialize()
  {
    //create the controller
    controller = ChassisControllerBuilder()
    .withMotors(Ports::Chassis::frontLeft, -Ports::Chassis::frontRight, -Ports::Chassis::backRight, Ports::Chassis::backLeft)
    .withGearset(AbstractMotor::gearset::green)
    .withDimensions({{4_in, 14.25_in}, imev5GreenTPR})
    .build();
  }
  /*
  ControllerBuilder()
  .withMotors(Ports::Chassis::frontLeft, -Ports::Chassis::frontRight, Ports::Chassis::backLeft, -Ports::Chassis::backRight)
  .withGearset(AbstractMotor::gearset::green)
  .withDimensions({{4_in, 14.25_in}, imev5GreenTPR})
  .build();
  */
}

namespace Deploy
{

}
