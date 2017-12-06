#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <Ethernet.h>
#include <ArduinoJson.h>        // JSON Parser
#define LEDPIN D2
#define SERIAL_BAUD 115200
const char* SSID1="muenchen.freifunk.net";
const char* PASSWD1="";
const char* server = "api.openweathermap.org";
const char* api = "/data/2.5/weather?id=7285134&APPID=745045d2eb881a43fe0d8fe3cde1c979"; //Baden, CH
//const char* api = "/data/2.5/weather?id=3688689&APPID=745045d2eb881a43fe0d8fe3cde1c979"; //Bogota, CO
//const char* api = "/data/2.5/weather?id=1275339&APPID=745045d2eb881a43fe0d8fe3cde1c979"; //Mumbai

String line;
double temperatura;
//int MINUTES=1;

//int SECONDS=30;
int INIT=4000;
int DANCE=2000;
//int MINIMUM=7;
//float qual=0;
//int countDown=0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();
  strip.begin();
  while (!Serial) {} // Wait
  delay(10);
  initializeH();
  clean();
  initializeV();
  initializeV();
  wifi_conn();
  askWetter();
  showWetterFarbe();
}//close setup

void loop() {  
}

void wifi_conn(){
    WiFi.disconnect(1);
    WiFi.begin(SSID1, PASSWD1);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      if (WiFi.status() == WL_NO_SSID_AVAIL){
        Serial.println("Wifi not found");showColorAll(255,0,0);//rojo polska
        }
      Serial.print(".");
      Serial.print(WiFi.status());
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}//close wifi_conn

void askWetter(){
  Serial.print("connecting to ");
  Serial.println(server);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(server, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // We now create a URI for the request
  Serial.print("Requesting URL: ");
  Serial.println(api);
  // This will send the request to the server
  client.print(String("GET ") + api + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.println(line);
  }
  Serial.println();
  Serial.println("closing connection");
  // Memory pool for JSON object tree.
StaticJsonBuffer<2000> jsonBuffer;
// JSON input string.
// Root of the object tree.
// JsonObject& root = jsonBuffer.parseObject(json); cambio de jenny
 JsonObject& root = jsonBuffer.parseObject(line);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  // Fetch values.
  double tempe = root["main"]["temp"];
  temperatura = tempe - 273.15;
  temperatura = 25; //fake value 4 testing
  // Print values.
  Serial.println(temperatura);  
}//close askWetter

void showWetterFarbe(){
  if (temperatura>=30){
    showColorAll(206, 17, 38);//rot
    }
  else if (temperatura<30 && temperatura>=20){
    showColorAll(252, 209, 22);//gelb
    }
  else if (temperatura<20 && temperatura>=10){
    showColorAll(0,128,0);//gruen
    }
  else if (temperatura<10 && temperatura>=5){
    showColorAll(25,25,112);//dunkelblau
    }
  else if (temperatura<5 && temperatura>=0){
    showColor(0,26,25,25,112);//dunkelblau
    showColor(27,54,135,206,235);//blauweiss
    }
  else{
    showColorAll(135,206,235);//blauweiss
    }
  }//end showWetterFarbe

void clean(){
    for(int i = 0; i<=53; i++){
  strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  strip.show(); 
}//end clean

void showColorAll(int r, int g, int b){
    for(int i = 0; i<=53; i++){
  strip.setPixelColor(i, strip.Color(r, g, b));
    }
  strip.show(); 
  }// end showColorAll

void showColor(int a, int e, int r, int g, int b){
    for(int i = a; i<=e; i++){
  strip.setPixelColor(i, strip.Color(r, g, b));
    }
  strip.show(); 
  }// end showColor

void initializeH(){
  //54 LEDs  
  showColor(0,17,252, 209, 22);//amarillo
  showColor(18,35,0, 56, 147); //azul
  showColor(36,53,206, 17, 38); //rojo
  delay(INIT);
 
  showColor(0,17,206, 17, 38); //rojo
  showColor(18,35,252, 209, 22);//amarillo
  showColor(36,53,0, 56, 147); //azul
  delay(INIT);

  showColor(0,17,0, 56, 147); //azul  
  showColor(18,35,206, 17, 38); //rojo
  showColor(36,53,252, 209, 22);//amarillo 
  delay(INIT);
  }

void initializeV(){  
  showColor(0,2,252, 209, 22);//amarillo 
  showColor(3,5,0, 56, 147); //azul  
  showColor(6,8,206, 17, 38); //rojo
  showColor(9,11,252, 209, 22);//amarillo
  showColor(12,14,0, 56, 147); //azul  
  showColor(15,17,206, 17, 38); //rojo
  showColor(18,20,252, 209, 22);//amarillo
  showColor(21,23,0, 56, 147); //azul
  showColor(24,26,206, 17, 38); //rojo
  showColor(27,29,252, 209, 22);//amarillo
  showColor(30,32,0, 56, 147); //azul
  showColor(33,35,206, 17, 38); //rojo
  showColor(36,38,252, 209, 22);//amarillo
  showColor(39,41,0, 56, 147); //azul
  showColor(42,44,206, 17, 38); //rojo
  showColor(45,47,252, 209, 22);//amarillo
  showColor(48,50,0, 56, 147); //azul
  showColor(51,53,206, 17, 38); //rojo 
  delay(DANCE);

//take2
  showColor(0,2,206, 17, 38); //rojo
  showColor(3,5,252, 209, 22);//amarillo
  showColor(6,8,0, 56, 147); //azul  
  showColor(9,11,206, 17, 38); //rojo
  showColor(12,14,252, 209, 22);//amarillo
  showColor(15,17,0, 56, 147); //azul
  showColor(18,20,206, 17, 38); //rojo
  showColor(21,23,252, 209, 22);//amarillo
  showColor(24,26,0, 56, 147); //azul
  showColor(27,29,206, 17, 38); //rojo
  showColor(30,32,252, 209, 22);//amarillo
  showColor(33,35,0, 56, 147); //azul
  showColor(36,38,206, 17, 38); //rojo
  showColor(39,41,252, 209, 22);//amarillo
  showColor(42,44,0, 56, 147); //azul
  showColor(45,47,206, 17, 38); //rojo
  showColor(48,50,252, 209, 22);//amarillo
  showColor(51,53,0, 56, 147); //azul
  delay(DANCE);

//take3
  showColor(0,2,0, 56, 147); //azul
  showColor(3,5,206, 17, 38); //rojo
  showColor(6,8,252, 209, 22);//amarillo
  showColor(9,11,0, 56, 147); //azul  
  showColor(12,14,206, 17, 38); //rojo
  showColor(15,17,252, 209, 22);//amarillo
  showColor(18,20,0, 56, 147); //azul
  showColor(21,23,206, 17, 38); //rojo
  showColor(24,26,252, 209, 22);//amarillo
  showColor(27,29,0, 56, 147); //azul
  showColor(30,32,206, 17, 38); //rojo
  showColor(33,35,252, 209, 22);//amarillo
  showColor(36,38,0, 56, 147); //azul
  showColor(39,41,206, 17, 38); //rojo
  showColor(42,44,252, 209, 22);//amarillo
  showColor(45,47,0, 56, 147); //azul
  showColor(48,50,206, 17, 38); //rojo
  showColor(51,53,252, 209, 22);//amarillo
  delay(DANCE);
  }//close init H
 
