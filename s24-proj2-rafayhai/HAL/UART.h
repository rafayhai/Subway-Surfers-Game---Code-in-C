/*
 * UART.h
 *
 *  Created on: Dec 31, 2019
 *      Author: Matthew Zhong
 *  Supervisor: Leyla Nazhand-Ali
 */

#ifndef HAL_UART_H_
#define HAL_UART_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// Ever since the new API update in mid 2019, the UART configuration struct's
// name changed from [eUSCI_UART_Config] to [eUSCI_UART_ConfigV1]. If your code
// does not compile, uncomment the alternate #define and comment the original
// one.
// -----------------------------------------------------------------------------
// #define UART_Config eUSCI_UART_Config
#define UART_Config eUSCI_UART_ConfigV1

// TODO: define these macros based on the UART module that is connected to USB
// on Launchpad via XDS110

#define USB_UART_PORT GPIO_PORT_P1
#define USB_UART_PINS \
  (GPIO_PIN2 | GPIO_PIN3)  // The pins are given to you for guidance. Also,
                           // because many students miss the parentheses
#define USB_UART_INSTANCE EUSCI_A0_BASE

// An enum outlining what baud rates the UART_construct() function can use in
// its initialization.
enum _UART_Baudrate {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200,
  NUM_BAUD_CHOICES
};
typedef enum _UART_Baudrate UART_Baudrate;

// TODO: Write an overview explanation of what this UART struct does, and how it
//       interacts with the functions below. Consult <HAL/Button.h> and
//       <HAL/LED.h> for examples on how to do this.

//this struct is defines the UART, allowing it to be configurable in regards to a particular
//module Instance at a given port and pin value
//The UART_construct function can use this struct to create a UART with the given parameters

struct _UART {
  UART_Config config;

  uint32_t moduleInstance;
  uint32_t port;
  uint32_t pins;
};
typedef struct _UART UART;

// Constructs a uart using the moduleInstance at the given port and pin
UART UART_construct(uint32_t moduleInstance, uint32_t port, uint32_t pins);

// Sets the baudrate and enables a UART based on the given baudrate enum
void UART_SetBaud_Enable(UART*, UART_Baudrate baudrate);

// TODO: Write a comment which explains what each of these functions does. In
// the
//       header, prefer explaining WHAT the function does, as opposed to HOW it
//       is implemented.

//the UART_hasChar function checks the interrupt status of the UART module to see if the user
//has sent a UART data packet to the board which will consist of a character. The function will return
//true or false depending on if a character was sent
bool UART_hasChar(UART* uart_p);
//this function returns the character that the user entered by sending a UART data packet
char UART_getChar(UART* uart_p);
//this function checks if we are able to send trasmit data and will return either true/false.
bool UART_canSend(UART* uart_p);
//this function will allow a character to be transmitted as a UART data packet
void UART_sendChar(UART* uart_p, char c);

// Updates the UART baudrate to use the new baud choice.
void UART_updateBaud(UART* uart_p, UART_Baudrate baudChoice);

#endif /* HAL_UART_H_ */
