import com.cyberbotics.webots.controller.*;

public class Terminator_1 extends DifferentialWheels {
  private DistanceSensor distanceSensor1;
  private DistanceSensor distanceSensor14;
	
  private static final int MAX_SPEED = 60; // milliseconds
  private static final int TIME_STEP = 64; // milliseconds
	
  public Terminator_1() {
    super();
    distanceSensor1 = getDistanceSensor("ds1");
    distanceSensor14 = getDistanceSensor("ds14");
		
    distanceSensor1.enable(TIME_STEP);
    distanceSensor14.enable(TIME_STEP);
  }
	
  public void run() {
    while (step(TIME_STEP) != -1) {
      double value1 = distanceSensor1.getValue();
      double value14 = distanceSensor14.getValue();
      System.out.printf("Distance sensor ds1 (left): %.2f.\n", value1);
      System.out.printf("Distance sensor ds14 (right): %.2f.\n", value14);
			
      double left_speed, right_speed;
      if (value14 > 50) {
        if (value1 > 50) {
          System.out.printf("Backing up and turning left.\n"); 
          left_speed = - MAX_SPEED / 2.0;
          right_speed = - MAX_SPEED / 25.0;
        } else {
          System.out.printf("Turning on the spot.\n"); 
          left_speed = -MAX_SPEED / 2.0;
          right_speed = MAX_SPEED / 2.0;
        }
      } else {
        System.out.printf("Moving forward.\n");
        left_speed = MAX_SPEED;
        right_speed = MAX_SPEED;
      }
      this.setSpeed(left_speed, right_speed);
    }
  }
	
  public static void main(String[] args) {
    Terminator_1 terminator = new Terminator_1();
    terminator.run();
  }
}