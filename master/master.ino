#include <SoftwareSerial.h>
#define STATE_PIN 6
#define STATE_LED 13
#define CHAR_DELAY 5

String sendStr = "";

SoftwareSerial blt(2,3);
SoftwareSerial esp(4,5)

boolean confirmConnection()
{
	if(digitalRead(STATE_PIN))
		return true;
	Serial.print("Waiting for device");
	while(!digitalRead(STATE_PIN))
	{
    Serial.print(".");
		digitalWrite(STATE_LED, LOW);
		delay(32);
		digitalWrite(STATE_LED, HIGH);
		delay(468);
	}
	//Serial.println("\nConnected");
	delay(100);
  return true;
}

void setup()
{
  pinMode(STATE_PIN, INPUT);
  pinMode(STATE_LED, OUTPUT);
  digitalWrite(STATE_LED, HIGH);
  Serial.begin(9600);
  while(!Serial);
  while(!confirmConnection());
  initialise();
  blt.begin(9600);
  esp.begin(9600);
  blt.println("#Ready :)~");
  delay(2000);
  confirmConnection();
}

void loop()
{
  String rssi = "", esprecStr = "", bltrecStr = "";
  bool rf = false, sf = false;
  while(esp.available())
  {
    char espch = esp.read();
    esprecStr += espch;
    sf = true;
    delay(CHAR_DELAY);
  }
  while(blt.available())
  {
    char bltch = blt.read();
    bltrecStr += bltch;
    rf = true;
    delay(CHAR_DELAY);
  }
	if(confirmConnection() && sf)
  {
	  blt.print('#'+esprecStr+'~');
    Serial.print("RSSID:" + rssi + "dBm\n");
  }
  if(rf)
  {
    esp.print(bltrecStr);
    Serial.println("TO_ESP: "+ bltrecStr);
  }
}