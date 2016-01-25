#if defined(ARDUINO) && ARDUINO > 18   // Arduino 0019 or later
#include <SPI.h>
#endif
#include <Ethernet.h>
//#include <EthernetDNS.h>  Only needed in Arduino 0022 or earlier
#include <Twitter.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 245 };
Twitter twitter("42260605-VwFJFPiBtUySEwJVOxhnq5u0DXrVrKifsRIfHw3gO");
char msg[] = "Hello, World! I'm Arduino!";

void setup()
{
  delay(1000);
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}

void loop()
{
}
