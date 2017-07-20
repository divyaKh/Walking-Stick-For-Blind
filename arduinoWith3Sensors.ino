
#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 7
#define echoPin3 8
#define buzzer 9
#define alertButton 10

long duration,distance,RightSensor,BackSensor,FrontSensor,LeftSensor, MinDistance,alertButtonValue;

void setup()
{
Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(alertButton, OUTPUT);
}

void loop() {
SonarSensor(trigPin3, echoPin3);
RightSensor = distance;
  
SonarSensor(trigPin1, echoPin1);
LeftSensor = distance;


SonarSensor(trigPin2, echoPin2);
FrontSensor = distance;

alertButtonValue=digitalRead(alertButton);

if((LeftSensor<50 && LeftSensor>2) || (RightSensor<50 && RightSensor>2) || (FrontSensor<50 && FrontSensor>2))
{
  if(alertButtonValue==HIGH)                         //if alert button is in ON state (i.e connected to +5V) then the buzzer continuously beeps
MakeAlertBeepSound();
else                                           //if alert button is in OFF state (i.e connected to GND) then obstacle detection is carried out
FindMinDistance();}

}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;              //this converts the distance into centimeters

}

void MakeBeepSound()
{
  tone(buzzer, 1000);               // Send 1KHz sound signal...
  delay(500);                      // ...for 500 msec
  noTone(buzzer);                   // Stop sound...
 }

 
void MakeAlertBeepSound()
{
  tone(buzzer, 1000);               // Send 1KHz sound signal...
  delay(2000);                      // ...for 1000 msec
  noTone(buzzer);                   // Stop sound...
 }

 void FindMinDistance()
 {
  if(LeftSensor<FrontSensor && FrontSensor<RightSensor)
{
  MinDistance=LeftSensor;
  MakeBeepSound();
 delay(300);
 MakeBeepSound();
 delay(2000);
    }

    else if(FrontSensor<LeftSensor && FrontSensor<RightSensor)
    {
      MinDistance=FrontSensor;
       MakeBeepSound();
 delay(300);
 MakeBeepSound();
 delay(300);
 MakeBeepSound();
 delay(2000);
      }

      else if(RightSensor<LeftSensor && RightSensor<FrontSensor)
      { MinDistance=RightSensor;
        MakeBeepSound();
       delay(2000);
        }

Serial.print("Alert button value:  ");
Serial.println(alertButtonValue);
Serial.print(LeftSensor);
Serial.print("-");
Serial.print(FrontSensor);
Serial.print("-");
Serial.println(RightSensor);
Serial.println(MinDistance);

}
