// This file contains the DCC and LED definitions.
//
// It was automatically generated by the program Prog_Generator_MobaLedLib.xlsm Ver. 3.1.0A      by Hardi
// File creation: 20.12.2021 11:53:54
// (Attention: The display in the Arduino IDE is not updated if Options/External Editor is disabled)

#ifndef __LEDS_AUTOPROG_H__
#define __LEDS_AUTOPROG_H__

#ifndef ARDUINO_RASPBERRY_PI_PICO
#define FASTLED_INTERNAL       // Disable version number message in FastLED library (looks like an error)
#include <FastLED.h>           // The FastLED library must be installed in addition if you got the error message "..fatal error: FastLED.h: No such file or directory"
                               // Arduino IDE: Sketch / Include library / Manage libraries                    Deutsche IDE: Sketch / Bibliothek einbinden / Bibliothek verwalten
                               //              Type "FastLED" in the "Filter your search..." field                          "FastLED" in das "Grenzen Sie ihre Suche ein" Feld eingeben
                               //              Select the entry and click "Install"                                         Gefundenen Eintrag auswaehlen und "Install" anklicken
#else
#include <PicoFastLED.h>       // Juergens minimum version or FastLED for Raspberry Pico
#endif

#include <MobaLedLib.h>

#define START_MSG "LEDs_AutoProg Ver 1: Ver_3.1.0 20.12.21 11:53"

#define TWO_BUTTONS_PER_ADDRESS 1      // Two buttons (Red/Green) are used (DCC/CAN)
#ifdef NUM_LEDS
  #warning "'NUM_LEDS' definition in the main program is replaced by the included 'LEDs_AutoProg.h' with 44"
  #undef NUM_LEDS
#endif

#define NUM_LEDS 44                    // Number of LEDs (Maximal 256 RGB LEDs could be used)

#define LEDS_PER_CHANNEL ",44"

#define RECEIVE_LED_COLOR_PER_RS232
#define USE_EXT_ADDR
#define USE_RS232_OR_SPI_AS_INPUT      // Use the RS232 or SPI Input to read DCC/SX commands from the second Arduino and from the PC (The SPI is only used if enabled with USE_SPI_COM)
#define ADDR_OFFSET 0

#define ADDR_MSK  0x3FFF  // 14 Bits are used for the Address

#define S_ONOFF   (uint16_t)0
#define B_RED     (uint16_t)(1<<14)
#define B_GREEN   (uint16_t)(2<<14)
#define B_RESERVE (uint16_t)(3<<14)    // Not used at the moment
#define B_TAST    B_RED


typedef struct
    {
    uint16_t AddrAndTyp; // Addr range: 0..16383. The upper two bytes are used for the type
    uint8_t  InCnt;
    } __attribute__ ((packed)) Ext_Addr_T;

// Definition of external adressesconst PROGMEM Ext_Addr_T Ext_Addr[] =         { // Addr & Typ    InCnt
           { 1    + S_ONOFF, 1 },      // UhrStunde (pc)         };


// Input channel defines for local inputs and expert users
#define INCH_DCC_1_ONOFF        0      // UhrStunde (pc)

//*** Output Channels ***
#define t0                      1
#define t1                      2
#define t2                      3
#define t3                      4
#define t4                      5
#define t5                      6
#define t6                      7
#define t7                      8
#define t8                      9
#define t9                      10
#define t10                     11
#define t11                     12
#define t12                     13
#define t13                     14
#define t14                     15
#define t15                     16
#define t16                     17
#define t17                     18
#define t18                     19
#define t19                     20
#define t20                     21
#define t21                     22
#define t22                     23
#define t23                     24
#define m0                      25
#define m5                      26
#define m10                     27
#define m15                     28
#define m20                     29
#define m25                     30
#define m30                     31
#define m35                     32
#define m40                     33
#define m45                     34
#define m50                     35
#define m55                     36

/*********************/
#define SETUP_FASTLED()                                                      \
/*********************/                                                      \
  CLEDController& controller0 = FastLED.addLeds<NEOPIXEL, 27>(leds+  0, 44); \
                                                                             \
  controller0.clearLeds(256);                                                \
  FastLED.setDither(DISABLE_DITHER);       // avoid sending slightly modified brightness values
/*End*/

// ----- LED to Var -----
  #define USE_LED_TO_VAR

  #define T_EQUAL_THEN     0
  #define T_NOT_EQUAL_THEN 1
  #define T_LESS_THEN      2
  #define T_GREATER_THAN   3
  #define T_BIN_MASK       4
  #define T_NOT_BIN_MASK   5

  typedef struct
      {
      uint8_t  Var_Nr;
      uint8_t  LED_Nr;
      uint8_t  Offset_and_Typ; // ---oottt    Offset: 0..2
      uint8_t  Val;
      } __attribute__ ((packed)) LED2Var_Tab_T;

  const PROGMEM LED2Var_Tab_T LED2Var_Tab[] =
      {
        // Var name           LED_Nr LED Offset   Typ                Compare value
        { t0,                 1,     (0   << 3) | T_EQUAL_THEN,      0   },        { t1,                 1,     (0   << 3) | T_EQUAL_THEN,      1   },        { t2,                 1,     (0   << 3) | T_EQUAL_THEN,      2   },        { t3,                 1,     (0   << 3) | T_EQUAL_THEN,      3   },        { t4,                 1,     (0   << 3) | T_EQUAL_THEN,      4   },        { t5,                 1,     (0   << 3) | T_EQUAL_THEN,      5   },        { t6,                 1,     (0   << 3) | T_EQUAL_THEN,      6   },        { t7,                 1,     (0   << 3) | T_EQUAL_THEN,      7   },        { t8,                 1,     (0   << 3) | T_EQUAL_THEN,      8   },        { t9,                 1,     (0   << 3) | T_EQUAL_THEN,      9   },        { t10,                1,     (0   << 3) | T_EQUAL_THEN,      10  },        { t11,                1,     (0   << 3) | T_EQUAL_THEN,      11  },        { t12,                1,     (0   << 3) | T_EQUAL_THEN,      12  },        { t13,                1,     (0   << 3) | T_EQUAL_THEN,      13  },        { t14,                1,     (0   << 3) | T_EQUAL_THEN,      14  },        { t15,                1,     (0   << 3) | T_EQUAL_THEN,      15  },        { t16,                1,     (0   << 3) | T_EQUAL_THEN,      16  },        { t17,                1,     (0   << 3) | T_EQUAL_THEN,      17  },        { t18,                1,     (0   << 3) | T_EQUAL_THEN,      18  },        { t19,                1,     (0   << 3) | T_EQUAL_THEN,      19  },        { t20,                1,     (0   << 3) | T_EQUAL_THEN,      20  },        { t21,                1,     (0   << 3) | T_EQUAL_THEN,      21  },        { t22,                1,     (0   << 3) | T_EQUAL_THEN,      22  },        { t23,                1,     (0   << 3) | T_EQUAL_THEN,      23  },        { m0,                 2,     (0   << 3) | T_EQUAL_THEN,      0   },        { m5,                 2,     (0   << 3) | T_EQUAL_THEN,      1   },        { m10,                2,     (0   << 3) | T_EQUAL_THEN,      2   },        { m15,                2,     (0   << 3) | T_EQUAL_THEN,      3   },        { m20,                2,     (0   << 3) | T_EQUAL_THEN,      4   },        { m25,                2,     (0   << 3) | T_EQUAL_THEN,      5   },        { m30,                2,     (0   << 3) | T_EQUAL_THEN,      6   },        { m35,                2,     (0   << 3) | T_EQUAL_THEN,      7   },        { m40,                2,     (0   << 3) | T_EQUAL_THEN,      8   },        { m45,                2,     (0   << 3) | T_EQUAL_THEN,      9   },        { m50,                2,     (0   << 3) | T_EQUAL_THEN,      10  },        { m55,                2,     (0   << 3) | T_EQUAL_THEN,      11  },
      };




//*******************************************************************
// *** Configuration array which defines the behavior of the LEDs ***
MobaLedLib_Configuration()
  {
  RGB_Heartbeat(0)                                                                                            /* Excel row 4                                                                                                                                                                                 */  APatternT2(1,28,0,1,0,255,0,PF_SLOW|PM_NORMAL,144 Sek/16,0/16,24,0)                                         /* UhrStunde (pc)                                                                                                                                                                              */  // LED_to_Var(t0, 0, =, 0)                                                                                  /* Stunde 0                                                                                                                                                                                    */  // LED_to_Var(t1, 0, =, 1)                                                                                  /* Stunde 1                                                                                                                                                                                    */  // LED_to_Var(t2, 0, =, 2)                                                                                  /* Stunde 2                                                                                                                                                                                    */  // LED_to_Var(t3, 0, =, 3)                                                                                  /* Stunde 3                                                                                                                                                                                    */  // LED_to_Var(t4, 0, =, 4)                                                                                  /* Stunde 4                                                                                                                                                                                    */  // LED_to_Var(t5, 0, =, 5)                                                                                  /* Stunde 5                                                                                                                                                                                    */  // LED_to_Var(t6, 0, =, 6)                                                                                  /* Stunde 6                                                                                                                                                                                    */  // LED_to_Var(t7, 0, =, 7)                                                                                  /* Stunde 7                                                                                                                                                                                    */  // LED_to_Var(t8, 0, =, 8)                                                                                  /* Stunde 8                                                                                                                                                                                    */  // LED_to_Var(t9, 0, =, 9)                                                                                  /* Stunde 9                                                                                                                                                                                    */  // LED_to_Var(t10, 0, =, 10)                                                                                /* Stunde 10                                                                                                                                                                                   */  // LED_to_Var(t11, 0, =, 11)                                                                                /* Stunde 11                                                                                                                                                                                   */  // LED_to_Var(t12, 0, =, 12)                                                                                /* Stunde 12                                                                                                                                                                                   */  // LED_to_Var(t13, 0, =, 13)                                                                                /* Stunde 13                                                                                                                                                                                   */  // LED_to_Var(t14, 0, =, 14)                                                                                /* Stunde 14                                                                                                                                                                                   */  // LED_to_Var(t15, 0, =, 15)                                                                                /* Stunde 15                                                                                                                                                                                   */  // LED_to_Var(t16, 0, =, 16)                                                                                /* Stunde 16                                                                                                                                                                                   */  // LED_to_Var(t17, 0, =, 17)                                                                                /* Stunde 17                                                                                                                                                                                   */  // LED_to_Var(t18, 0, =, 18)                                                                                /* Stunde 18                                                                                                                                                                                   */  // LED_to_Var(t19, 0, =, 19)                                                                                /* Stunde 19                                                                                                                                                                                   */  // LED_to_Var(t20, 0, =, 20)                                                                                /* Stunde 20                                                                                                                                                                                   */  // LED_to_Var(t21, 0, =, 21)                                                                                /* Stunde 21                                                                                                                                                                                   */  // LED_to_Var(t22, 0, =, 22)                                                                                /* Stunde 22                                                                                                                                                                                   */  // LED_to_Var(t23, 0, =, 23)                                                                                /* Stunde 23                                                                                                                                                                                   */  APatternT2(2,28,INCH_DCC_1_ONOFF,1,0,12,0,PM_NORMAL,6 Sek,0,12,0)                                           /* UhrStunde (pc)                                                                                                                                                                              */  // LED_to_Var(m0, 0, =, 0)                                                                                  /* Minute 0                                                                                                                                                                                    */  // LED_to_Var(m5, 0, =, 1)                                                                                  /* Minute 5                                                                                                                                                                                    */  // LED_to_Var(m10, 0, =, 2)                                                                                 /* Minute 10                                                                                                                                                                                   */  // LED_to_Var(m15, 0, =, 3)                                                                                 /* Minute 15                                                                                                                                                                                   */  // LED_to_Var(m20, 0, =, 4)                                                                                 /* Minute 20                                                                                                                                                                                   */  // LED_to_Var(m25, 0, =, 5)                                                                                 /* Minute 25                                                                                                                                                                                   */  // LED_to_Var(m30, 0, =, 6)                                                                                 /* Minute 30                                                                                                                                                                                   */  // LED_to_Var(m35, 0, =, 7)                                                                                 /* Minute 35                                                                                                                                                                                   */  // LED_to_Var(m40, 0, =, 8)                                                                                 /* Minute 40                                                                                                                                                                                   */  // LED_to_Var(m45, 0, =, 9)                                                                                 /* Minute 45                                                                                                                                                                                   */  // LED_to_Var(m50, 0, =, 10)                                                                                /* Minute 50                                                                                                                                                                                   */  // LED_to_Var(m55, 0, =, 11)                                                                                /* Minute 55                                                                                                                                                                                   */  // Reserve LEDs(5)                                                                                          /* Excel row 43                                                                                                                                                                                */  ConstRGB(8, t0, 0, 0, 0, 127, 127, 127)                                                                     /* Excel row 44                                                                                                                                                                                */  ConstRGB(9, t1, 0, 0, 0, 127, 127, 127)                                                                     /* Excel row 45                                                                                                                                                                                */  ConstRGB(10, t2, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 46                                                                                                                                                                                */  ConstRGB(11, t3, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 47                                                                                                                                                                                */  ConstRGB(12, t4, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 48                                                                                                                                                                                */  ConstRGB(13, t5, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 49                                                                                                                                                                                */  ConstRGB(14, t6, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 50                                                                                                                                                                                */  ConstRGB(15, t7, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 51                                                                                                                                                                                */  ConstRGB(16, t8, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 52                                                                                                                                                                                */  ConstRGB(17, t9, 0, 0, 0, 127, 127, 127)                                                                    /* Excel row 53                                                                                                                                                                                */  ConstRGB(18, t10, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 54                                                                                                                                                                                */  ConstRGB(19, t11, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 55                                                                                                                                                                                */  ConstRGB(20, t12, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 56                                                                                                                                                                                */  ConstRGB(21, t13, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 57                                                                                                                                                                                */  ConstRGB(22, t14, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 58                                                                                                                                                                                */  ConstRGB(23, t15, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 59                                                                                                                                                                                */  ConstRGB(24, t16, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 60                                                                                                                                                                                */  ConstRGB(25, t17, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 61                                                                                                                                                                                */  ConstRGB(26, t18, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 62                                                                                                                                                                                */  ConstRGB(27, t19, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 63                                                                                                                                                                                */  ConstRGB(28, t20, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 64                                                                                                                                                                                */  ConstRGB(29, t21, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 65                                                                                                                                                                                */  ConstRGB(30, t22, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 66                                                                                                                                                                                */  ConstRGB(31, t23, 0, 0, 0, 127, 127, 127)                                                                   /* Excel row 67                                                                                                                                                                                */  ConstRGB(32, m0, 0, 0, 0, 127, 0, 0)                                                                        /* Excel row 68                                                                                                                                                                                */  ConstRGB(33, m5, 0, 0, 0, 0, 127, 0)                                                                        /* Excel row 69                                                                                                                                                                                */  ConstRGB(34, m10, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 70                                                                                                                                                                                */  ConstRGB(35, m15, 0, 0, 0, 127, 0, 0)                                                                       /* Excel row 71                                                                                                                                                                                */  ConstRGB(36, m20, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 72                                                                                                                                                                                */  ConstRGB(37, m25, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 73                                                                                                                                                                                */  ConstRGB(38, m30, 0, 0, 0, 127, 0, 0)                                                                       /* Excel row 74                                                                                                                                                                                */  ConstRGB(39, m35, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 75                                                                                                                                                                                */  ConstRGB(40, m40, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 76                                                                                                                                                                                */  ConstRGB(41, m45, 0, 0, 0, 127, 0, 0)                                                                       /* Excel row 77                                                                                                                                                                                */  ConstRGB(42, m50, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 78                                                                                                                                                                                */  ConstRGB(43, m55, 0, 0, 0, 0, 127, 0)                                                                       /* Excel row 79                                                                                                                                                                                */
  EndCfg // End of the configuration
  };
//*******************************************************************

//---------------------------------------------
void Set_Start_Values(MobaLedLib_C &MobaLedLib)
//---------------------------------------------
{
}


// if function returns TRUE the calling loop stops
typedef bool(*HandleValue_t) (uint8_t CallbackType, uint8_t ValueId, uint8_t* Value, uint16_t EEPromAddr, uint8_t TargetValueId, uint8_t Options);


#define InCnt_MSK  0x0007  // 3 Bits are used for the InCnt
#define IS_COUNTER (uint8_t)0x80
#define IS_PULSE   (uint8_t)0x40
#define IS_TOGGLE  (uint8_t)0x00
#define COUNTER_ID

typedef struct
    {
    uint8_t TypAndInCnt; // Type bit 7, InCnt bits 0..3, reserved 0 bits 4..6
    uint8_t Channel;
    } __attribute__ ((packed)) Store_Channel_T;

// Definition of channels and counters that need to store state in EEPromconst PROGMEM Store_Channel_T Store_Values[] =         { // Mode + InCnt , Channel
           { IS_TOGGLE + 1 , INCH_DCC_1_ONOFF    },      // UhrStunde (pc)         };






#endif // __LEDS_AUTOPROG_H__
