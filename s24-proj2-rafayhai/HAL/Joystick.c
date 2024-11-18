#include <HAL/Joystick.h>
#define LEFT_THRESHOLD 3000
#define RIGHT_THRESHOLD 17000
#define RIGHT_THRESHOLD_MIN 15000
#define DOWN_THRESHOLD 7900
enum _JoystickDebounceStateLeft { LEFT, NOT_LEFT, RIGHT, NOT_RIGHT, NOT_DOWN, DOWN, NOT_UP, UP };
typedef enum _JoystickDebounceStateLeft JoystickDebounceStateLeft;
/**
 * Constructs a Joystick
 * Initializes the debouncing and output FSMs.
 *

 *
 * @return a constructed Joystick with debouncing and output FSMs initialized
 */
// Initializing the ADC which resides on SoC
void initADC() {
    ADC14_enableModule();

    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1,
                      0
                     );

    // This configures the ADC to store output results
    // in ADC_MEM0 for joystick X.
    // Todo: if we want to add joystick Y, then, we have to use more memory locations
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // This configures the ADC in manual conversion mode
    // Software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}


void startADC() {
   // Starts the ADC with the first conversion
   // in repeat-mode, subsequent conversions run automatically
   ADC14_enableConversion();
   ADC14_toggleConversionTrigger();
}


// Interfacing the Joystick with ADC (making the proper connections in software)
void initJoyStick() {

    // This configures ADC_MEM0 to store the result from
    // input channel A15 (Joystick X), in non-differential input mode
    // (non-differential means: only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0,
                                  ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                  ADC_INPUT_A15,                 // joystick X
                                  ADC_NONDIFFERENTIAL_INPUTS);

    // This selects the GPIO as analog input
    // A15 is multiplexed on GPIO port P6 pin PIN0
    // TODO: which one of GPIO_PRIMARY_MODULE_FUNCTION, or
    //                    GPIO_SECONDARY_MODULE_FUNCTION, or
    //                    GPIO_TERTIARY_MODULE_FUNCTION
    // should be used in place of 0 as the last argument?
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
                                               GPIO_PIN0,
                                               GPIO_TERTIARY_MODULE_FUNCTION);

    // TODO: add joystick Y
    ADC14_configureConversionMemory(ADC_MEM1,
                                   ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                   ADC_INPUT_A9,                 // joystick Y
                                   ADC_NONDIFFERENTIAL_INPUTS);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                                GPIO_PIN4,
                                                GPIO_TERTIARY_MODULE_FUNCTION);


}
Joystick Joystick_construct() {
  // The Joystick object which will be returned at the end of construction
  Joystick Joystick = {0,0};
  initADC();
  initJoyStick();
  startADC();



  // Initialize all buffered outputs of the Joystick
  //Joystick.pushState = RELEASED;
  //Joystick.isTapped = false;

  // Return the constructed Joystick object to the user
  return Joystick;
}
void Joystick_refresh(Joystick* joystick_p) {
    joystick_p->x = ADC14_getResult(ADC_MEM0);
    joystick_p->y = ADC14_getResult(ADC_MEM1);

    static JoystickDebounceStateLeft leftState = NOT_LEFT;
    joystick_p->isTappedToLeft = false;

        switch(leftState) {

            case NOT_LEFT:
                if (joystick_p->x < LEFT_THRESHOLD) {
                    leftState = LEFT;
                    joystick_p->isTappedToLeft = true;
                }
                break;
            case LEFT:
                if (joystick_p->x > LEFT_THRESHOLD) {
                    leftState = NOT_LEFT;
                }

        }
        static JoystickDebounceStateLeft rightState = NOT_RIGHT;
        joystick_p->isTappedToRight = false;
        switch(rightState) {

            case NOT_RIGHT:
                if (joystick_p->x > 12000 ) {
                    rightState = RIGHT;
                    joystick_p->isTappedToRight = true;
                }
                break;
            case RIGHT:
                if (joystick_p->x < 12000) {
                    rightState = NOT_RIGHT;
                }

        }
     static JoystickDebounceStateLeft downState = NOT_DOWN;
    joystick_p->isTappedToDown = false;
    switch(downState) {

        case NOT_DOWN:
            if (joystick_p->y > 3000 ) {
                downState = DOWN;
                joystick_p->isTappedToDown = true;
            }
            break;
        case DOWN:
            if (joystick_p->y < 3000) {
                downState = NOT_DOWN;
            }

    }
    static JoystickDebounceStateLeft upState = NOT_UP;
   joystick_p->isTappedToUp = false;
   switch(upState) {

       case NOT_UP:
           if (joystick_p->y > 12000) {
               upState = UP;
               joystick_p->isTappedToUp = true;
           }
           break;
       case UP:
           if (joystick_p->y < 12000 ) {
               upState = NOT_UP;
           }

   }

}
bool Joystick_isPressedToLeft(Joystick* Joystick_p) {

    if (Joystick_p->x < LEFT_THRESHOLD) {
        return true;
    }
    else {
        return false;
    }


}

//when joystick is up x = 8741 y = 8741
//when joystick is right x = 16103 y = 16105
//when joystick is down x = 7282 y = 7281
//when joystick is left x = 19 y = 19

bool Joystick_isTappedToLeft(Joystick* Joystick_p) {

    return Joystick_p->isTappedToLeft;


}

bool Joystick_isPressedToRight(Joystick* Joystick_p) {

    if (Joystick_p->x > 12000) {
        return true;
    }
    else {
        return false;
    }


}

bool Joystick_isTappedToRight(Joystick* Joystick_p) {

    return Joystick_p->isTappedToRight;


}
//down
bool Joystick_isPressedToDown(Joystick* Joystick_p) {

    if (Joystick_p->y > 3000) {
        return true;
    }
    else {
        return false;
    }


}

bool Joystick_isTappedToDown(Joystick* Joystick_p) {

    return Joystick_p->isTappedToDown;


}

bool Joystick_isPressedToUp(Joystick* Joystick_p) {

    if (Joystick_p->y > 12000 ) {
        return true;
    }
    else {
        return false;
    }


}

bool Joystick_isTappedToUp(Joystick* Joystick_p) {

    return Joystick_p->isTappedToUp;


}
