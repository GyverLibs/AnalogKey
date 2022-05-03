[![Foo](https://img.shields.io/badge/Version-1.1-brightgreen.svg?style=flat-square)](#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)

[![Foo](https://img.shields.io/badge/README-ENGLISH-brightgreen.svg?style=for-the-badge)](https://github-com.translate.goog/GyverLibs/AnalogKey?_x_tr_sl=ru&_x_tr_tl=en)

# AnalogKey
Библиотека для работы с аналоговой клавиатурой для Arduino
- Встроенный простенький дебаунс
- Оптимальный опрос пина по таймеру
- Проверка конкретной кнопки или вывод номера нажатой

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **AnalogKey** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/AnalogKey/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
AnalogKey<A0, 16> keys;             // указываем пин и количество кнопок
AnalogKey<A0, 16, signals> keys;    // указываем пин, количество кнопок и внешний массив сигналов
```

<a id="usage"></a>
## Использование
```cpp
void attach(uint8_t num, int value);    // подключает кнопку на указанное значение
void setWindow(int window);             // устанавливает окно сигнала (умолч. 40)
bool status(uint8_t num);               // возвращает статус указанной кнопки
int pressed();                          // выводит номер нажатой кнопки или -1, если нажатых кнопок нет
```
### Как работать
- Измерить и записать сигналы с клавиатуры (например, вывести значения в монитор порта)
- Передать значения в библиотеку:
    - Положить во внешний массив и передать его при инициализации (см. пример)
    - Подключить каждую кнопку через attach (см. пример)
- При необходимости настроить размер окна, чтобы сигналы с кнопок не пересекались: расстояние между соседними сигналами должно быть не меньше половины окна
- Данная библиотека позволяет просто найти нажатую кнопку. Для расширенной работы (клики, удержания) используй библиотеку [EncButton](https://github.com/GyverLibs/EncButton) в виртуальном режиме

<a id="example"></a>
## Пример
### Внешний массив
```cpp
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
```

### Внутренний массив
```cpp
#include "AnalogKey.h"
// указываем пин и количество кнопок
AnalogKey<A0, 16> keys;

void setup() {
  Serial.begin(9600);
  
  // назначаем кнопкам их сигналы
  keys.attach(0, 1023);
  keys.attach(1, 927);
  keys.attach(2, 856);
  keys.attach(3, 783);
  keys.attach(4, 671);
  keys.attach(5, 632);
  keys.attach(6, 590);
  keys.attach(7, 560);
  keys.attach(8, 504);
  keys.attach(9, 480);
  keys.attach(10, 455);
  keys.attach(11, 440);
  keys.attach(12, 399);
  keys.attach(13, 319);
  keys.attach(14, 255);
  keys.attach(15, 230);
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
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - оптимизация, изменена логика размера окна

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!
