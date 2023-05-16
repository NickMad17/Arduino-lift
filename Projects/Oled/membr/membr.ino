#include <GyverOLED.h>
#include <Keypad.h>
using namespace std;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
  //пинф подключения
byte colPins[4] = {8, 7, 6, 5};
byte rowPins[4] = {12, 11, 10, 9};
//массив имен кнопок
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad pad((char*)keys, rowPins, colPins, 4, 4);



void setup() {

  oled.init();
  oled.clear();
  oled.setScale(1);
  oled.home();

}

// Глобальные переменные
  bool star_on = false;
  int f_numb = 0;

void loop() {
char key = pad.getKey();
switch (key){
case '*': star_on = true; break;
case '#':
  star_on = false;
  oled.print("  Ваш этаж - ");
  oled.print(f_numb);
  break;
}
if (star_on && (key != '*')){
  oled.print(key);
  switch (key){
    case '1': f_numb = f_numb * 10 + 1; break;
    case '2': f_numb = f_numb * 10 + 2; break;
    case '3': f_numb = f_numb * 10 + 3; break;
    case '4': f_numb = f_numb * 10 + 4; break;
    case '5': f_numb = f_numb * 10 + 5; break;
    case '6': f_numb = f_numb * 10 + 6; break;
    case '7': f_numb = f_numb * 10 + 7; break;
    case '8': f_numb = f_numb * 10 + 8; break;
    case '9': f_numb = f_numb * 10 + 9; break;
  }
}

}


