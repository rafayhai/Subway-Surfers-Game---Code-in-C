#ifndef HAL_JOYSTICK_H_
#define HAL_JOYSTICK_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

struct _Joystick {

    uint_fast16_t x;
    uint_fast16_t y;

    bool isTappedToLeft;
    bool isTappedToRight;
    bool isTappedToDown;
    bool isTappedToUp;


};
typedef struct _Joystick Joystick;

/** Constructs a new Joystick object, given a valid port and pin. */
Joystick Joystick_construct();

/** Given a Joystick, determines if the switch is currently pressed left */
bool Joystick_isPressedToLeft(Joystick* Joystick);

/** Given a Joystick, determines if it was "tapped" to left - it went from middle to left */
bool Joystick_isTappedToLeft(Joystick* Joystick);

bool Joystick_isPressedToRight(Joystick* Joystick_p);

bool Joystick_isTappedToRight(Joystick* Joystick_p);

bool Joystick_isPressedToDown(Joystick* Joystick_p);
bool Joystick_isTappedToDown(Joystick* Joystick_p);
bool Joystick_isPressedToUp(Joystick* Joystick_p);
bool Joystick_isTappedToUp(Joystick* Joystick_p);
/** Refreshes this Joystick so the Joystick FSM by polling its x and y channel  */
void Joystick_refresh(Joystick* joystick_p);
#endif /* HAL_JOYSTICK_H_ */
