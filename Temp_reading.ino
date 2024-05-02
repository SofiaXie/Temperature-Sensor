// Counter for reading temp
unsigned long previousMillis = 0;
const long interval = 300; //in milliseconds =  3s

// Counter for LED
#define LED_PIN 13
unsigned long prevMilLed = 0; // used to determine start of next timer
#define DELAY 2500 //2.5s

void setup() {
  Serial.begin(9600); 
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
 unsigned long currentMillis = millis();
       
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    int sensorValue = analogRead(A0); //reads 1023 values
    float voltage = sensorValue * (3.3/1023.0); //read voltage 

    // Convert voltage to a Temp
    float temp = 0.0;
    temp = (1/40)*voltage-0.3;
    Serial.println(voltage);

    // if (voltage < 1.5) {
    //   temp = (60.0/1.5)*voltage; 
    // }
    // if(voltage < 1.6 & voltage > 1.5){
    //   temp = (70.0/1.6)*voltage;
    // }
    // if(voltage < 1.7 & voltage >1.8){
    //   temp = (80.0/1.8)*voltage;
    // }
    // if(voltage < 1.8  & voltage > 1.9);{
    //   temp = (90.0/1.9)*voltage;    
    // }
    // if(voltage > 2.0 & voltage < 2.1){
    //   temp = (95.0/2.0)*voltage;
    // }
    if(voltage > 3.2){
      temp = (95.0/2.0)*voltage;
      //turn on led, wait 5s then turn off
      digitalWrite(LED_PIN, HIGH);      
      Serial.println("ledOn");      
    }

    // digitalWrite(LED_PIN, LOW);
    Serial.println(temp);
    timeDelay();                 
  } 
}

void timeDelay(){
  // countdown for when the LED turns off
  unsigned long currentMil = millis();

  if(currentMil - prevMilLed >= DELAY){
    prevMilLed = currentMil;
    digitalWrite(LED_PIN, LOW);
    Serial.println("off");
  }
}



