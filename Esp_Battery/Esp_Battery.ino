#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  //Setting Screen Height And Width

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80



// function prototypes for HTTP handlers
void handleRoot();              
void handleRequest();
void handleNotFound();

int Current_Value = 0;
int Preset_Value = 85;
int Threshold_Value = 75;

int Pin_Relay = 2;

void setup(){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  pinMode(Pin_Relay, OUTPUT); //Relay Connection
  digitalWrite(Pin_Relay,HIGH);
  Serial.println('\n');
  Serial.println("Working");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(2000);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("NOT");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  // Display static text
  display.println("CONNECTED");
  display.display();

  WiFi.softAP("flash1", "iamtheflash"); //Access point id and pwd In this case Id="flash1" Password="iamtheflash"

  IPAddress myIP = WiFi.softAPIP(); //Get Ip Address == 192.168.4.1
  Serial.print("AP IP address: ");
  Serial.println(myIP);          // Send the IP address of the ESP8266 to the computer

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/command", HTTP_POST, handleRequest); // Call the 'handRequest' function when a POST request is made to URI "/command"
  server.onNotFound(handleNotFound); // When a client requests an unknown URI 

  server.begin(); // Actually start the server
  Serial.println("HTTP server started");
 
}

void loop(void){
  server.handleClient(); // Listen for HTTP requests from clients
  
  return;
}

void handleRoot() {  // When URI / is requested, send a standard web page 
  server.send(200, "text/html", "Wi-fi Remote Control Example");
  return;
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
  return;
}

void handleRequest() { // If a POST request is made to URI /command
  // Validate parameters
  if(!server.hasArg("pin") || !server.hasArg("value") || server.arg("pin") == NULL || server.arg("value") == NULL) { 
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  
  // Get the parameters: pin and value
  String temp = "";          //temporary variable
  temp = server.arg("pin");   // Value of Preset Level and Threshold depending upon the variable value is "true" "false" "preset" threshold"
  String  pin = temp;        
  temp = server.arg("value"); // Value i.e true false preset threshold
  String value = temp;

  Current_Value = pin.toInt();
  
  if(value == "preset")
    {
      Preset_Value = Current_Value; //Setting Preset Value From User
    }  

     if(value == "threshold")
    {
      Threshold_Value = Current_Value; //Setting Threshold Value from user
    }  

  if(value == "true")
    {
      if(Current_Value > Preset_Value-1) //OFF THE RELAY IF Current_Value>=Preset_Value
    {
      digitalWrite(Pin_Relay,LOW);
    }
    DisplayScreen(Current_Value,value);
    }

  if(value == "false")
    {
      if(Current_Value < Threshold_Value+1) //ON THE RELAY IF Current_Value<= Threshold_Value
    {
      digitalWrite(Pin_Relay,HIGH);
    }
    DisplayScreen(Current_Value,value);
    }

  
  Serial.println(pin); //Printing to debug
  Serial.println(value);
  
  server.send(200, "text/html", "Wi-fi Remote Control Example");
  return;
}

void DisplayScreen(int bat_level ,String bat_status ) //Setting Display
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Status :");
  
if(bat_status=="false")
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  // Display static text
  display.println("Discharge");
}

if(bat_status=="true")
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  // Display static text
  display.println("Charge");
}

display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 50);
  // Display static text
  display.println("Level:"+String(bat_level)+"%");
  display.display();
}
