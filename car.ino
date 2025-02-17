#define sensorR A0
#define sensorL A1
int y1 = 4;
int y2 = 2;
int r1 = 8;
int r2 = 7;
int w1 = 10;
int w2 = 11;
int servo1p = 6;
int servo1n = 9;
int servo2p = 3;
int servo2n = 5;

void setup()
{
  pinMode(y1, OUTPUT);
  pinMode(y2, OUTPUT);
  pinMode(w1, OUTPUT);
  pinMode(w2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  Serial.begin(9600);
  pinMode(sensorR, INPUT);
  pinMode(sensorL, INPUT);
  pinMode(servo1p, OUTPUT);
  pinMode(servo1n, OUTPUT);
  pinMode(servo2p, OUTPUT);
  pinMode(servo2n, OUTPUT);
}

int state_of_sensorL(){
  Serial.print("SensorL value: ");
  int y = analogRead(sensorL);
  Serial.print(y);
  return y;
}

int state_of_sensorR(){
  Serial.print("       SensorR value: ");
  int x = analogRead(sensorR);
  Serial.println(x);
  return x;
}

void light(int x, int y1, int y2, int r1, int r2, int w1, int w2){
  if(x == 0){
  	digitalWrite(y2, HIGH);
    delay(1250);
  	digitalWrite(y2, LOW);
    delay(250);
    digitalWrite(w1, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
    digitalWrite(w2, LOW);
  }
  else if(x == 1){
  	digitalWrite(y1, HIGH);
    delay(1250);
  	digitalWrite(y1, LOW);
    delay(250);
    digitalWrite(w1, LOW);
    digitalWrite(w2, LOW);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
  }
  else if(x == 2){
  	digitalWrite(w1, HIGH);
  	digitalWrite(w2, HIGH);
    digitalWrite(r1, LOW);
    digitalWrite(r2, LOW);
  }
  else{
       digitalWrite(r1, HIGH);
       digitalWrite(r2, HIGH);
       digitalWrite(w1, LOW);
       digitalWrite(w2, LOW);
      }
}

void move(int x, int y, int servo1p, int servo1n, int servo2p, int servo2n, int y1, int y2, int r1, int r2, int w1, int w2){
  if((x & y) >= 54 && (x & y) <= 200){
  	Serial.println("Forward");
    analogWrite(servo1n, 255);
    analogWrite(servo2p, 255);
    analogWrite(servo2n, 0);
    analogWrite(servo1p, 0);
    light(2, y1, y2, r1, r2, w1, w2);
  }
  else if(x >= 54 && x <= 300 && y >= 310 && y <= 974){
  	Serial.println("Right");
    analogWrite(servo1p, 130);
    analogWrite(servo2p, 230);
    analogWrite(servo1n, 0);
    analogWrite(servo2n, 0);
    light(0, y1, y2, r1, r2, w1, w2);
  }
  else if(y >= 54 && y <= 300 && x >= 310 && x <= 974){
  	Serial.println("Left");
    analogWrite(servo1n, 230);
    analogWrite(servo2n, 130);
    analogWrite(servo1p, 0);
    analogWrite(servo2p, 0);
    light(1, y1, y2, r1, r2, w1, w2);
  }
  else if((x & y) >= 970 && (x & y) <= 974){
    Serial.println("Stop");
    analogWrite(servo1p, 0);
    analogWrite(servo2p, 0);
    analogWrite(servo1n, 0);
    analogWrite(servo2n, 0);
    light(3, y1, y2, r1, r2, w1, w2);
      }
}

void loop()
{
  Serial.println("..............");
  int y = state_of_sensorL();
  int x = state_of_sensorR();
  move(x, y, servo1p, servo1n, servo2p, servo2n, y1, y2, r1, r2, w1, w2);
  delay(1500);
}