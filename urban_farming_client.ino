#include <WiFiNINA.h>
#include <RTCZero.h>

// globally declare WiFi object:
WiFiClient wifiClient;
// globally declare clock object:
RTCZero rtcZero;

int wifiStatus;

char serviceAddress[] = "684.236.0.506";

bool hasConnection = false;

void setup() {

  // predefine WiFi status as idle:
  wifiStatus = WL_IDLE_STATUS;
  // (re)try to establish over the air connection:
  while (wifiStatus != WL_CONNECTED) {
    // provide here SSID and passphrase of WiFi:
    wifiStatus = WiFi.begin("...", "...");
    delay(10000);
  }

  // set the clock (to current time):
  rtcZero.begin();
  rtcZero.setHours(11);
  rtcZero.setMinutes(35);
  rtcZero.setSeconds(0);
  rtcZero.setDay(28);
  rtcZero.setMonth(12);
  rtcZero.setYear(21);
  // remember to set the clock each time these
  // instructions are uploaded to Arduino

}

void loop() {

  while (wifiClient.connect(serviceAddress, 8000)) {
    // we have a connection:
    int sensorPin = A0;
    int moisture0To1023 = analogRead(sensorPin);
    int moistureValue = map(moisture0To1023, 0, 1023, 100, 0);

    char moistureString[] = "000";
    char currYear[] = "00";
    char currMonth[] = "00";
    char currDay[] = "00";
    char currHours[] = "00";
    char currMin[] = "00";

    itoa(moistureValue, moistureString, 10);
    itoa(rtcZero.getYear(), currYear, 10);
    itoa(rtcZero.getMonth(), currMonth, 10);
    itoa(rtcZero.getDay(), currDay, 10);
    itoa(rtcZero.getHours(), currHours, 10);
    itoa(rtcZero.getMinutes(), currMin, 10);

    // create URL query part string:
    char queryUrl[] = "GET /?moisture=";
    strcat(queryUrl, moistureString);
    strcat(queryUrl, "&time=");
    strcat(queryUrl, currYear);
    strcat(queryUrl, "-");
    strcat(queryUrl, currMonth);
    strcat(queryUrl, "-");
    strcat(queryUrl, currDay);
    strcat(queryUrl, "_");
    strcat(queryUrl, currHours);
    strcat(queryUrl, "-");
    strcat(queryUrl, currMin);
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