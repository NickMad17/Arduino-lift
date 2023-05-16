#include <microDS3231.h>
#include <GyverOLED.h>

MicroDS3231 rtc;

 GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void setup() {
  oled.init();
  oled.clear();
  oled.setScale(2);
  oled.home();
  oled.setCursor(0, 4);



  
  // проверка наличия модуля на линии i2c
  if (!rtc.begin()) {
    oled.print("DS3231 not found");
    for(;;);
  }

  // получаем все данные в структуру
  DateTime now = rtc.getTime();

  // меняем любой параметр
  now.year += 5;
  // now.second;
  // now.minute;
  // now.hour;
  // now.day;
  // now.date;
  // now.month;

  // отправляем в rtc
  rtc.setTime(now);
}

void loop() {
  printTime();
  delay(500);
}

void printTime() {
    oled.setCursor(0, 4);
  // получаем все данные в структуру и используем их
  // этот способ быстрее и "легче" вызова отдельных get-функций
  DateTime now = rtc.getTime();

  oled.print(now.hour);
  oled.print(":");
  oled.print(now.minute);
  oled.print(":");
  oled.print(now.second);
  oled.print(" ");

}
