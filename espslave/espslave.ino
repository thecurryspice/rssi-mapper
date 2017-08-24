#include <ESP8266WiFi.h>
#define STATE_LED 0

uint8_t mac[6];
uint8_t *bssid;
String sendStr, _BSSID = "Akhil", _PASSWORD = "12345678";

void initialise()
{
  WiFi.begin(_BSSID,_PASSWORD);
  delay(2000);
  Serial.print("Contacting Host");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(STATE_LED, LOW);
    delay(32);
    digitalWrite(STATE_LED, HIGH);
    delay(468);
  }
  WiFi.macAddress(mac);
}

void networkDetails()  //diagnostic details mostly
{
  bool isCon = false;
  if(WiFi.status() == WL_CONNECTED)
      isCon = true;
  Serial.println(isCon ? "\nConnected" : "\nWaiting to Connect");
  if(isCon)
  {
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());
      bssid = WiFi.BSSID();
      Serial.printf("bssid: %02x:%02x:%02x:%02x:%02x:%02x\n",bssid[0],bssid[1],bssid[2],bssid[3],bssid[4],bssid[5]);
      rssi = WiFi.RSSI();
      Serial.printf("RSSID: %d dBm\n", rssi);
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("Subnet Mask: ");
      Serial.println(WiFi.subnetMask());
      Serial.printf("Gateway: ");
      Serial.println(WiFi.gatewayIP());
      Serial.print("DNS\t#1: ");
      Serial.print(WiFi.dnsIP());
      Serial.print("\n\t#2: ");
      Serial.println(WiFi.dnsIP(1));
  }
  Serial.printf("DHCP Hostname: %s\n",WiFi.hostname().c_str());
  WiFi.macAddress(mac);
  Serial.printf("macAddress: %02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

void getRSSI()
{
  if(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(STATE_LED, HIGH);
    sendStr = "-inf";
  }
  else
  {
  	digitalWrite(STATE_LED, LOW);
    rssi = WiFi.RSSI();
    sendStr = String(rssi);
  }
}

void setup()
{
	Serial.begin(9600);
	pinMode(STATE_LED, OUTPUT);
	initialise();
	networkDetails();
}

void loop()
{
	String recStr = "";
	bool sf = false;
	int set = 0;
	getRSSI();
	while(Serial.available())
	{
		char ch = Serial.read();
		recStr += ch;
	}
	while(recStr.equals("set ssid") && set == 0)
	{
		while(Serial.available())
		{
			char ch = Serial.read();
			recStr += ch;
			set = 1;
		}
		if(set)
		{
			_BSSID = recStr;
			recStr = "";
		}
	}
	while(recStr.equals("set pwd") && set == 0)
	{
		while(Serial.available())
		{
			char ch = Serial.read();
			recStr += ch;
			set = 1;
		}
		if(set)
		{
			_PASSWORD = recStr;
			recStr = "";
		}
	}
	if(recStr.equals("init"))
	{
		initialise();
	}
	Serial.println(sendStr);
	delay(250);
}