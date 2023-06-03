int buttonPinA = D3;
int buttonPinB = D8;
int speedPin = D4;
int speedPinB = D7;
int dirA = D2;
int dirB = D1;
int dirC = D6;
int dirD = D5;
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
  Serial.begin(115200);
  forward(actionTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonStateA = digitalRead(buttonPinA);
  buttonStateB = digitalRead(buttonPinB);
  Serial.println(buttonStateA);
  Serial.println(buttonStateB);
  if(buttonStateB == HIGH){
    Serial.println("FORWARD");
    forward(actionTime);
    isLocked=True;
  } else if(buttonStateB == LOW){
      Serial.println("REVERSE");
      reverse(actionTime);
      isLocked=False;
  } else{
      speed(LOW);
  }
}
  