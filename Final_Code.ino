// IoT Based Smart Agriculture :- SAATHI
//depth_plus_servo();
  #include <Servo.h>
  #include<SoftwareSerial.h>
  const int servoPin = 7;
  const int emptyPin = 9;//LED
  const int fullPin = 8;//LED
  //Create a servo object 
  Servo Servo1;

//temp_humid();
  #include <Adafruit_Sensor.h>
  #include <DHT.h> 
  int length = 1;
  #define DHTPIN A2
  #define DHTTYPE DHT11
  #define LED_TOO_COLD 4
  #define LED_PERFECT 5
  #define LED_TOO_HOT 6
  #define buzz 13 //Silent for another code
  DHT dht(DHTPIN, DHTTYPE);

//soil_moisture();
  const int sensorPin = A1; 
  int sensorValue;  
  const int limit = 300; 

//motion_sensor();
int buzzerPin = 13;  //BUZZER INPUT PIN.
int pirPin = 10;  //MOTION SENSOR INPUT PIN.
int sensorValuePIR = LOW;//DEFAULT SENSOR STATE.

//rain_detector();
//Analog pin A3

//ultrasonic_piezo();
  //defining the pins
  const int trigPin = 2; 
  const int echoPin = 3;
  const int buzzPin = 11;
  //defining variables
  float duration;
  float distance;

void setup() 
{
  
//depth_plus_servo();
    //both LED
    pinMode(fullPin,OUTPUT);
    pinMode(emptyPin,OUTPUT);

//temp_humid();
    Serial.println("DHT11 test!"); 
    dht.begin(); 

//soil_moisture();
    Serial.begin(9600);
    // Starts the serial communication
    
//motion_sensor();
pinMode(buzzerPin,OUTPUT);//SET BUZZER AS OUTPUT.
pinMode(pirPin, INPUT);//SET PIR AS INPUT.

//rain_detector();
    //NIL

//ultrasonic_piezo();
    pinMode(trigPin, OUTPUT);
    // Sets the trigPin as an Output 
    pinMode(echoPin, INPUT);
    // Sets the echoPin as an Input 
    pinMode(buzzPin,OUTPUT);
    
}

void loop() 
  { 
  
    //Declaring the functions in the LOOP function for continuous working
    
    //Water Level Sensor + Servo Motor + LED*3
    depth_plus_servo();
  
    //Temperature and Humidity Sensor + LED*3
    temp_humid();
  
    //Soil Moisture Sensor
    soil_moisture();
  
    //Motion Sensor (PIR)
    motion_sensor();
  
    //Rain Detection Sensor
    rain_detector();
  
    //Ultrasonic Sensor + Piezo Buzzer
    ultrasonic_piezo();
  
  }

//Defining the functions

//Water Level Sensor + Servo Motor + LED*3
void depth_plus_servo()
  {
      int level = analogRead(A0); 
      // read input value
      Serial.print("Water Depth Sensor : Water level = \n");
      Serial.println(level);
      if(level>500&&level<540)
        { 
          digitalWrite(9,1);//empty
          digitalWrite(8,0);//full
          //No water
          //Make servo go to 0 degrees 
          Serial.println("Water Depth Sensor : Tank Empty\n"); 
          digitalWrite(9,1);
          digitalWrite(8,0);
          Serial.println("Opening full flap\n"); 
          digitalWrite(9,1);
          digitalWrite(9,0);
          Servo1.write(0); //angle value
          delay(300);
          //Make servo go to 90 degrees 
          Servo1.write(90); 
          digitalWrite(9,1);
          digitalWrite(9,0);
          delay(300); 
          //Make servo go to 180 degrees 
          Servo1.write(180); 
          delay(500);
        }
 
      else if(level>540&&level<620)
       { 
           //Little water
           Serial.println("Water Depth Sensor : Water available in Tank\n"); 
           Serial.println("Opening half flap\n");
          //Make servo go to 0 degrees 
           Servo1.write(0);
           delay(300); 
          //Make servo go to 90 degrees 
           Servo1.write(90); 
           delay(3000);    
       } 
      
      else if(level>620&&level<660) 
        {
            Serial.println("Water Depth Sensor : Tank full\n");
            digitalWrite(8,1);
            digitalWrite(9,0);
            Serial.println("Flap is not supposed to open\n");
        }
      else
        {
            digitalWrite(8,0);
            digitalWrite(9,0);
         
        }
      
  }

//Temperature and Humidity Sensor + LED*3
void temp_humid()
  { 
      pinMode (4, OUTPUT); 
      pinMode (5, OUTPUT);
      pinMode (6, OUTPUT); 
      pinMode (13, OUTPUT);
      delay(1000); 
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);
      if (isnan(h) || isnan(t) || isnan(f)) 
        { 
          Serial.println("Failed to read from DHT sensor!");
          return; 
        }
      Serial.println("DHT11 Sensor Data : "); 
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t); 
      Serial.println(" *C "); 
      if (t <= 22)    
        { 
          Serial.println("DHT11 Sensor : Too cold!"); 
          digitalWrite(4, HIGH);
          digitalWrite(13,HIGH);
          delay (500);
          digitalWrite(13,LOW);
          digitalWrite(5, LOW);
        } 
      if (22 < t < 38)
        { 
          Serial.println("DHT11 Sensor : Perfect temperature!"); 
          digitalWrite(5, HIGH);
          delay (500); 
          digitalWrite(5, LOW); 
        } 
      if (t >= 39)
        { 
          Serial.println("DHT11 Sensor : Too hot!"); 
          digitalWrite(6, HIGH); 
          digitalWrite(13,HIGH);
          delay (500); 
          digitalWrite(13,LOW);
          digitalWrite(6, LOW); 
        }
  }

//Soil Moisture Sensor
void soil_moisture()
  {
      sensorValue = analogRead(sensorPin); 
      Serial.println("Soil Moisture Sensor : Analog Value : ");
      Serial.println(sensorValue);
      Serial.println("Moisture Sensor Units");
      delay(1000); 
  }

//Motion Sensor (PIR)
void motion_sensor()
  {
      sensorValuePIR = digitalRead(pirPin); //READ PIR INPUT PIN.
      if ( sensorValuePIR == HIGH) 
        {//IF MOTION IS DETECTED.
          tone(buzzerPin, 2500 ,1050);   //BUZZ THE BUZZER
          delay(500); //TIME DIFFERENCE BETWEEN HIGH(ON)& LOW(OFF).
          sensorValuePIR = analogRead(pirPin); 
          Serial.println("PIR Motion Sensor : Motion Detected");
          //Serial.println("Analog Data from Sensor : ");
          //Serial.println(sensorValuePIR);
          delay(500);
        }
      else 
        {     //IF NO MOTION IS DETECTED.
          noTone(buzzerPin);    //SILENT THE BUZZER.
          sensorValuePIR = analogRead(pirPin); 
          Serial.println("PIR Motion Sensor : No Motion Detected : ");
          //Serial.println(sensorValuePIR);
          delay(1500);
        }
  }

//Rain Detection Sensor
void rain_detector()
  {
      //analog output
      if(analogRead(A3)<300)
        Serial.println("Heavy Rain");
      else if(analogRead(A3)<500||analogRead(A3)>300) 
        Serial.println("Rain Detector : Moderate Rain");
      else 
        Serial.println("Rain Detector : Its Not Raining");
       
      delay(250);
  }

//Ultrasonic Sensor + Piezo Buzzer
void ultrasonic_piezo()
  {
      // Clears the trigPin 
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2); 
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds 
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = (duration*0.034/2)/100;//taking 10 seconds as default value
      // Prints the distance on the Serial Monitor 
      Serial.print("Ultrasonic Sensor : Distance of intruder from Field ( in metres ) \n"); 
      Serial.println(distance);
      Serial.print("\n");
      delay(150);
      if( distance <= 1 )
        {
          digitalWrite(11,1);
        }
      else
        {
          digitalWrite(11,0);
        }
      Serial.println("-----------------End Of Stanza-------------------");
  }
