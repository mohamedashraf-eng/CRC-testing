#include "Wx_Encryption_H.h"

int main(void)
{
  char messege[100];
  char *messege_pointer = messege;

  uint16_t gpc = 0;

// GETTING THE MESSEGE:
  printf("\n Enter messege to decode it: ");
  gets(messege_pointer);  // Get string with spaces in it.

// MESSEGE AFTER BEING DECODED TO BINARY:
  printf("\n Messege coded: ");
  MESSEGE_DECODER(messege_pointer);

// TESTING STORED DATA(POLYNOMIAL):
  MESSEGE_POLYNOMIAL(gpc);


  printf("\n");
  return 0;
};// end main.
