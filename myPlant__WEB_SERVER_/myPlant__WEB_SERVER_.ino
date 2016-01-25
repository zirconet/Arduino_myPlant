#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 8

#include <Ethernet.h>
#include <SPI.h>
#include <Twitter.h>


int sensorPin = A0;    // MOISTURE SENSOR analog input 
int sensorValue = 0;   // declaration sensor value


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   
byte ip[] = { 192, 168, 0, 235 }; // indirizzo IP della shield  
byte gateway[] = { 192, 168, 0, 1 }; // indirizzo ip del router  
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask 
EthernetServer server(80);


void setup() {
  Serial.begin(9600);

  Ethernet.begin(mac, ip, gateway, subnet); 
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  
  sensorValue = analogRead(sensorPin);
  int chk = DHT.read(DHT11_PIN);
  
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 10");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
              client.print("<html><head><title>myPlant</title> <link rel='shortcut icon' type='image/x-icon' href='http://www.logosforwebsites.com/wp-content/uploads/2009/07/favicon.ico' /> <meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' ></head><body>"); 
              client.print("<h1><font color ='#228B22'>Progetto myPlant</font></h1>");
              client.print("<h3>Stato sensori:</h3>");

              client.print("Umidita' terreno = ");
              client.print(sensorValue);
              if (sensorValue < 100){
                client.print(" = Irrigazione buona");
                }else {
                client.print(" = Irrigazione INSUFFICENTE");
              }
              client.print("</br>");
              
              client.print("Umidita' aria = ");
              client.print(DHT.humidity,1);
              client.print("%");
              client.print("</br>");

              client.print("Temperatura aria = ");
              client.print(DHT.temperature,1);
              client.println(" gradi");
              client.print("</br>");
              client.print("</br>");

              if (sensorValue <100) {
                client.print ("<h2><font color='#1E90FF'>TUTTO OK!!!<h2>");
                client.print ("<img src=https://zirconet.files.wordpress.com/2016/01/vaso-di-fiore-che-tiene-un-mazzo-di-fiori-49250471.jpg height='200' width='205'/>");
                } else{
                client.print ("<h2><font color='#FF4500'HO SETE!!!<h2>");
                client.print ("<img src=https://zirconet.files.wordpress.com/2016/01/vaso-di-fiore-che-grida-un-tessuto-49012397.jpg height='200' width='205'/>");    
              }
              
          client.println("</body></html>");    
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    Ethernet.maintain();
  }
  delay(10000);
}

