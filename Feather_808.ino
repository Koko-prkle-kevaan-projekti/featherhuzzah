#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
SoftwareSerial mySerial(3, -1); // RX, TX

// your WiFi network credentials
const char* ssid = "iPhone (nico)";
const char* password = "niconluuri";

// your server IP address and port number
IPAddress serverIP(64, 226, 84, 226);
int serverPort = 65000;

// WiFi client and TCP connection objects
WiFiClient client;
bool connected = false;


void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }

  // Connect to the WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("."); //.... means no wifi connection
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Connect to the server over TCP wificlient.h
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");
    connected = true;
  } else {
    Serial.println("Connection to server failed");
  }
}



void loop() {
   // Read data from the software serial connection on pin 13 of the Mega
  if (mySerial.available()) {
    char data = mySerial.read();
    Serial.print(data);
    if (connected) {
      // Send the data to the server over TCP
      client.write(data);
    }
  }

  // Check for incoming data from the server over TCP
  if (client.available()) {
    char data = client.read();
    Serial.print(data);
  }

  // Check if the TCP connection is still alive
  if (!client.connected()) {
    Serial.println("Server disconnected");
    connected = false;
    client.stop();
    delay(1000);
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
      connected = true;
    } else {
      Serial.println("Connection to server failed");
    }
  }
}
