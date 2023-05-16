//#include <buildTime.h>
#include <microDS3231.h>
MicroDS3231 rtc;
#include <GyverOLED.h>

 GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void setup() {
  oled.init();
  oled.clear();
  oled.setScale(1);
  oled.home();
  oled.setCursor(0, 4);
  //rtc.setTime(COMPILE_TIME);
  DateTime now = rtc.getTime();
  rtc.setTime(now);
  for (int i = 0; i < 20; i++){
   
    oled.print(1234567891);
    oled.print("12345678911");
    oled.setCursor(0, i);
  }
}

void loop() {
  oled.clear(0, 32, 64, 40);
  
  //oled.print(rtc.getTimeString());

}

void clock(){


}
