#include <AccelStepper.h>
#include <MultiStepper.h>

//This example will use a static IP ttrol the switching of a relay. Over LAN using a web browser. 
//A lot of this code have been resued the example on the ESP8266 Learning Webpage below. 
//http://www.esp8266learning.com/wemoserver-example.php

//CODE START 
//1
#include <ESP8266WiFi.h>

// Below you will need to use your owI informaiton.
//2
const char* ssid = "FiOS-JF2XA_UPSTAIRS"; //WIFI Name, WeMo will only connect to a 2.4GHz network.
const char* password = "hear9649dot0430sit"; //WIFI Password

//defining the pin and setting up thever"
//3
WiFiServer server(80);
IPAddress ip(192, 168, 1, 100); // whx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); //gateway to match your network
IPAddress subnet(255, 255, 255, 0); // subnet mask to match your network

AccelStepper stepper1(1,D0,D5);


// void setup is where we initialize variables, pin modes, start using libraries, etc. 
//The setup function will only run once, after each powerup or reset of the wemos board.
//4
void setup() {
  Serial.begin(115200);
  delay(10);
  stepper1.setMaxSpeed(1000);

  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  //5
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  //Trying to connect it will display dots
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

//void loop is where you put all your code. it is a funtion that returns nothing and will repeat over and over again
//6
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //Match the request, checking to see what the currect state is
  int value = LOW;
  if (request.indexOf("/motor=ON") != -1) {
    stepper1.setSpeed(500);
    stepper1.runSpeed();
    value = HIGH;
  } 
  if (request.indexOf("/motor=REVERSE") != -1){
    stepper1.setSpeed(-500);
    stepper1.runSpeed();
    value = LOW;
  }
  if (request.indexOf("/motor=OFF") != -1){
    stepper1.setSpeed(0);
    stepper1.runSpeed();
    value = LOW;
  }
  // Return the response, build the html page
  //7
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Relay is now: ");
 
  if(value == HIGH) {
    client.print("Engaged (ON)");  
  } else {
    client.print("Disengaged (OFF)");
  }
  client.println("<br><br><br>");
  client.println("<a href=\"/motor=ON\">Click here to engage (Turn ON) the motor.</a> <br><br><br>");
  client.println("<a href=\"/motor=REVERSE\">Click here to reverse the motor.</a> <br><br><br>");
  client.println("<a href=\"/motor=OFF\">Click here to disengage (Turn OFF) the motor.</a><br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}//END