#include "HX711.h"
const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;
float calibration_factor = 40; // this calibration factor must be adjusted according to your load cell
float units;
int reset_weight = 3 ; // resets the weight
int alarm_off = 4 ; // ideally turns the alarm off
int ringer = 5 ; // alarm output
int LED = 6 ; // LED light
int time_filter = 5000 ; // amount of time the weight needs to be changed
const long morn_night = 43200000; // 12 hours in milliseconds
unsigned long previousMillis = 0; // initialized start time
int state = LOW; // initial state of what the light and alarm do
int loud = 0; // Marijuana aka whether or not things are popping off
int switch1 = 0;
float margin = 1; //tolerance
float diff = 5767; // difference that's wanted to confirm meds taken
float base_weight = 0; 
void setup() {
  // put your setup code here, to run once:
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  scale.tare(); //Reset the scale to 0
  pinMode(ringer, OUTPUT); // ringer will be the an output
  pinMode(LED, OUTPUT); // LED light wil be an output 
}

void loop() {
  // put your main code here, to run repeatedly:
  float weight = scale.get_units();// reads the value from the weight sensor
  unsigned long current_time = millis(); // determines how much time has passed
  if (current_time - previousMillis >= morn_night && switch1 == 0 ) {
    previousMillis = current_time;
    loud = 1; 
  }
  // has one time cycle passed and have pills been take
  if (digitalRead(reset_weight) == HIGH) {
    float base_weight = weight;
    delay(time_filter); // delay so weird shit doesn't happen if program loops before unpressed Ya'know 
  }
  if (weight - base_weight >= diff){
    delay(time_filter);
    float error_weight = scale.get_units();
    if (error_weight - weight < margin && error_weight - weight > -1*margin){
      switch1 = 1;
    } 
  } 
  if (digitalRead(alarm_off) == HIGH){
    loud = 0;
    delay(time_filter); // delay so weird shit doesn't happen if program loops before unpressed Ya'know 
  }
  if (loud == 1) {
    state = HIGH;
  } else {
    state = LOW;
  }
  digitalWrite(ringer, state);
  digitalWrite(LED, state);  
}
