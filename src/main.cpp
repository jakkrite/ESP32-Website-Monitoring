#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArtronShop_LineNotify.h> //Include Libery https://github.com/TridentTD/ArtronShop_LineNotify

const char WIFI_SSID[] = "SSID";        // CHANGE IT
const char WIFI_PASSWORD[] = "PASSWORD";  // CHANGE IT

#define LINE_TOKEN "LINE_TOKENLINE_TOKENLINE_TOKENLINE_TOKEN"  //CHANGE IT https://notify-bot.line.me/en/

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(2, OUTPUT);//LED
}

void WebsiteTracker(String WEB_URL) {
  LINE.setToken(LINE_TOKEN);

  HTTPClient http;

  http.begin(WEB_URL);
  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(".");
      //LINE.send("\n" + WEB_URL + " , Code: " + httpCode);
    } else {
      Serial.printf("%s , Error: %d\n", WEB_URL, httpCode);
      LINE.send("\n" + WEB_URL + " , Error: " + httpCode);
    }
  } else {
    Serial.printf("%s , Error: %d\n", WEB_URL, httpCode);
    //LINE.send("\n" + WEB_URL + " , Error: " + httpCode);
  }
  http.end();

  delay(500);
}

void loop() {
  
  digitalWrite(2, HIGH);  //LED Status

  WebsiteTracker("https://www.website1.com");  //CHANGE IT
  WebsiteTracker("https://www.website2.com");
  WebsiteTracker("https://www.website3.com");
  WebsiteTracker("https://www.website4.com");

  digitalWrite(2, LOW);   //LED Status

  delay(5 * 60 * 1000);  // 5 Minute
  
}