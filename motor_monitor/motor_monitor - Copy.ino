#include <CytronWiFiShield.h>
#include <CytronWiFiClient.h>
#include <SoftwareSerial.h>

const char ssid[] = "Digital Signage";
const char pass[] = "dsdsds123";

const char* host = "192.168.16.12";
const int httpPort = 80;

int tempPin1 = A5;
int vibePin1 = A4;
int tempA;
float vib1;




void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  if(!wifi.begin(12, 13))
  {
    Serial.println(F("Error talking to shield"));
    while(true);
  }
    
  Serial.println(F("Start wifi connection"));
  if(!wifi.connectAP(ssid, pass))
  {
    Serial.println(F("Error connecting to WiFi"));
    while(true);
  }
    
  Serial.print(F("Connected to: "));Serial.println(wifi.SSID());
  Serial.print(F("IP address: "));Serial.println(wifi.localIP());

 
}

void loop() 
{

 //Temperature
  tempA = analogRead(tempPin1);
  float mv = ( tempA/1023.0)*5000;
  float temp1 = mv/10;

  delay(3000);
  vib1 = analogRead(vibePin1);

  //Sending the Data
  ESP8266Client client;
  
  Serial.print("Connecting to ");
  Serial.println(host);
  
  if (!client.connect(host, httpPort))
  {
    Serial.println(F("Failed to connect to server."));
    return;
  }
  
  Serial.println("Connected Succesfully");
  
  String url = "/motor/dbMotor1.php";
  String data1 = "?Temperature="+String(temp1)+"&Vibration="+String(vib1);
  
  Serial.println("Requesting URL: ");
  Serial.println(String("GET ")+url+data1);

  client.print(String("GET ") + url + data1 + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  
  Serial.println(F("Request Sent"));

  int i=5000;
  while (client.available()<=0&&i--)
  {
    delay(1);
    if(i==1) {
      Serial.println(F("Timeout"));
      return;
      }
  }

  while (client.available()>0)
  {
    client.read();
    client.read(); //flush the first "\r\n"
    String line = client.readStringUntil('\r');
    if (line.endsWith("HTTP/1.1 200 OK")) {
      Serial.println(F("Data successfully sent!"));
      Serial.println(" ");
      Serial.println(" ");
    } 
  }

  delay(8000);
  client.stop();
}
