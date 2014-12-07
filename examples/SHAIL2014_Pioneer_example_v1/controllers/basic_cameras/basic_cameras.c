/*
 * File:          basic_cameras.c
 * Date:          24/11/2013
 * Description:   A simple example for getting and processing camera images.
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
#include <webots/camera.h>


/*
 * You may want to add defines macro here.
 */
#define TIME_STEP 64


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
  
  // Get and enable forward camera device
  WbDeviceTag my_forward_camera = wb_robot_get_device("camera_f");
  wb_camera_enable(my_forward_camera, TIME_STEP);
  
  // Get and enable spherical camera device
  WbDeviceTag my_spherical_camera = wb_robot_get_device("camera_s");
  wb_camera_enable(my_spherical_camera, TIME_STEP); 
  
  // Get size of images for forward camera
  int image_width_f = wb_camera_get_width(my_forward_camera);
  int image_height_f = wb_camera_get_height(my_forward_camera);
  printf("Size of forward camera image: %d, %d.\n",image_width_f,image_height_f);
  
  // Get size of images for spherical camera
  int image_width_s = wb_camera_get_width(my_spherical_camera);
  int image_height_s = wb_camera_get_height(my_spherical_camera);
  printf("Size of spherical camera image: %d, %d.\n",image_width_s,image_height_s);
  
  
  /* main loop */
  do {
    
    /* 
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
    
    // Get current image from forward camera
    const unsigned char *image_f = wb_camera_get_image(my_forward_camera);
    
    
    /* Process sensor data here */
    
    // Count number of pixels that are white (here assumed to have pixel value > 245 out of 255 for all scolor components)
    int sum = 0;
    int x, y;
    for(x=0;x<image_width_f;x++) {
      for(y=0;y<image_height_f;y++) {
        int green = wb_camera_image_get_green(image_f, image_width_f, x, y);
        int red = wb_camera_image_get_red(image_f, image_width_f, x, y);
        int blue = wb_camera_image_get_blue(image_f, image_width_f, x, y);
        
        if((green > 245) && (red > 245) && (blue > 245)) {
          sum = sum + 1;
        }
      }
    }
    
    double percentage_white = (sum/((float) (image_width_f*image_height_f)))*100;
    
    printf("Percentage of white pixels in forward camera image: %4.1f.\n", percentage_white);
    
    
    /*
     * Enter here functions to send actuator commands, like:
     * wb_differential_wheels_set_speed(100.0,100.0);
     */
    double left_speed, right_speed;
    
    // Turn around slowly
    left_speed = 5;
    right_speed = -5;
    
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
