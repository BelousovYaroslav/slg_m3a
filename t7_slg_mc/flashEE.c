#include <ADuC7026.h>
#include <string.h>

void flashEE_configure( void) {
  FEEMOD = 0x8;				// bit 3 should be set to allow erase/write command
}

int flashEE_load_short( unsigned short int addr, unsigned short *result) {
  unsigned char status;
	FEEADR = addr;
	FEECON = 0x01;				// single read command
	
  status = FEESTA & 0x03;
  while (!(status))
    status = FEESTA & 0x03;
  
  memcpy( result, &FEEDAT, 2);
	
  if( ( status & 0x02) == 0x02)
    return 1;
  else
    return 0;
}

int flashEE_save_short( unsigned short int addr, unsigned short data) {
  unsigned char status = 0;

	FEEADR = addr;				// set data address
	FEEDAT = data;				// set data value
	FEECON = 0x02;				// single Write command
	
  status = FEESTA & 0x03;
	while( !( status))
    status = FEESTA & 0x03;
	
  if( ( status & 0x02) == 0x02)
  	return 1;
  else
    return 0;
}

int flashEE_load_text( unsigned short int addr, char *buf, int nChars) {
  unsigned char status = 0;
  int i;

  for( i = 0; i < nChars; i++) {
	  FEEADR = addr + i*2;
	  FEECON = 0x01;				// single read command
	
    status = FEESTA & 0x03;
    while (!(status))
      status = FEESTA & 0x03;
    
    if( ( status & 0x02) == 0x02)
      return 1;
    
    buf[i] = ( char) FEEDAT;
	}

  if( ( status & 0x02) == 0x02)
    return 1;
  else
    return 0;
}

int flashEE_save_text( unsigned short int addr, char *buf, int nChars) {
  unsigned char status = 0;
  int i;

  for( i = 0; i < nChars; i++) {
	  FEEADR = addr + i*2;		// set data address
	  FEEDAT = buf[i];			// set data value
	  FEECON = 0x02;				// single Write command
	
    status = FEESTA & 0x03;
	  while( !( status))
      status = FEESTA & 0x03;

    if( ( status & 0x02) == 0x02)
  	  return 1;
  }	
    
  if( ( status & 0x02) == 0x02)
  	return 1;
  else
    return 0;
}

int flashEE_erase_page( unsigned short int addr) {
  unsigned char status;
	FEEADR = addr;				// set data address
	FEECON = 0x05;				// erase page command

	status = FEESTA & 0x03;
	while (!(status))
    status = FEESTA & 0x03;

	if( ( status & 0x02) == 0x02) return 1;
 	else return 0;
}

int flashEE_load_int( unsigned short int addr, unsigned int *result) {
  unsigned char status;

  //1st 2-bytes (low)
	FEEADR = addr;
	FEECON = 0x01;				// single read command
	
  status = FEESTA & 0x03;
  while (!(status))
    status = FEESTA & 0x03;

  if( ( status & 0x02) == 0x02)
    return 1;

  memcpy( result, &FEEDAT, 2);

  //2nd 2-bytes (high)
	FEEADR = addr + 2;
	FEECON = 0x01;				// single read command
	
  status = FEESTA & 0x03;
  while (!(status))
    status = FEESTA & 0x03;
  
  memcpy( result + 4, &FEEDAT, 2);
	
  if( ( status & 0x02) == 0x02)
    return 1;
  else
    return 0;
}

int flashEE_save_int( unsigned short int addr, unsigned int data) {
  unsigned char status = 0;

  //1st 2-bytes (low)
	FEEADR = addr;				// set data address
	FEEDAT = data;				// set data value
	FEECON = 0x02;				// single Write command
	
  status = FEESTA & 0x03;
	while( !( status))
    status = FEESTA & 0x03;
	
  if( ( status & 0x02) == 0x02)
  	return 1;
  
  //2nd 2-bytes (high)
  FEEADR = addr + 2;		// set data address
	FEEDAT = (data >> 16);	// set data value
	FEECON = 0x02;				// single Write command
	
  status = FEESTA & 0x03;
	while( !( status))
    status = FEESTA & 0x03;
	
  if( ( status & 0x02) == 0x02)
  	return 1;
  else
    return 0;
}