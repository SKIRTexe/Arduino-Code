int buttonPinA = 2;
int buttonPinB = 6;
int speedPin = 5;
int speedPinB = 11;
int dirA = 4;
int dirB = 3;
int dirC = 10;
int dirD = 9;
int mSpeed = 255;

int buttonStateA;
int buttonStateB;
int buttonMem = 0;

int actionTime = 200;

bool isLocked = false;

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
  isLocked  = true;
  speed(LOW);
}
void reverse(int time){
  direction(LOW,HIGH);
  speed(HIGH);
  delay(time);
  isLocked = false;
  speed(LOW);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPinA,INPUT);
  pinMode(buttonPinB,INPUT);
  pinMode(speedPin,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(dirC,OUTPUT);
  pinMode(dirD,OUTPUT);
  Serial.begin(9600);
  forward(actionTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStateA = digitalRead(buttonPinA);
  buttonStateB = digitalRead(buttonPinB);
  Serial.println(buttonStateA);
  if(buttonStateA == HIGH){
    Serial.println("FORWARD");
    forward(actionTime);
  } else if(buttonStateB == HIGH){
      Serial.println("REVERSE");
      reverse(actionTime);
  } else{
      speed(LOW);
  }
}
  