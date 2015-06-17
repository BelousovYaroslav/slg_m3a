void flashEE_configure( void);
int flashEE_load_short( unsigned short int addr, unsigned short *result);
int flashEE_load_text( unsigned short int addr, char *resultbuf, int nChars);
int flashEE_save_short( unsigned short int addr, unsigned short data);
int flashEE_save_text( unsigned short int addr, char *buf, int nChars);
int flashEE_erase_page( unsigned short int addr);
int flashEE_load_int( unsigned short int addr, unsigned int *result);
int flashEE_save_int( unsigned short int addr, unsigned int data);