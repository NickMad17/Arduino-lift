#include <buildTime.h>
#include <microDS3231.h>

#include <GyverOLED.h>
#include <Keypad.h>

  //инициализация переменных
  MicroDS3231 rtc;
  GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
  //Настррйка мембранной клавиатуры
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
//Обьявление функций
void florsUp(int n);
void clock();
void Output();
void input_floor(char key);
char key;

void setup() {
  oled.init();
  oled.clear();
  oled.setScale(1);
  oled.home();
  oled.setCursor(0, 4);
  //rtc.setTime(COMPILE_TIME);     //Для настройки времени с компа (убрать //, загрузить, поставить //, загрузить еще раз )
  DateTime now = rtc.getTime();
  rtc.setTime(now);

}
//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
    int s = 0;
    bool IsSNew = false;
    int i = 1;

    bool drive = false;
    int aim_floor = 1;
    int tick_5 = 0;
    bool IsTick = false;
    bool star_on = false;
    int f_numb = 0;


void loop() {
  clock();

  Output();

  key = pad.getKey();
  input_floor(key);
}

//Функция вывода 3
 void Output(){

   oled.setCursor(0, 4);
    if (drive) oled.print("Лифт движется");
    else oled.clear(0, 32, 76, 32);
    oled.setCursor(0, 5);
    oled.print("Введите *этаж#");
  
   florsUp(aim_floor);
     
 }

//Функция времени.1
void clock(){
  
  oled.setScale(1);
  if(s < rtc.getSeconds()) IsSNew = true;
  s = rtc.getSeconds();
  oled.setCursor(0, 0);
  oled.print(rtc.getTimeString());
}
//Функция изменения этажа 2
void florsUp(int n){
  drive = false;
  oled.setCursor(0, 3);
  if (i < n && !star_on){       //ЛИФТ ЕДЕТ ВВЕРХ
    if ((s % 3 == 0) && IsSNew){
      i++;
      IsSNew = false;
    } 

    oled.print(i);            //  ВЫВОД ЭТАЖА КОГДА ЕДЕТ ВВЕРХ

    if (s % 2){              //ВЫВОД значка ^
       oled.print("^");
       oled.print("  ");
    } else oled.print(" ");
    drive = true;
    return 0;
    }
  else if (i > n && !star_on){       //ЛИФТ ЕДЕТ ВНИЗ
    if ((s % 3 == 0) && IsSNew){
      i--;
      IsSNew = false;
    } 
    oled.print(i);         //ВЫВОД ЭТАЖА
    if (s % 2){
      oled.print("v");      //Вывод значка v
      oled.print("  ");
    }
    else oled.print(" ");
    drive = true;
    return 0;
  }
  oled.print(i);        //Когда лифт стоит
  oled.print(" ");
}


//Функция ввода этажа с клавиатуры 4.
void input_floor(char key){

  switch (key){
  case '*': 
    if (drive) break;
    oled.setCursor(0, 6);
    oled.clear();
    star_on = true; 
    f_numb = 0;
    break;
  
  case '#':
    if (drive) break;
    star_on = false;
    if (!f_numb) {
      oled.setCursor(0, 6);
      oled.print("Нужно ввести этаж!");
      break;
     } 
    aim_floor = f_numb;
    f_numb = 0;
    oled.setCursor(0, 6);
      oled.print("Ваш этаж - ");
      oled.print(aim_floor);
    break;
  }
  if (star_on && (key != '*')){
    
  
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
      case '0': f_numb = f_numb * 10; break;

  }
}

}

