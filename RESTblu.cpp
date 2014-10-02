
#include "RESTblu.h"



RESTblu::RESTblu(String UUID, String TOKEN)
{

  _UUID = UUID;
  _TOKEN = TOKEN;
 

}


void RESTblu::send(String payload, String target, WiFiClient client) {


 String PostData = "{\"devices\": \"" + target + "\", \"payload\" :" + payload + "}";
  // if there's a successful connection:
  if (client.connect("meshblu.octoblu.com", 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
  client.println("POST /messages HTTP/1.1");
  client.println("Host: meshblu.octoblu.com");
 // client.print(server);
  client.println("User-Agent: microblu");
  client.println("skynet_auth_uuid: ");
  client.print(_UUID);
  client.println("skynet_auth_token: ");
  client.print(_TOKEN);
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.print("Content-Length: ");
  client.println(PostData.length());
  client.println();
  client.println(PostData);
  client.println();
  Serial.println();
    

    // note the time that the connection was made:
    
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }

}
