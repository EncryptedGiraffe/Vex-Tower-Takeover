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
  //intake state: 1 = forward, -1 = backward
  int state = 1;
  //intake mode: 1 = running, 0 = stopped
  int mode = 0;
  //intake speed, represented as a decimal percantage from 0.00 (off) to 1.00 (full speed)
  float speed = 1.00F;
  //functions
  void SetMotor()
  {
    Motors::intake.moveVoltage(12000 * mode * state * speed);
  }
  void Start()
  {
    mode = 1;
    SetMotor();
  }
  void Stop()
  {
    mode = 0;
    SetMotor();
  }
  void SetForwards()
  {
    state = 1;
    SetMotor();
  }
  void SetBackwards()
  {
    state = -1;
    SetMotor();
  }
  void SetSpeed(float value)
  {
    if (value < 0)
    {
      speed = 0.00;
    }
    else if (value > 1)
    {
      speed = 1.00;
    }
    else {
      speed = value;
    }
    SetMotor();
  }
}

namespace Deploy
{

}
