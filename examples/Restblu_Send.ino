/*


Modified version of Repeating Wifi Web Client

Sends a Meshblu message to a specific UUID at repeated intervals.




  Repeating Wifi Web client
 
 This sketch connects to a a web server and makes a request
 using an Arduino Wifi shield.
 
 Circuit:
 * Wifi shield attached to pins 10, 11, 12, 13
 
 created 23 April 2012
 by Tom Igoe
 modifide 10 October 2014
 by Moheeb Zara + Aaron Herres
 
 http://arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */

#include <SPI.h> 
#include <WiFi.h>
#include <RESTblu.h>

char ssid[] = "@HomeD8A7" ;      //  your network SSID (name) 
char pass[] = "kickback21" ;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;



// Initialize the Wifi client library
WiFiClient client;

String UUID = "36731e80-4799-11e4-b14a-dd19039b8fdc";
String TOKEN = "ifnpox80e8r7wrk944osy7o3v6zgp66r" ;

RESTblu mesh( UUID , TOKEN );

// server address:
char server[] = "meshblu.octoblu.com";
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    
    
  //  meshblu_send("*", 15);
   // meshblu_recieve();
 lastConnectionTime = millis();
  mesh.send("15", "*", client);
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}





void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





