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
  Motor deploy(Ports::deploy);
  MotorGroup intake({Ports::Intake::left, -Ports::Intake::right});
  Motor arm(Ports::arm);
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
  int cur_pos = 0;
  //get the position of the ramp
  int GetPosition()
  {
    return cur_pos / finalPosition;
  }
  //percent is a decimal percentage of the deploy system's total movement
  void Move(float percent)
  {
    float per;
    //check percent
    if(percent > 1.00)
      per = 1.00;
    else if(percent < 0.00)
      per = 0.00;
    else
      per = percent;
    //calculate new position
    cur_pos = per * finalPosition;
    //set the motor
    Motors::deploy.moveAbsolute(-cur_pos, maxSpeed);
  }
  //task state variables
  bool isDeploying = false;
  bool isFinished = false;

  //internal async deploy sequence
  void _deploy(void* param)
  {
    while(true)
    {
      if(isDeploying)
      {
        //move the intake
        Intake::SetBackwards();
        Intake::SetSpeed(0.4);
        Intake::Start();
        pros::Task::delay(200);
        if(!isDeploying) //check for abort
          continue;
        //move the intake
        Intake::SetSpeed(0.1);
        //move the ramp
        Deploy::Move(1.0F);
        pros::Task::delay(3300);
        if(!isDeploying) //check for abort
          continue;
        //move intake
        Intake::SetSpeed(0.8);
        Intake::SetForwards();
        //move forwards
        Motors::Chassis::frontLeft.moveVoltage(2000);
        Motors::Chassis::frontRight.moveVoltage(-2000);
        Motors::Chassis::backLeft.moveVoltage(2000);
        Motors::Chassis::backRight.moveVoltage(-2000);
        pros::Task::delay(700);
        if(!isDeploying) //check for abort
          continue;
        //move the intake
        Intake::SetBackwards();
        Intake::SetSpeed(0.4);
        Intake::Start();
        //move the deploy
        Deploy::Move(0.00F);
        //move backwards
        Motors::Chassis::frontLeft.moveVoltage(-2000);
        Motors::Chassis::frontRight.moveVoltage(2000);
        Motors::Chassis::backLeft.moveVoltage(-2000);
        Motors::Chassis::backRight.moveVoltage(2000);
        pros::Task::delay(4000);
        if(!isDeploying) //check for abort
          continue;
        Deploy::Move(0.0F);
        Intake::SetForwards();
        Intake::SetSpeed(1.00);
        Intake::Stop();
        //finish
        isDeploying = false;
        isFinished = true;
      }
      else
      {
        pros::Task::delay(20);
      }
    }
  }
  //run the deploy sequence
  void Deploy()
  {
    //start the sequence
    isDeploying = true;
    isFinished = false;
    Deploy::Move(0.00F);
    Arm::SetPosition(0);
    while(true)
    {
      //check if finished
      if(isFinished)
      {
        isDeploying = false;
        isFinished = false;
        break;
      }
      if(Core::master.getDigital(ControllerDigital::X))
      {
        isDeploying = false;
        isFinished = false;
        break;
      }
      pros::delay(20);
    }
  }
  void Initialize()
  {
    pros::Task deploy_task(_deploy, (void*)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Deploy Task");
  }
}

namespace Arm
{
  std::shared_ptr<AsyncPositionController<double, double>> controller;
  void Initialize()
  {
    controller = AsyncPosControllerBuilder()
    .withMotor(Ports::arm)
    .build();
  }
  int cur_pos = 0;
  //set the position of the arm
  void SetPosition(int pos)
  {
    //check bounds
    if(pos < 0)
    {
      cur_pos = 0;
    }
    else if(pos > maxHeight)
    {
      cur_pos = maxHeight;
    }
    else
    {
      cur_pos = pos;
    }
    //set the motor
    controller->setTarget(cur_pos);
  }
}
