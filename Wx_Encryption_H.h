/*
    Author: Mohamed Ashraf (Wx)
    Date: 31/9/2021
    Type: Header file for encryption functions.
*/

// HEADER GUARDS: __WX_ENCRYPTION_H__H
#ifndef __WX_ENCRYPTION_H__H__
#define __WX_ENCRYPTION_H__H__


// HEADER LIBRARIES USED:
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
//#include <pthread.h>
//#include <unistd.h>
//=========== =========== =========== =========== =========== ===========

/*****************************************************
*                    GLOBAL DEFINES                  *
******************************************************/
// IMPORTANT KEYBOARD KEYS(ASCII):
// BACKSPACE:
#define BKSP 8
// ENTER:
#define ENTER 13
// ESCAPE:
#define ESC 27
// SPACE:
#define SPACE 32
// TAB:
#define TAB 9

/*****************************************************
*                    FUNCTION DECLARED               *
******************************************************/
// FUNCTION TO DECODE MESSEGE:
void MESSEGE_DECODER(char *);
// FUNCTION FOR CONVERTING FROM DECIMAL TO BINARY(STRING_FORMAT):
char cvtD2B_STRING(char *);
// FUNCTION FOR CONVERTING FROM DECIMAL TO BINARY(DECIMAL_FORMAT):
uint32_t cvtD2B_DECIMAL(uint32_t);
// FUNCTION TO GET THE SUM FOR MESSGE:
void CHECKSUMS(uint32_t);
// FUNCTION TO GET THE POLYNOMIAL FOR MESSEGE:
void MESSEGE_POLYNOMIAL(uint16_t);
// FUNCTION TO CALCULATE THE CRC:
void CRC16_CALCULATOR(char *);

/*****************************************************
*                 GLOBAL VARIABLES                   *
******************************************************/
// CRC-16Bits-KEYS (Prof.koopman):
#define CRC16_XMODEM_KEY 	0x1021
#define CRC16_HD6_KEY    1001111010110010
#define CRC16_HD5_KEY    1010110010011010
#define CRC16_HD4_KEY    1101000101110101

char
  DATA_DECIMAL[100] = {},
 *DATA_DECIMAL_POINTER = DATA_DECIMAL;

char
  DATA_STRING[200] = {},
 *DATA_STRING_POINTER = DATA_STRING;

uint16_t
  POLYNOMIAL_POSITION[200] = {},
 *POLYNOMIAL_POSITION_POINTER = POLYNOMIAL_POSITION;
uint8_t
  STRING_DATA[300] = {},
 *STRING_DATA_POINTER = STRING_DATA;

uint16_t GLOBAL_COUNTER = 0;
uint16_t MESSEGE_LENGTH_TRACKER = 0;
uint16_t STRING_BIT_LENGTH_TRACKER = 0;

/*****************************************************
*                  MAIN FUNCTIONS                    *
******************************************************/
// DECODE THE MESSEGE RECIVED:
void MESSEGE_DECODER(char *messege_string)
{
  uint16_t counter = 0;
  uint16_t DECIMAL_SUM = 0;

  while(messege_string[counter] != '\0')
  {
    cvtD2B_STRING(&messege_string[counter]);

    DECIMAL_SUM += messege_string[counter];
    counter++;

    MESSEGE_LENGTH_TRACKER++;
  }; printf("\n");

  printf("\n Decimal sum: %d\n",DECIMAL_SUM);
  CHECKSUMS(DECIMAL_SUM);
}//end MESSEGE_DECODER.

// CHECK SUM OF MESSEGE:
void CHECKSUMS(uint32_t decimal_sum)
{
  uint32_t not_decimal_sum = 0;

  printf("\n CHECKSUM(BIN): ");
  cvtD2B_DECIMAL(decimal_sum);

  // Getting ones complement for it.
  printf("\n Ones Complement(BIN): ");
  not_decimal_sum = ~decimal_sum;
  cvtD2B_DECIMAL(not_decimal_sum);

  printf("\n");
}//end CHECKSUMS.

//CRC CALCULATOR:
void CRC16_CALCULATOR(char *messege)
{


}//end CRC16_CALCULATOR.
/*****************************************************
*                  SUB - FUNCTIONS                    *
******************************************************/
// Convert decimal to binary function:
char cvtD2B_STRING(char *messege)
{
  int16_t temp = 0;

  uint8_t COUNTER = 0;
  static uint16_t POSITION_COUNTER = 0;

  for(COUNTER = 7; COUNTER >= 0; COUNTER--)
  {
    temp = (*messege) >> COUNTER;

    if(temp & 1)
    {
      // STORE THE DATA act(NON-VOLATILE MEMORY):
      DATA_STRING_POINTER[GLOBAL_COUNTER] = '1';
      STRING_DATA_POINTER[GLOBAL_COUNTER] =  1;
      GLOBAL_COUNTER++;

      // TRACK THE BIT_LENGTH:
      STRING_BIT_LENGTH_TRACKER += 1;

      // TRACK THE BIT POSITION:
      POSITION_COUNTER += 1;
      POLYNOMIAL_POSITION_POINTER[GLOBAL_COUNTER] = POSITION_COUNTER;

      printf("1");
    }
    else
    {
      // STORE THE DATA act(NON-VOLATILE MEMORY):
      DATA_STRING_POINTER[GLOBAL_COUNTER] = '0';
      STRING_DATA_POINTER[GLOBAL_COUNTER] =  0;
      GLOBAL_COUNTER++;

      // TRACK THE BIT_LENGTH:
      STRING_BIT_LENGTH_TRACKER += 1;

      // TRACK THE BIT POSITION: (POSITIONING)
      POSITION_COUNTER += 1;

      printf("0");
    };// end else.
    if(COUNTER == 0) {/*printf(" ");*/ break;}
  };// end for.
  return 0;
}// end d2bCVT.

// Convert decimal to binary function:
uint32_t cvtD2B_DECIMAL(uint32_t DATA)
{
  int16_t _TEMP = 0;
  uint8_t COUNTER = 0;

  // 16 BIT REGISTER.
  for (COUNTER = 16; COUNTER >= 0; COUNTER--)
  {
    _TEMP = DATA >> COUNTER;

    if (_TEMP & 1)
    {
      // STORE THE DATA act(NON-VOLATILE MEMORY):
      DATA_DECIMAL_POINTER[GLOBAL_COUNTER] = '1';
      GLOBAL_COUNTER++;

      printf("1");
    }
    else
    {
      // STORE THE DATA act(NON-VOLATILE MEMORY):
      DATA_DECIMAL_POINTER[GLOBAL_COUNTER] = '0';
      GLOBAL_COUNTER++;

      printf("0");
    };// end else.
    if(COUNTER == 0) {printf(" "); break;}
  };// end for.
  return 0;
}// end d2bCVT.

// DISPLAYING THE POLYNOMIAL FOR MESSEGE:
void MESSEGE_POLYNOMIAL(uint16_t _COUNTER)
{
  printf("\n POLYNOMIAL CODE: ");

  while(_COUNTER <= STRING_BIT_LENGTH_TRACKER)
  {
    // HIGH-BIT POSITION (POLYNOMIAL TRACK):
    if(POLYNOMIAL_POSITION_POINTER[_COUNTER] != 0)
      {printf("%dx ", POLYNOMIAL_POSITION_POINTER[_COUNTER]);}
      /*
    else
      {printf("0x ");}
      */
    _COUNTER += 1;
  }
}
//=========== =========== =========== =========== =========== ===========
#endif // __WX_ENCRYPTION_H__H__
