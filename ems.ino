/* 
 * ems.c - BMW R80 electronics management system.
 * Written March 2019 by Jacob Wood.
*/

/*
 * Constants
 */
#define CRANKING_TIMEOUT          3500   // * CONFIGURABLE * The amount of milliseconds to run the start motor before timing out if the engine has not started.
#define RUNNING_ODOMETER          10.0   // * CONFIGURABLE * An RPM value which is below the lowest RPM the engine could hit when running but well above the RPM the engine could hit when the start motor is running.
#define OFF_HOLD_TIME             5000   // * CONFIGURABLE * The length of time the start button should be held to turn the engine off.
#define DEBOUNCE_DELAY            150    // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
#define FLASH_RATE                120    // * CONFIGURABLE * Times per minute to flash indicators (legally between 60 and 120).
#define BRAKE_LIGHT_BRIGHTNESS    100    // * CONFIGURABLE * Percentage of tail light brightness to be used when the break light is on.
#define TAIL_LIGHT_BRIGHTNESS     100    // * CONFIGURABLE * Percentage of tail light brightness to be used when the brake light is not on/
#define MOMENTARY                 0x0    // Used in record_state() to specify that the state variable should only be changed temporally
#define STICKY                    0x1    // Used in record_state() to specify that the state variable should be changed until the button is pushed again
#define MILLISECONDS_PER_SECOND   1000
#define MILLISECONDS_PER_MINUTE   60000
#define MILLISECONDS_PER_HOUR	    3600000
#define SPEEDOMETER_DEBOUNCE	    28
#define MAX_KM_ACCELERATION_PER_SECOND 	50
#define AVERAGE_WHEEL_CIRCUMFEFRENCE_IN_KILOMETERS 0.001516133
static int const FLASH_CYCLE    = MILLISECONDS_PER_MINUTE /(FLASH_RATE * 2); // Converts the flash rate from flashes per second to the amount of time between state changes.

/*
 * Inputs
 */
static int const high_beam_button_pin       = 4;  // High Beam Button - Sticky
static int const tail_light_button_pin      = 5;  // Tail Light Button - Momentary
static int const indicator_right_button_pin = 6;  // Right Indicator Button - Sticky
static int const indicator_left_button_pin  = 7;  // Left Indicator Button - Sticky
static int const horn_button_pin            = 3;  // Horn Button - Momentary
static int const start_button_pin           = 2;  // Start Button - Momentary
static int const odometer_pin               = A0; // Odometer Analogue Input
static int const speedometer_pin            = A3; // Speedometer Digital Input
static int const speedometer_adjustment_pin = A4;

/*
 * Outputs
 */
static int const high_beam_light_pin        = 10;
static int const tail_light_light_pin       = 11;
static int const indicator_right_light_pin  = 12;
static int const indicator_left_light_pin   = 13;
static int const starter_motor_pin          = 8;
static int const horn_pin                   = 9;
static int const aux_output_pin             = A1;
static int const points_output              = A2;

/*
 * Button States
 */
static int high_beam_button_state       = LOW;
static int tail_light_button_state      = LOW;
static int indicator_right_button_state = LOW;
static int indicator_left_button_state  = LOW;
static int horn_button_state            = LOW;
static int start_button_state           = LOW;
static int aux_output_state             = LOW;
static int points_state                 = LOW;

/*
 * Miscellaneous Variables
 */
static unsigned long record_state_last_debounce_time                    = 0;
static unsigned long indicator_trigger_left_indicator_last_flash_time   = 0;
static unsigned long indicator_trigger_right_indicator_last_flash_time  = 0;
static unsigned long start_attempt_time                                 = 0;
static unsigned long stop_bike_initial_push                             = 0;
static unsigned long stop_bike_last_push_time                           = 0;
static unsigned long time_last_revoloution                              = 0;
static unsigned int  previous_speed									                  	= 0;
static unsigned int  junk_int                                           = 0;
static unsigned long wheel_circumference_in_kilometers = AVERAGE_WHEEL_CIRCUMFEFRENCE_IN_KILOMETERS; // Set to the default so we can use analogRead in the main loop to calculate the custom value.

/*
 * Function Declarations
 */
static void record_state(int read_pin, int output_state_variable, int stickiness);
static void accessories(int state);
static void indicator_trigger(int output_state_variable, int output_pin, int contrasting_output_state_variable, unsigned long last_flash_time);
static void brake_light_trigger(int *button_state, const int *light_pin);
static void start_bike(void);
static void stop_bike(void);
static int bike_running(void);
static float read_odometer(const int odometer_pin);
static int interval_passed(unsigned long start_time, int interval);
static unsigned int read_speed(const int *sensor_input, unsigned long milliseconds_for_revoloution, unsigned long *time_last_revoloution);


void setup()
{
  Serial.begin(9600); // Setup serial connection for debugging

  /*
   * Input Pin Setup
   */
  pinMode(high_beam_button_pin       ,INPUT);
  pinMode(tail_light_button_pin      ,INPUT);
  pinMode(indicator_right_button_pin ,INPUT);
  pinMode(indicator_left_button_pin  ,INPUT);
  pinMode(start_button_pin           ,INPUT);
  pinMode(speedometer_pin            ,INPUT);

  /*
   * Output Pin Setup
   */
  pinMode(high_beam_light_pin        ,OUTPUT);
  pinMode(tail_light_light_pin       ,OUTPUT);
  pinMode(indicator_right_light_pin  ,OUTPUT);
  pinMode(indicator_left_light_pin   ,OUTPUT);
  pinMode(horn_pin                   ,OUTPUT);
  pinMode(starter_motor_pin          ,OUTPUT);
  pinMode(aux_output_pin             ,OUTPUT);
}


void loop()
{ 
  /*
   * Regardless of Running State
   */
  /* Record & Action Button States */
  record_state(high_beam_button_pin, &high_beam_button_state, STICKY);
  digitalWrite(high_beam_light_pin, high_beam_button_state);

  record_state(horn_button_pin, &horn_button_state, MOMENTARY);
  digitalWrite(horn_pin, horn_button_state);

  record_state(tail_light_button_pin, &tail_light_button_state, MOMENTARY);
  brake_light_trigger(&tail_light_button_state, &tail_light_light_pin);

  aux_output_state = HIGH;
  digitalWrite(aux_output_pin, aux_output_state);

  record_state(indicator_right_button_pin, &indicator_right_button_state, STICKY);
  indicator_trigger(indicator_right_button_state, indicator_right_light_pin, &indicator_left_button_state,  &indicator_trigger_right_indicator_last_flash_time);

  record_state(indicator_left_button_pin, &indicator_left_button_state, STICKY);
  indicator_trigger(indicator_left_button_state,  indicator_left_light_pin,  &indicator_right_button_state, &indicator_trigger_left_indicator_last_flash_time);

  wheel_circumference_in_kilometers = (AVERAGE_WHEEL_CIRCUMFEFRENCE_IN_KILOMETERS * 0.9) + ((analogRead(speedometer_pin) * (1.0 / 1023)) * (AVERAGE_WHEEL_CIRCUMFEFRENCE_IN_KILOMETERS * 0.2));
                                    // (Calculate the minimum - 90% (0.9) of the average)   (Add a percentage of the difference between the minimum and maximum value - 20% (0.2))


  /*
   * Bike Running
   */                                  
  if (bike_running()) {
    digitalWrite(points_output, HIGH);



    // update display
    Serial.print("********************\n");

    Serial.print("Bike Status: ");
    if(bike_running()) {
      Serial.print("Running\n");
    }
    else {
      Serial.print("Off\n");
    }

    Serial.print("Speed: ");
    Serial.print(read_speed(&speedometer_pin, &time_last_revoloution));
    Serial.print(" km/h\n");

    Serial.print("Odometer: ");
    Serial.print(read_odometer(odometer_pin));
    Serial.print(" rpm\n");

    Serial.print("\nLeft Indicator: ");
    if(indicator_left_button_state == HIGH) {
      Serial.print("On");
    }
    else {
      Serial.print("Off");
    }

    Serial.print("\nRight Indicator: ");
    if(indicator_right_button_state == HIGH) {
      Serial.print("On");
    }
    else {
      Serial.print("Off");
    }

    Serial.print("\nHigh Beam: ");
    if(high_beam_button_state == HIGH) {
      Serial.print("On");
    }
    else {
      Serial.print("Off");
    }

    Serial.print("\n********************\n\n\n");


    /* Check Stop Button */
    record_state(start_button_pin, &start_button_state, MOMENTARY);
    if (start_button_state == HIGH) {
      stop_bike();
    }
  }


  /* 
   * Bike Not Running
   */
  else {
    digitalWrite(points_output, LOW); // Turn off points if bike has failed to start, has stalled, or has been turned off.
    
    /* Start Button */
    record_state(start_button_pin, &start_button_state, MOMENTARY);
    if (start_button_state == HIGH) {
      accessories(LOW);
      start_bike();
    }
  }
}


/*
 * Function:  record_state 
 * --------------------
 * Reads the state of a button and either momentary or semi-permentantly (STICKY) assigns the changes to the state variable.
 *
 * read_pin: the input pin of the button to read.
 *
 * output_state_variable: a reference to the button's corresponding state variable.
 *
 * stickiness: either MOMENTARY (state changes back to LOW when released) or STICKY (holds it's HIGH position until pressed again).
 */
static void record_state(int read_pin, int *output_state_variable, int stickiness)
{
  /* Button Pressed */
  if (digitalRead(read_pin) == HIGH){
    /* Momentary */
    if (stickiness == MOMENTARY) {
      *output_state_variable = HIGH;
    }
    
    /* Sticky */
    else if (stickiness == STICKY) {
      if (interval_passed(record_state_last_debounce_time, DEBOUNCE_DELAY))  { // Check if DEBOUNCE_DELAY is exceeded ensure it is a new button press and not noise.
        record_state_last_debounce_time = millis();
        *output_state_variable = !*output_state_variable;
      }
    }
  }
  /* Button Not Pressed */
  else {
    if (stickiness == MOMENTARY) {
      *output_state_variable = LOW;
    }
  }
}


/*
 * Function:  accessories 
 * --------------------
 * Allows the easy digitalWrite'ing of all accessories at once.
 * Useful for turning everything off to avoid damage due to current raise/drop during start.
 * 
 * state: the state to set all accessories to - either LOW or HIGH.
 */
static void accessories(int state) {
  digitalWrite(aux_output_pin, state);
  digitalWrite(tail_light_light_pin, state);
  digitalWrite(high_beam_light_pin, state);
  digitalWrite(horn_pin, state);
  digitalWrite(indicator_left_light_pin, state);
  digitalWrite(indicator_right_light_pin, state);
}


/*
 * Function:  indicator_trigger 
 * --------------------
 * Handles the flash speed of indicators based on the FLASH_RATE constant.
 * Also prevents two indicators from being triggered at once.
 *
 * output_state_variable: the state variable for the light to action (left or right).
 *
 * output_pin: the output pin of the light to action.
 *
 * contrasting_output_state_variable: the state variable for the opposite light to the one in output_state_variable. (left or right).
 * 
 * last_flash_time: a pointer to the last_flash_time variable of the corresponding light.
 */
static void indicator_trigger(int output_state_variable, int output_pin, int *contrasting_output_state_variable, unsigned long *last_flash_time)
{
  /* Button Pressed */
  if (output_state_variable == HIGH) {
    *contrasting_output_state_variable = LOW; // Turn contrasting light off.
    /* Check if it's time to cycle indicators. */
    if (interval_passed(*last_flash_time, FLASH_CYCLE)) { 
      /* Swap bulb state */
      digitalWrite(output_pin, !digitalRead(output_pin));
      *last_flash_time = millis();
    }
  }
  /* Button Not Pressed */
  else {
    digitalWrite(output_pin, LOW);
    *last_flash_time = 0;
  }
}


/*
 * Function:  brake_light_trigger 
 * --------------------
 * Handles the 2-in-1 tail light by using PWM to change it from a tail light to a brake light with brightness.
 */
static void brake_light_trigger(int *button_state, const int *light_pin) {
  if (*button_state == HIGH) {
    analogWrite(*light_pin, BRAKE_LIGHT_BRIGHTNESS / 100 * 255);
  }
  else {
    analogWrite(*light_pin, TAIL_LIGHT_BRIGHTNESS / 100 * 255);
  }
}


/*
 * Function:  start_bike 
 * --------------------
 * Handles the push button start process as well as hold to stop.
 */
static void start_bike(void)
{
  digitalWrite(points_output, HIGH);
  delay(1000);
  start_attempt_time = millis();  // Grab current millis() reading to use as a timer for timeout.
  /* While the bike is not running and the starter has not timed out. */
  while (!bike_running() && !interval_passed(start_attempt_time, CRANKING_TIMEOUT)) {
    digitalWrite(starter_motor_pin, HIGH);
  }

  digitalWrite(starter_motor_pin, LOW);
}


/*
 * Function:  stop_bike 
 * --------------------
 * Handles the OFF_HOLD_TIME hold period for the start button to function as an off button.
 */
static void stop_bike(void)
{
  /* If it's been longer than DEBOUNCE_DELAY since the button was last pushed. */
  if(interval_passed(stop_bike_last_push_time, DEBOUNCE_DELAY)) {
    stop_bike_initial_push = millis();
    stop_bike_last_push_time = millis();
  }
  // If it's been less than DEBOUNCE_DELAY since the last recorded push.
  else {                                                  
    stop_bike_last_push_time = millis();
    /* If it's been longer than OFF_HOLD_TIME since the initial push */
    if (stop_bike_last_push_time > stop_bike_initial_push + OFF_HOLD_TIME) {
      /* Turn the engine off */
      points_state == LOW;
    }
  }
}


/*
 * Function:  bike_running 
 * --------------------
 * Detects whether the bike is running or not.
 * 
 * returns: TRUE or FALSE as an integer.
 *            TRUE being the bike is running.
 *            FALSE being that the engine is not running. 
 */
static int bike_running(void)
{
  return (read_odometer(odometer_pin) > RUNNING_ODOMETER);  // If the current odometer is greater than the minimum running value (RUNNING_ODOMETER) than the bike is started.
}


/*
 * Function:  read_odometer 
 * --------------------
 * Returns the current odometer value in RPM (revolutions per minute).
 * 
 * odometer_pin: the analogue pin that the odometer is in.
 *
 * returns: a float value of the current odometer reading in reveloutions per minute (RPM).
 */
static float read_odometer(const int odometer_pin)
{
  int sensor_value = analogRead(odometer_pin); // Read the analog value from the pin specified in odometer_pin.
  float odometer = sensor_value * (100.0 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V).
  return odometer;
}


/*
 * Function:  interval_passed 
 * --------------------
 * Compares an inputted mills() start time plus an interval against the current time to see if the interval has passed.
 * 
 * start_time: a value recorded from mills() to compare the current time to.
 * interval: the amount of time in milliseconds to check if it has been since start_time.
 * 
 * returns: a boolean value as an integer - 1 (TRUE) if the interval has passed and 0 (FALSE) if it has not.
 */
static int interval_passed(unsigned long start_time, int interval) {
  return (((unsigned long) (millis() - start_time)) >= interval);
}

/*
 * Function:  read_speed 
 * --------------------
 * Calculates the speed the vehicle is moving at based on how long/often a wheel rotation takes/occurs along with the size of the wheel.
 * 
 * *sensor_input: an interger pointer of the pin that the speedometer sensor is on.
 * *time_last_revoloution: an unsigned long pointer that the the mills() time that the last revolution occured is stored on.
 * 
 * returns: an integer value of the speed in km/h.
 */
static unsigned int read_speed(const int *sensor_input, unsigned long *time_last_revoloution) {
  if (digitalRead(*sensor_input) == HIGH) {                                     // If the sensor is HIGH
    unsigned long milliseconds_for_revoloution = ((unsigned long) (millis() - *time_last_revoloution)); // Work out how long that revolution took
    *time_last_revoloution = millis();  // Record the current time as when this revoloution was

    int speed = wheel_circumference_in_kilometers * (MILLISECONDS_PER_HOUR / milliseconds_for_revoloution);

    if (speed < previous_speed + (*time_last_revoloution / MILLISECONDS_PER_SECOND) * MAX_KM_ACCELERATION_PER_SECOND) { // If the speed has increased less than the speed would if the bike was accellerating at 50km/s
      previous_speed = speed;
    }
  }
  else {
    if (interval_passed(*time_last_revoloution, (MILLISECONDS_PER_HOUR / ((previous_speed - 1) / wheel_circumference_in_kilometers))) && previous_speed > 0) {
      previous_speed = previous_speed - 1;
    }
  }

  return previous_speed;
}