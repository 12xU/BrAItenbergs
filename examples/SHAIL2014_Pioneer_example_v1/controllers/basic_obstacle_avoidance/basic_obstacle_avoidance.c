/*
 * File:          basic_obstacle_avoidance.c
 * Date:          24/11/2013
 * Description:   A simple example for avoiding obstacles using two infrared sensors.
 * Author:        Martin F. Stoelen
 * Modifications: 
 */


/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <stdio.h>

#include <webots/robot.h>
#include <webots/differential_wheels.h>
#include <webots/distance_sensor.h>


/*
 * You may want to add defines macro here.
 */
#define TIME_STEP 64
#define MAX_SPEED 60


int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  
  
  /*
   * You should declare here DeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  
  // Get and enable two proximity sensors
  WbDeviceTag my_ir_sensor_1 = wb_robot_get_device("ds1");
  wb_distance_sensor_enable(my_ir_sensor_1, TIME_STEP);
  WbDeviceTag my_ir_sensor_14 = wb_robot_get_device("ds14");
  wb_distance_sensor_enable(my_ir_sensor_14, TIME_STEP);
  
  
  /* main loop */
  do {
    
    /* 
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
    double ir1_val = wb_distance_sensor_get_value(my_ir_sensor_1);
    double ir14_val = wb_distance_sensor_get_value(my_ir_sensor_14);
    printf("Distance sensor ds1 (left): %.2f.\n",ir1_val);
    printf("Distance sensor ds14 (right): %.2f.\n",ir14_val);
    
    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
    double left_speed, right_speed;
    
    if (ir14_val > 50) {
      if (ir1_val > 50) {
        printf("Backing up and turning left.\n"); 
      
        left_speed = - MAX_SPEED / 2.0;
        right_speed = - MAX_SPEED / 25.0;
      }
      else {
        printf("Turning on the spot.\n"); 
      
        left_speed = -MAX_SPEED / 2.0;
        right_speed = MAX_SPEED / 2.0;
      }
    }
    else {
      printf("Moving forward.\n");
      
      left_speed = MAX_SPEED;
      right_speed = MAX_SPEED;
    }
    
    /*Set the motor speeds.*/
    wb_differential_wheels_set_speed(left_speed, right_speed);
    
    /* 
     * Perform a simulation step of 64 milliseconds
     * and leave the loop when the simulation is over
     */
  } while (wb_robot_step(TIME_STEP) != -1);
  
  
  /* Necessary to cleanup webots stuff */
  wb_robot_cleanup();
  
  return 0;
}
