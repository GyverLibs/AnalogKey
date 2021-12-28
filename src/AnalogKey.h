/*
    Библиотека для работы с аналоговой клавиатурой
    GitHub: https://github.com/GyverLibs/AnalogKey
    - Встроенный простенький дебаунс
    - Оптимальный опрос пина по таймеру
    - Проверка конкретной кнопки или вывод номера нажатой
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    v1.1 - оптимизация, изменена логика размера окна
*/

#ifndef _AnalogKey_h
#define _AnalogKey_h
#include <Arduino.h>

#define _AKEY_PERIOD 40   // период опроса в мс

template <uint8_t PIN, uint8_t AMOUNT, int16_t* S_PTR = nullptr>
class AnalogKey {
public:
    // подключает кнопку на указанное значение
    void attach(uint8_t num, int value) {
        if (num >= AMOUNT) return;
        if (S_PTR == nullptr) signals[num] = value;
        else signals_p[num] = value;
    }

    // устанавливает окно сигнала (умолч. 20)
    void setWindow(int window) {
        _window = window / 2;
    }
    
    // возвращает статус указанной кнопки
    bool status(uint8_t num) {
        if (millis() - tmr > _AKEY_PERIOD) {
            tmr = millis();
            int16_t thisRead = analogRead(PIN);
            _ready = (abs(thisRead - _lastRead) < _window);
            _lastRead = thisRead;		
        }
        return check(num);
    }
    
    // выводит номер нажатой кнопки или -1, если нажатых кнопок нет
    int pressed() {
        status(0);	// вызываем опрос
        for (uint8_t i = 0; i < AMOUNT; i++) {
            if (check(i)) return i;
        }
        return -1;
    }

private:
    bool check(int i) {
        int16_t sig = (S_PTR == nullptr) ? signals[i] : signals_p[i];
        return (_ready && (_lastRead > sig - _window) && (_lastRead < sig + _window));
    }
    
    int16_t signals[(S_PTR == nullptr) ? AMOUNT : 0];
    int16_t* signals_p = S_PTR;
    int16_t _lastRead = 0;
    int16_t _window = 20;
    bool _ready = false;
    uint32_t tmr;
};
#endif