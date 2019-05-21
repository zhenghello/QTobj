#ifndef __DEFTYPE_H
#define __DEFTYPE_H




/******************************************************************************/
/*                            宏定义                                        */
/******************************************************************************/
/*! exact-width signed integer types */
typedef                   char  int8;
typedef   signed short     int  int16;
typedef   signed           int  int32;
typedef   signed       __int64  int64;

/*! exact-width unsigned integer types */
typedef unsigned          char  uint8;
typedef const unsigned    char  cuint8;
typedef unsigned short     int  uint16;
typedef unsigned           int  uint32;
typedef unsigned       __int64  uint64;

/* float define */
typedef float                   float32;
typedef double                  double64;

//返回成功
#ifndef EXIT_SUCCESS_LOCOAL
 #define EXIT_SUCCESS_LOCOAL           (0)
#endif

//返回失败
#ifndef EXIT_FAILURE_LOCOAL
 #define EXIT_FAILURE_LOCOAL           (-272)
#endif


#ifndef NULL
 #define NULL                   (0)
#endif

#ifndef FALSE
 #define FALSE                  (0)
#endif

#ifndef TRUE
 #define TRUE                   (1)
#endif

#ifndef ENABLE
 #define ENABLE                 (1)
#endif

#ifndef DISABLE
 #define DISABLE                (0)
#endif

//获取数组长度
#ifndef ARRAY_SIZE
 #define __must_be_array(a)     0
 #define ARRAY_SIZE(x)          (sizeof(x)/sizeof((x)[0]) + __must_be_array(x))
#endif

//判断指针是否有效
#define INVALID_POINTER(x)      (NULL == (x))
#define VALID_POINTER(x)        (NULL != (x))

//位定义
#define BIT0                    0x01
#define BIT1                    0x02
#define BIT2                    0x04
#define BIT3                    0x08
#define BIT4                    0x10
#define BIT5                    0x20
#define BIT6                    0x40
#define BIT7                    0x80
#define BIT8                    0x0100
#define BIT9                    0x0200
#define BIT10                   0x0400
#define BIT11                   0x0800
#define BIT12                   0x1000
#define BIT13                   0x2000
#define BIT14                   0x4000
#define BIT15                   0x8000

//字节位操作的宏定义
typedef union 
{
    unsigned char Byte;
    struct
    {
        unsigned char Bit0:1;
        unsigned char Bit1:1;
        unsigned char Bit2:1;
        unsigned char Bit3:1;
        unsigned char Bit4:1;
        unsigned char Bit5:1;
        unsigned char Bit6:1;
        unsigned char Bit7:1;
    } Bitfield;
} byte_bit_t;

/*! short转化成2字节 */
typedef union 
{
    unsigned short int Short;
    unsigned char Byte[2];
} short_byte_t;

/*! float转化成4字节 */
typedef union 
{
    float Float;
    unsigned char Byte[4];
} float_byte_t;

//函数指针定义
typedef void (*pFunProc)(void);


#endif /*!< end __DEFTYPE_H */

/********************************end of file***********************************/
