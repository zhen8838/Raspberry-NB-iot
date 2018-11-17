#ifndef __HEXSTRING_H
#define __HEXSTRING_H

#include <stdint.h>

/**************************************************************/
/**************         hexstring接口        ******************/
/**************************************************************/
extern uint8_t *StringToByte(char *pString, uint8_t *pByte);
extern char *ByteToString(char *pByte, char *pString, uint32_t len);
extern char *DecToString(uint32_t Dec, char *pString);
extern char *lstrip(const char *str);
extern char *rstrip(const char *str);
extern char *strip(const char *str);
#endif
