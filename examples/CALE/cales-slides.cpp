/*
   10_Inkplate_Download_And_Show example for e-radionica Inkplate6 original example
   Modified by Martin to make it work with CALE.es web-service for ESP32 displays
   Added deepsleep functionality so it wakes up each N minutes and downloads a new image
*/

#include "Inkplate.h"               //Include Inkplate library to the sketch
#include "HTTPClient.h"             //Include library for HTTPClient
#include "WiFi.h"                   //Include library for WiFi
Inkplate display(INKPLATE_3BIT);    //Create an object on Inkplate library and also set library into 3 Bit mode (Grayscale)

// CALE.es screen URL:
#define SCREEN_URL "http://img.cale.es/bmp/fasani/5ef94f52ad2f6" //BMP 4 bits works partially
//#define SCREEN_URL "http://img.cale.es/jpg/fasani/5ea1dec401890" // JPG 24 bits does not work at all

// Einkplate will sleep this minutes after rendering the image. 
// Please don't make this shorter than once per hour since it's using our shared server!
#define SLIDES_CHANGE_SECONDS 30

char * screenUrl = SCREEN_URL;
uint64_t USEC = 1000000;

void setup() {
  Serial.begin(115200);
  display.begin();        //Init Inkplate library (you should call this function ONLY ONCE)
  display.clearDisplay(); //Clear frame buffer of display
  display.display();      //Put clear image on display

  display.print("Connecting to WiFi...");
  display.partialUpdate();

  //Connect to the WiFi network.
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.partialUpdate();
  }
  display.println("\nWiFi OK! Downloading...");
  display.partialUpdate(); 
}

void loop() {
  //Draw image from CALE.es
  Serial.printf("Rendering screen again from: %s\n",screenUrl);
  //display.fillScreen(WHITE);

  if (!display.drawBitmapFromWeb(screenUrl, 0, 0, false)) {
    //If is something failed (wrong filename or wrong bitmap format), write error message on the screen.
    //REMEMBER! You can only use Windows Bitmap file with color depth of 1, 4, 8 or 24 bits with no compression! 
    display.println("Image open error");
  }
  display.display();
  delay(SLIDES_CHANGE_SECONDS*1000);
}
