//use esp-01 with level converter for rx/tx
#include <ESP8266WiFi.h>
const char* ssid = "xxxxx";//type your ssid
const char* password = "xxxxxx";//type your password

WiFiServer server(80);

void setup() {
Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
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
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();
  // Match the request
  if (request.indexOf("/left") != -1) {
   Serial.print("l");
  } 
  if (request.indexOf("/right") != -1){
   Serial.print("r");
  }
  if (request.indexOf("/up") != -1) {
   Serial.print("u");
  } 
  if (request.indexOf("/down") != -1){
   Serial.print("d");
  }
  if (request.indexOf("/stop") != -1){
   Serial.print("s");
  }
  if (request.indexOf("/explore") != -1){
   Serial.print("e");
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println(""); //  do not forget this one
  client.println(request);
}
