#ifndef DRIVERS_HPP
#define DRIVERS_HPP
#include "main.h"

namespace Core
{
  extern Controller master;
  extern Controller partner;
  extern int isInitialized;
  void Initialize();
}

namespace Ports
{
  namespace Chassis
  {
    const int frontLeft = 1;
    const int frontRight = 12;
    const int backLeft = 8;
    const int backRight = 10;
  }
  const int deploy = 2;
  namespace Intake
  {
    const int left = 20;
    const int right = 9;
  }
  const int arm = 3;
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
  extern Motor arm;
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
  //bounds
  const int finalPosition = 6800;
  const int maxSpeed = 100;
  //get the position of the ramp
  int GetPosition();
  //percent is a decimal percentage of the deploy system's total movement
  void Move(float percent);
  //run the deploy sequence for the small goal
  void Deploy();
  //run the deploy sequence for the wide goal
  void DeployWide();
  //initialize
  void Initialize();
}

namespace Arm
{
  void Initialize();
  //arm position controller
  extern std::shared_ptr<AsyncPositionController<double, double>> controller;
  //bounds
  const int maxHeight = 4500;
  const int maxSpeed = 200;
  //tower heights
  const int lowTower = 2700;
  const int highTower = 4000;
  //set the position of the arm
  void SetPosition(int pos);
}

#endif
