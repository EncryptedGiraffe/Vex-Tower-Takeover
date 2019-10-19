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
    //create chassis motors
    Motor frontLeft(Ports::Chassis::frontLeft);
    Motor frontRight(Ports::Chassis::frontRight);
    Motor backLeft(Ports::Chassis::backLeft);
    Motor backRight(Ports::Chassis::backRight);
  }
  Motor deploy(Ports::deploy);
  MotorGroup intake({Ports::Intake::left, Ports::Intake::right});
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

namespace Intake
{
  //intake state: 1 = forward, 0 = stopped, -1 = backward
  int state = 0;
  //intake speed, represented as a decimal percantage from 0.00 (off) to 1.00 (full speed)
  float speed = 0.00F;
}

namespace Deploy
{

}
