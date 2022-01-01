#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP_EEPROM.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h> 

const char *ssid="Room_wifi";
const char *password="18092000";
boolean r;
int l0s,l1s,l2s,fan_s;

ESP8266WebServer server(80);

const uint16_t kRecvPin = 14;

IRrecv irrecv(kRecvPin);

decode_results results;
int tem;
const int l0=16;
const int l1=12;
const int l2=05;
const int fan=13;

const int d_led = 2;

void handleRoot(){
  EEPROM.get(0,l0s);
  EEPROM.get(4,l1s);
  EEPROM.get(8,l2s);
  EEPROM.get(12,fan_s);
  String l0bgc,l1bgc,l2bgc,fanbgc;
  if(l0s==0){
    l0bgc="background-color: rgb(255, 242, 128);";
    }
  else{
    l0bgc="background-color: rgb(255, 174, 0);";
    }

  if(l1s==0){
    l1bgc="background-color: rgb(150, 250, 110);";
    }
  else{
    l1bgc="background-color: rgb(21, 255, 0);";
    }

  if(l2s==0){
    l2bgc="background-color: rgb(128, 240, 255);";
    }
  else{
    l2bgc="background-color: rgb(0, 174, 255);";
    }

    
  if(fan_s==0){
    fanbgc="background-color: rgb(250, 141, 205);";
    }
  else{
    fanbgc="background-color: rgb(255, 0, 149);";
    }
  server.send(200,"text/html"," <!DOCTYPE html>\n"
" <html lang=\"en\">  \n"
" <head>  \n"
"     <meta charset=\"UTF-8\">  \n"
"     <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">  \n"
"     <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">  \n"
"     <style>  \n"
"         body{  \n"
"             display: flex;  \n"
"             flex-direction: column;  \n"
"             justify-content: center;  \n"
"             justify-items: center;  \n"
"             background-color: rgb(51, 50, 50);\n"
"         }  \n"
"         h1{  \n"
"             text-align: center; \n"
"             font-size: 7vw;\n"
"             color: white; \n"
"         }\n"
"         h2{\n"
"             font-size: 5vw;\n"
"             color: white;\n"
"             margin: 5vw;\n"
"         }  \n"
"         h3{\n"
"             font-size: 3vw;\n"
"             color: white;\n"
"             margin: 5vw;  \n"
"         }\n"
"         div{  \n"
"             width: 50vw;  \n"
"             height: 20vw;  \n"
"             margin-left: 25vw;  \n"
"             margin-top: 10vh;  \n"
"             border-color:rgb(255, 255, 255) ;  \n"
"             border-width: 1vw;  \n"
"             border-radius: 9vw;  \n"
"             border-style: solid;\n"
"             text-align: center;  \n"
"             justify-content: center;\n"
"             justify-items: center;\n"
"         }  \n"
"         div a{    \n"
"             font-size: 7vw;  \n"
"             text-decoration: none;  \n"
"             display: block;\n"
"             margin-top: 6vw;\n"
"             color: rgb(0, 0, 0);\n"
"         }  \n"
"         #d0{  \n"
+l0bgc+
"         }  \n"
"         #d1{  \n"
+l1bgc+
"         }  \n"
"         #d2{  \n"
+l2bgc+
"         }  \n"
"         #d3{  \n"
+fanbgc+
"         }  \n"
"     </style>  \n"
"     <title>Home control</title>  \n"
" </head>  \n"
" <body>  \n"
"     <h1>Wellcome </h1>  \n"
"     <div id=\"d0\">  \n"
"         <a href='/l0'>Tube 1</a>  \n"
"     </div>  \n"
"     <div id=\"d1\">  \n"
"         <a href='l1'>Tube 2</a>  \n"
"     </div>  \n"
"     <div id=\"d2\">  \n"
"         <a href='l2'>Others</a>  \n"
"     </div>  \n"
"     <div id=\"d3\">  \n"
"         <a href='/fan'>Fan</a>  \n"
"     </div>  \n"
"     <footer>\n"
"         <h1>About</h1>\n"
"         <h2>For more details visit my youtube channel or git profile</h2>\n"
"         <h3>youtube link- https://www.youtube.com/channel/UCK6HlyCjssslr956vJsCFPQ</h3>\n"
"         <h3>Git profile link- https://github.com/rm10078</h3>\n"
"        </footer>\n"
" </body>  \n"
" </html>  ");
  }
void l0_fun(){
      EEPROM.get(0,tem);
      tem = ~tem;
      EEPROM.put(0,tem);
      r=EEPROM.commit();
      handleRoot();
  }
void l1_fun(){
      EEPROM.get(4,tem);
      tem = ~tem;
      EEPROM.put(4,tem);
      r=EEPROM.commit();
      handleRoot();
  }
void l2_fun(){
      EEPROM.get(8,tem);
      tem = ~tem;
      EEPROM.put(8,tem);
      r=EEPROM.commit();
      handleRoot();
  }
void fan_fun(){
      EEPROM.get(12,tem);
      tem = ~tem;
      EEPROM.put(12,tem);
      r=EEPROM.commit();
      handleRoot();
  }
void setup(){
  pinMode(l0,OUTPUT);
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(d_led,OUTPUT);
  EEPROM.begin(20);
  Serial.begin(9600);
  irrecv.enableIRIn();  
  while (!Serial) 
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  delay(2000);
  WiFi.softAP(ssid,password);
  IPAddress myip = WiFi.softAPIP();
  Serial.print("Device ip address : ");
  Serial.println(myip);
  server.on("/",handleRoot);
  server.on("/l0",l0_fun);
  server.on("/l1",l1_fun);
  server.on("/l2",l2_fun);
  server.on("/fan",fan_fun);
  server.begin();
  delay(2000);
  }

void loop(){
  server.handleClient();
  EEPROM.get(0,l0s);
  EEPROM.get(4,l1s);
  EEPROM.get(8,l2s);
  EEPROM.get(12,fan_s);
  digitalWrite(l0,l0s);
  digitalWrite(l1,l1s);
  digitalWrite(l2,l2s);
  digitalWrite(fan,fan_s);
              //webserver code start form here

             //Remote code start from here
  while (irrecv.decode(&results)) {
    serialPrintUint64(results.value,DEC);
    Serial.println("");
    if(results.value == 33441975){
      EEPROM.put(0,0);
      EEPROM.put(4,0);
      EEPROM.put(8,0);
      EEPROM.put(12,0);
      }
    else if(results.value == 33444015){
      EEPROM.get(0,tem);
      tem = ~tem;
      EEPROM.put(0,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }

    else if(results.value == 33478695){
      EEPROM.get(4,tem);
      tem = ~tem;
      EEPROM.put(4,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }

   else if(results.value == 33486855){
      EEPROM.get(8,tem);
      tem = ~tem;
      EEPROM.put(8,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }
   else if(results.value == 33435855){
      EEPROM.get(12,tem);
      tem = ~tem;
      EEPROM.put(12,tem);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
        delay(5);
        digitalWrite(d_led,HIGH);
        delay(5);
        digitalWrite(d_led,LOW);
      }
    r=EEPROM.commit();
    irrecv.resume();
    delay(50);
  }
  
  }
