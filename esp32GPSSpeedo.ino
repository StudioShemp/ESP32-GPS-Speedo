//GPS Speedo by StudioShemp, built initially on ESP32 Devkit V1 but moved to a Firebeetle ESP32-E (DR-0654) for embedded LiPo battery support/portability.


#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <EasyButton.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BUTTON_PIN 27 //button on D4/GPIO27

EasyButton button(BUTTON_PIN);

//On ESP32: GPIO-21(SDA), GPIO-22(SCL)
#define OLED_RESET -1 //Reset pin # (or -1 if sharing ESP32 reset pin)
#define SCREEN_ADDRESS 0x3C //See datasheet for Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

int gpsmode;
double maxgps_speed;
double maxgps_alt;
TinyGPSPlus gps;
String heading;


void onPressed()
{
  gpsmode = gpsmode + 1;
  Serial.println("Mode select pressed - Mode ");
  Serial.print(gpsmode);
  if (gpsmode == 2) {
    gpsmode = 0;
    //    maxgps_speed = 0;
  }
}

void setup() {
  Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // SSD1306_SWITCHCAPVCC = lift display voltage from 3.3V rail.
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 memory allocation failed"));
    for (;;); // stop/endless loop
  }

  display.clearDisplay();
  display.display();
  delay(2000);

  button.begin();
  // Add the callback function to be called when the button is pressed.
  button.onPressed(onPressed);

}

void loop() {
  // Continuously read the status of the button.
  button.read();


  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 600;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if (newData == true)
  {
    newData = false;
    Serial.println(gps.satellites.value());
    if (gpsmode == 0) {
      print_detail();
    }
    else {
      print_max();
    }
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 25);
    display.setTextSize(2);
    display.print("No Signal");
    display.display();
  }

}

void print_detail()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (gps.location.isValid() == 1)
  {
    display.setTextSize(1);
    display.setCursor(2, 5);
    display.print("Mode:Detail");


    display.setTextSize(1);
    display.setCursor(85, 5);
    display.print("SAT:");
    display.print(gps.satellites.value());

    display.setTextSize(1);
    display.setCursor(2, 18);
    display.print("km/h:");
    display.print(gps.speed.kmph());

    if ( gps.speed.kmph() > maxgps_speed) {
      maxgps_speed = gps.speed.kmph();
    }
    display.setCursor(70, 18);
    display.print("max:");
    display.print(maxgps_speed);

    display.setCursor(2, 35);
    display.print(gps.location.lat(), 5);
    display.print(", ");
    display.print(gps.location.lng(), 5);

    heading = gps.cardinal(gps.course.value());

    display.setCursor(5, 50);
    display.print(heading);



    display.setTextSize(1);
    display.setCursor(80, 50);
    display.print("ALT:");
    display.print(gps.altitude.meters(), 0);
    if ( gps.altitude.meters() > maxgps_alt) {
      maxgps_alt = gps.altitude.meters();
    }
    display.display();
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 5);
    display.print("MODE:Detail");
    display.setCursor(0, 25);
    display.setTextSize(2);
    display.print("No Signal");
    display.display();
  }

}

void print_max()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (gps.location.isValid() == 1)
  {

    display.setTextSize(1);
    display.setCursor(2, 5);
    display.print("MODE:Max");


    display.setTextSize(1);
    display.setCursor(85, 5);
    display.print("SAT:");
    display.print(gps.satellites.value());

    //String gps_speed = String(gps.speed.kmph());
    display.setTextSize(3);


    if ( gps.speed.kmph() > maxgps_speed) {
      maxgps_speed = gps.speed.kmph();
    }
    display.setCursor(1, 25);

    display.print(maxgps_speed);
    display.setTextSize(1);
    display.setCursor(90, 25);
    display.print("km/h");
    display.setCursor(30, 50);
    display.print(maxgps_alt);
    display.print(" Alt (m)");
    display.display();
  }
  else
  {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(2, 5);
    display.print("MODE: Max");
    display.setCursor(0, 25);
    display.setTextSize(2);
    display.print("No Signal");
    display.display();
  }

}
