#include <WiFi.h>
#include <esp_wifi.h>
int minl=0,minp=0;
int pocetL;
int pocetP;
int hodnotaP;
int hodnotaL;
int cas;
#define leva 4 
#define prava 5
void serverOutput(int pocetP,int pocetL);
char* ssid = "ESP32-JENICEK";
IPAddress staticIP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
void setup() {
  pinMode(leva, INPUT);
  pinMode(prava, INPUT);
  Serial.begin(115200)  ;
  Serial.println(ssid);
  WiFi.softAPConfig(staticIP, gateway, subnet);
  WiFi.softAP(ssid);
  Serial.print("ip:");
  Serial.println((WiFi.softAPIP()));
  server.begin();
}
 
 
void loop(){
 WiFiClient client = server.available();    
  if (client) {                            
    Serial.println("New Client.");           
    String currentLine = "";              
    while (client.connected()) {           
      if (client.available()) {            
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            if(minp==0 and digitalRead(prava)==1){
            client.println("----PRUCHOD DO LEVA-");
            cas=millis();
            client.println(cas);
            client.println("-----");
            } 
            client.println("-----");
            if(digitalRead(prava)==0){
             minp=digitalRead(prava); 
            }
            if(digitalRead(prava)==1){
             minp=digitalRead(prava);
            }
            if(minl==0 and digitalRead(leva)==1){
            client.println("----PRUCHOD DO LEVA-");
            cas=millis();
            client.println(cas);
            client.println("-----");
            } 
            client.println("-----");
            if(digitalRead(leva)==0){
             minl=digitalRead(leva); 
            }
            if(digitalRead(leva)==1){
             minl=digitalRead(leva);
            }
            client.println();
            client.print("<meta http-equiv='refresh' contend='1'>");
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
