#include <WiFiNINA.h>

// globally declare WiFi object:
WiFiClient wifiClient;

void setup() {

  // predefine WiFi status as idle:
  int wifiStatus = WL_IDLE_STATUS;
  // (re)try to establish over the air connection:
  while (wifiStatus != WL_CONNECTED) {
    // provide here SSID and passphrase of WiFi:
    wifiStatus = WiFi.begin("...", "...");
    delay(10000);
  }

}

void loop() {

  char serviceAddress[] = "684.236.0.506";
  if (wifiClient.connect(serviceAddress, 8000)) {
    // we have a connection:
    int sensorPin = A0;
    int moisture0To1023 = analogRead(sensorPin);
    int moisturePercentage = map(moisture0To1023, 0, 1023, 100, 0);

    char moisturePercString[] = "000";
    itoa(moisturePercentage, moisturePercString, 10);

    // create URL query part string:
    char queryUrl[] = "GET /?moisture=";
    strcat(queryUrl, moisturePercString);
    strcat(queryUrl, " HTTP/1.1");

    // print URL query part to WiFi client:
    wifiClient.println(queryUrl);

    char hostString[] = "Host: ";
    strcat(hostString, serviceAddress);

    wifiClient.println(hostString);

    wifiClient.println("Connection: close");
    wifiClient.println();
    wifiClient.flush();

    delay(43200000); // wait half a day
    // delay in milliseconds:
    // 43'200'000 ms = 12 hours * 60 min * 60 sec * 1000 ms

  }


}