#include "AnalogKey.h"
// создаём массив значений сигналов с кнопок
int16_t sigs[16] = {
  1023, 927, 856, 783,
  671,  632,  590,  560,
  504,  480,  455,  440,
  399,  319,  255,  230
};

// указываем пин, количество кнопок и массив значений
AnalogKey<A0, 16, sigs> keys;

void setup() {
  Serial.begin(9600);

  // размер окна опроса такой, чтобы кнопок не пересекались
  // Расстояние между соседними сигналами не меньше половины окна!
  keys.setWindow(30);
}

void loop() {
  // проверяем каждую кнопку в ручном режиме
  if (keys.status(0)) Serial.println("press 0");
  if (keys.status(1)) Serial.println("press 1");
  if (keys.status(2)) Serial.println("press 2");
  if (keys.status(3)) Serial.println("press 3");
  if (keys.status(4)) Serial.println("press 4");
  if (keys.status(5)) Serial.println("press 5");
  if (keys.status(6)) Serial.println("press 6");

  // или выводим номер текущей нажатой (-1 значит ни одна не нажата)
  if (keys.pressed() != -1) Serial.println(keys.pressed());
  delay(10);
}
