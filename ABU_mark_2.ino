#ifdef __AVR_ATmega2560__
#include "ABU_3.h"
ABU_ROBOT robot;

//Timer_2
#define PWM_LF 10  //A
#define IN1_LF 40
#define IN2_LF 38
//Timer_1
#define PWM_LB 11  //A
#define IN1_LB 36
#define IN2_LB 34

#define PWM_RB 13  //B
#define IN1_RB 26
#define IN2_RB 28

#define PWM_RF 12  //C
#define IN1_RF 30
#define IN2_RF 32

#define ROBOT_LEN 0.41f       // Example value, adjust according to your robot's specifications
#define ROBOT_WID 0.41f       // Example value, adjust according to your robot's specifications
#define SCALE_FACTOR_X 0.09f  // Example value, adjust according to your requirements
#define SCALE_FACTOR_Y 0.09f  // Example value, adjust according to your requirements
#define SCALE_FACTOR_Z 0.09f  // Example value, adjust according to your requirements
#define WHEEL_RADIUS 0.06f    // Example value, adjust according to your robot's specifications

float SCALE_FACTOR_Gear_1 = 0.09f;
float SCALE_FACTOR_Gear_2 = 0.10f;
float SCALE_FACTOR_Gear_3 = 0.11f;

#define button_speedUP 0
#define button_speedDOWN 2

#define pin_Clamp_1 23
#define pin_Clamp_2 25
#define pin_Clamp_Up_Down 27
#define pin_Clamp_Grab_Poll 29

#define pin_keep_Ball 7
#define pin_Keep A4
#define pin_UnKeep A5

#define pin_Shoot 6
#define Attack_Ball A2
#define Reload_Ball A3
#define Set_Attack_Ball A6  //limit switch
#define Set_Reload_Ball A7  //limit switch

#define button_Clamp_1 4
#define button_Clamp_2 6
#define button_Clamp_Up_Down 5
#define button_Clamp_Grab_Poll 7

#define button_keep 3
#define button_UnKeep 1
#define force 200

#define button_Shoot 0
#define button_UP 1
#define button_Reload 3
#define force_Shoot 230
#define force_UP 150
#define force_Reload 150

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define Slave answer size
#define ANSWERSIZE 18

void setup() {
  Serial.begin(115200);
  // robot.Setup_ROBOT_nRF24(A1 ,A0 ,0xF0F0F0F0E1LL ,0xF0F0F0F0D2LL);
  robot.Setup_ROBOT_master();

  // car.Setup_Scale_factor(SCALE_FACTOR_X ,SCALE_FACTOR_Y ,SCALE_FACTOR_Z);
  robot.GEAR_Setup(SCALE_FACTOR_Gear_1, SCALE_FACTOR_Gear_2, SCALE_FACTOR_Gear_3);
  robot.Setup_max_speed(0.0, 185.0, 205.0, 225.0);

  robot.Setup_LF_pin(PWM_LF, 8000, 8, IN1_LF, IN2_LF);
  robot.Setup_LB_pin(PWM_LB, 8000, 8, IN1_LB, IN2_LB);
  robot.Setup_RF_pin(PWM_RF, 8000, 8, IN1_RF, IN2_RF);
  robot.Setup_RB_pin(PWM_RB, 8000, 8, IN1_RB, IN2_RB);
  robot.Setup_Wheel(ROBOT_LEN, ROBOT_WID, WHEEL_RADIUS);

  robot.Setup_Clamp(pin_Clamp_1, pin_Clamp_2, pin_Clamp_Up_Down, pin_Clamp_Grab_Poll);

  robot.KEEP_Ball_Setup(pin_keep_Ball, pin_Keep, pin_UnKeep);

  robot.Shoot_Ball_Setup(pin_Shoot, Attack_Ball, Reload_Ball, Set_Attack_Ball, Set_Reload_Ball);
}

void loop() {
  // robot.Readvalue_nrf24();
  robot.Readvalue_slave(SLAVE_ADDR, ANSWERSIZE);

  robot.UP_speed(button_speedUP, button_speedDOWN);
  robot.Move();

  robot.CLAMP(button_Clamp_1, button_Clamp_2, button_Clamp_Up_Down, button_Clamp_Grab_Poll);

  robot.Shoot_Ball(button_Shoot, button_UP, button_Reload, force_Shoot, force_UP, force_Reload);

  robot.KEEP_Ball(button_keep, button_UnKeep, force);
}
#endif