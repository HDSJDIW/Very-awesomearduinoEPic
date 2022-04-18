int weight_sensor = 1 ; // weight sensor input
int set_time = 2 ; // the button that sets the night time
int reset_weight = 3 ; // resets the weight
int alarm_off = 4 ; // ideally turns the alarm off
int ringer = 5 ; // alarm output
int LED = 6 ; // LED light
int time_filter = 5000 ; // amount of time the weight needs to be changed
const long morn_night = 43200000; // 12 hours in milliseconds
unsigned long previousMillis = 0; // initialized start time
int state = LOW; // initial state of what the light and alarm do
int loud = 0; // Marijuana aka whether or not things are popping off
int LOLIDK = 0;
float margin = 1; //tolerance
float diff = 5767; // difference
void setup() {
  pinMode(ringer, OUTPUT); // ringer will be the an output
  pinMode(LED, OUTPUT); // LED light wil be an output 
}

void loop() {
  // put your main code here, to run repeatedly:
  float weight = analogRead(weight_sensor); // reads the value from the weight sensor
  unsigned long current_time = millis(); // determines how much time has passed
  
  
  if (current_time - previousMillis >= morn_night && LOLIDK == 0 ) {
    previousMillis = current_time;
    loud = 1; 
  }
  // has one time cycle passed and have pills been taken
  
  if (digitalRead(reset_weight) == HIGH) {
    float base_weight = weight;
    delay(time_filter); // delay so weird shit doesn't happen if program loops before unpressed Ya'know 
  }
  if (weight - base_weight >= diff){
    delay(time_filter);
    float error_weight = analogRead(weight_sensor);
    if (error_weight - weight =< margin && error weight - weight >= -1*margin){
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
