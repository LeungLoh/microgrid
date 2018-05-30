#ifndef _COMMON_H_
#define _COMMON_H_

/*
 * 数据类型声明
 */

typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef signed char         int8;   /*  8 bits */
typedef signed short int    int16;  /* 16 bits */
typedef signed long  int    int32;  /* 32 bits */
typedef signed long  long   int64;  /* 64 bits */

typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
typedef volatile int64      vint64; /* 64 bits */

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
typedef volatile uint64     vuint64; /* 64 bits */

/*
 * 定义带位域的联合体类型
 */
typedef union
{
    uint16  Word;
    uint8   Byte[2];
    struct
    {
        unsigned int b0: 1;
        unsigned int b1: 1;
        unsigned int b2: 1;
        unsigned int b3: 1;
        unsigned int b4: 1;
        unsigned int b5: 1;
        unsigned int b6: 1;
        unsigned int b7: 1;
        unsigned int b8: 1;
        unsigned int b9: 1;
        unsigned int b10: 1;
        unsigned int b11: 1;
        unsigned int b12: 1;
        unsigned int b13: 1;
        unsigned int b14: 1;
        unsigned int b15: 1;
        unsigned int b16: 1;
    };
} Dtype;    //sizeof(Dtype) 为 2
#endif