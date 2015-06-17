/***********************************************************************/
/*                                                                     */
/*  SERIAL.C:  Low Level Serial Routines                               */
/*                                                                     */
/***********************************************************************/

#include <aduc7026.H>                      /* ADuC7024 definitions          */

#define CR     0x0D

#pragma INTERWORK

int putchar( int ch)  {                   /* Write character to Serial Port  */
  if( ch == '\n')  {
    while( !( 0x020 == ( COMSTA0 & 0x020)))  {}
	COMTX = CR;							/* output CR */
  }
  
  while( !( 0x020 == ( COMSTA0 & 0x020))) {}
  return( COMTX = ch);
}

int putchar_nocheck( int ch)  {                   /* Write character to Serial Port w/o adding \r to \n */
  while( !( 0x020 == ( COMSTA0 & 0x020))) {}
  return( COMTX = ch);
}

int getchar( void)  {                      /* Read character from Serial Port */
  while( !( 0x01 == ( COMSTA0 & 0x01)))
  {}
  return( COMRX);
}

int write( char * ptr, int len) {
  int i;
  for( i = 0; i < len; i++)
    putchar( *ptr++);
  
  return len;
}

