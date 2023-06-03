int buttonPinA = 9;
int buttonPinB = 8;
int speedPin = 2;
int speedPinB = 10;
int dirA = 3;
int dirB = 4;
int dirC = 16;
int dirD = 14;
int mSpeed = 255;

int buttonStateA;
int buttonStateB;
int buttonMem = 0;

void direction(int a,int b){
  digitalWrite(dirA,a);
  digitalWrite(dirB,b);
  digitalWrite(dirC,a);
  digitalWrite(dirD,b);
}
void speed(int x){
  digitalWrite(speedPin, x);
  digitalWrite(speedPinB, x);
}
void forward(int time){
  direction(HIGH,LOW);
  speed(HIGH);
  delay(time);
  fastStop(LOW);
  speed(LOW);
}
void reverse(int time){
  direction(LOW,HIGH);
  speed(HIGH);
  delay(time);
  fastStop(LOW);
  speed(LOW);
}
void fastStop(int x){
  digitalWrite(dirA,x);
  digitalWrite(dirB,x);
  digitalWrite(dirC,x);
  digitalWrite(dirD,x);
}

void setup() {
  pinMode(buttonPinA,INPUT);
  pinMode(buttonPinB,INPUT);
  pinMode(speedPin,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(dirC,OUTPUT);
  pinMode(dirD,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonStateA = digitalRead(buttonPinA);
  buttonStateB = digitalRead(buttonPinB);
  if(buttonStateA == HIGH){
    Serial.println("FORWARD");
    forward(200);
  } else if(buttonStateB == HIGH){
      Serial.println("REVERSE");
      reverse(200);
  } else{
    forward(255);
      /*speed(LOW);*/
  }
}
  