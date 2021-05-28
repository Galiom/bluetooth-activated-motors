#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int trigPin = 8;
int echoPin = 2;
long duration;
int distance;
int enA = 9;
int in1 = 7;
int in2 = 6;
int enB = 3;
int in3 = 4;
int in4 = 5;
String x;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Working!");

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  mySerial.begin(9600);
  mySerial.println("Hello, world");
  }
  int flag = 0;
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  if (distance < 15){
      analogWrite(enA, 0);
      analogWrite(enB, 0);
  }
  if (mySerial.available()) {
    x = mySerial.readString();
    Serial.println(x);
    flag = 1;
  }
  if (Serial.available()) {
    x = Serial.readString();
    mySerial.println(x);
    flag = 1;
  }
  if (flag == 1){
  flag = 0;
  String tokens[2];
  int l = x.length();
  //split x to tokens , split is based on space(' ') between words
  int cnt = 0;
  for (int i=0; i<l ; i++)
  {
    if (x[i] == ' ')
      cnt++;
    tokens[cnt]=tokens[cnt]+x[i];
  }

  for(int i=0; i<2; i++)
  {
    tokens[i].trim();//remove white space
    Serial.println(tokens[i]);
  }
  //Serial.println(cnt); 
    if (cnt == 1){
    //we expect 2 item in command
    int Speed1  = tokens[0].toInt();
    int Speed2 = tokens[1].toInt();
    if (distance>15)
     {
       analogWrite(enA, 255*Speed1/100);
       digitalWrite(in1, HIGH);
       digitalWrite(in2, LOW);
       analogWrite(enB, 255*Speed2/100);
       digitalWrite(in3, HIGH);
       digitalWrite(in4, LOW);
     }
     else {
       Serial.println("ERORR: too close to a surface");
       mySerial.println("ERORR: too close to a surface");
     }
   }
   else {
     Serial.println("ERROR: command not in correct format");
     mySerial.println("ERROR: command not in correct format");
   }
  }
}
