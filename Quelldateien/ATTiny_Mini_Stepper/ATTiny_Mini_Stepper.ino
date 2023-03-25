/*
 ATTiny Mini Stepper
 ~~~~~~~~~~~~~~~~~~~

 Copyright (C) 2021  Hardi Stengelin: MobaLedLib@gmx.de

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 -------------------------------------------------------------------------------------------------------------


 Hardware:
 ~~~~~~~~~
 The Poti on the A4988 stepper Modul should be adjusted to 0.22V for the mini stepper motor.
 At 0.15V the power is not sufficient at 18V DCC. Vor some reasons its O.K. at 12V.
 The Motor heats up to 45°C.



 CPU Clock:
 ~~~~~~~~~~
 - The NMRADCC library is working with 8 MHz or 16 MHz.
   Make sure that the clock rate in the Arduino IDE is matching
   with the fuses. If they don't match the library is not working.
   If you are not sure the fuses could be set using the
   "Bootloader brennen" menu in the Arduino IDE.

 Programming:
 ~~~~~~~~~~~~
 Use the TinyUniProg and the ATTiny85 adapter board and connect the
 PCB with a 8-wire ribon cable. Don't use the 8-pin header SV3!.

                             ribon kable
                  ~~~~~~~~~~~~~~~~~~~~~~,
                  | |                   |
                =======                 |               Stepper
       O         #####     _T_          |       xxx xxx xxxxxxx
      ===========|IC=|===========       |       =================
                                        |                 |    |
              TinyUniProg               '~~~~~~~~~~~~~~~~~~~~~~~


 Arduino IDE settings:
 ~~~~~~~~~~~~~~~~~~~~~
 Board: "ATtiny25/45/85 (No bootloader)"                  Install board package from https://github.com/SpenceKonde/ATTinyCore
 Chip:  "ATtiny85"
 Clock: "8 MHz (internal)"
 Timer 1 Clock: "CPU (CPU frequency)"
 LTO (1.6.11+ only): "Enabled"
 millis()/micros(): "Enabled"
 Save EEPROM: "EEPROM retained"
 B.O.D. Level "B.O.D. Enabled (2.7v)"                     Prevent EEPROM errors if power is lost

 Programmer: "Arduino as ISP"

 !!! Use "Bootloader brennen" to burn the settings to the ATtiny !!!
 This is important to change the B.O.D. and to use the correct CPU frequency

 Programming the DCC addresses:
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 - Make sure that no DCC accessory commands are sent
 - Connect the "PROG" and the "P_GND" pins
 - Enable/connect the power and release the "PROG" pin within 3 seconds
    => Programm pode ie active. The LED is flashing fast (1 Hz)
 - Send the DCC accessory command for moving the stepper
   Red    = normal direction
   Green  = inverse direction
   => The LED is flashing slow (2 Hz)
 - Send the DCC accessory command for enabling the LED
   Red    = normal function
   Green  = inverse function
   => LED is controlled by the DCC
      End of the programming mode

 Testing/Manual mode
 ~~~~~~~~~~~~~~~~~~~
 The switch could be toggled when connecting the "PROG" pin to ground for a short time (~500ms)
 Attention: Don't press the button while the stepper is moving.
 The LED could be toggled by connecting the "PROG" pin to ground for (~3 seconds)


 Documents:
 ~~~~~~~~~~
 - https://www.opendcc.de/info/dcc/dcc.html
 - https://www.nmra.org/sites/default/files/s-9.2.1_2012_07.pdf
 - https://www.nmra.org/sites/default/files/s-92-2004-07.pdf


 Revision History :
 ~~~~~~~~~~~~~~~~~
 09.06.21:  - Started
 26.07.21:  - Added flag to invert the LED: LED_INVERS
              Added flag to flash the LED debugging: LED_DEBUG
 27.07.21:  - Added acceleration ramp
 28.07.21:  - Configuration of the DCC adresses via the PROG jumper finished
 19.03.23:  - The DCC adresses could only be programmed if the
              prog pins are connected while starting and released within 2 seconds.
            - Store the last switch position to the EEPROM to prevent driving the stepper twice
 20.03.23:  - Push button connected to the prog pins could be used to toggle the switch (press 500ms)
              and the LED (press ~3 seconds)
            - To use the same address for stepper and LED the button has to be pressed after programming
              the stepper address. In this case the LED could be used as status display.
            - Switch pos could be changed while moving per DCC
            - If the power was lost while the movement the stepper will move to the desired position when
              powered up again
 ToDo:
 ~~~~~
 - Unterstützung des MM (Märklin Motorola) Protokolls (Siehe 26.MM2Interface.ino)
 - Überhitzungsschutz einbauen wenn der Motor ständig hin und her bewegt wird.
 - Was macht man bei 3-Wege Weichen?
   Bei Märklin Weichen dürfen nicht beide Antriebe gleichzeitig auf Kurve stehen
   => Man müsste eine zweite Adresse definieren mit welcher der Stepper auf gerade gestellt wird
      wenn der andere Antrieb auf Bogen gestellt wird.
   ==> Die Zentralen (CSx) können das intern Regeln. Probleme gibt es nur bei der MS2
*/

// Disable the warning:                                                                                       // 26.12.19:
//   ... warning: 'EEPROM' defined but not used [-Wunused-variable]
//   static EEPROMClass EEPROM;
// and:
//   ... warning: comparison between signed and unsigned integer expressions [-Wsign-compare]
//
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include <NmraDcc.h>
#pragma GCC diagnostic pop

#include <EEPROM.h>





#define MOVE_TIME           3000     // Moving time [ms] (1000 ms is the minimum time for the miniature stepper. Otherwise steps are lost)
                                     // The real moving time is a little bit longer because of the acceleration ramp
                                     // In the real world the moving time of a switch is ~5 seconds  (0.9 - 6.6 sec according to: http://fahrdienstleiter.cl/elwnantriebe.html)

#define STEPS_TOTAL         1280     // Number of steps to move (1280 for the miniature stepper)              // 19.03.23:  Old 1300
#define MODE                8        // Mode is defined by the mode select jumpers
                                     //   Mode MS1 MS2 MS3
                                     //   1     -   -   -    Full Step (fast)
                                     //   2     X   -   -    1/2 Step
                                     //   4     -   X   -    1/4 Step
                                     //   8     X   X   -    1/8 Step
                                     //   16    X   X   X    1/16 Step (slow)
                                     //
                                     //   X = Jumper present

#define STORE_LED_TO_EEPOM  1        // Store the last state of the LED to the EEPROM and restore it at power on

#define LED_DEBUG           0        // 1 = LED flashes slowly

#define PRESSED             0        // State for the prog. button which
#define RELEASED            1        // is low active

// Mode (Moving time 1 sec):
// 16 =>  25us   20  kHz
//  8 =>  50us   10  kHz
//  4 => 100us   5   kHz
//  2 => 200us   2.5 kHz

// Die Geräuschentwicklung hängt von der Frequenz ab. Dabei ist eine größere
// Frequenz nicht unbedingt besser. Es wird laut wenn Resonanzfrequenzen getroffen werden.
// Niedrige Frequenzen höhrt man lauter und sie werden als unangenehmer empfunden.
// Bei groesseren Frequenzen wird die Frequenz verrauscht. Wie sich das auf die Resonanzen
// auswirkt weiß ich nicht.
//
// Manchmal bleibt der Stepper am unteren Anschlag hängen. Dann muss die Geschwindigkeit
// reduziert werden => Eine Anfahrrampe ist wichtig. Dabei wird die Geschwindigkeit
// Beginnend mit einer Startgeschwindigkeit linear erhöht bis die Zielgeschwindigkeit
// erreicht ist.
// ==> Rampe ist implementiert

#define MIN_RAMP_PERIOD2    (10 * 1000L / MODE / 2)      // Minimal half period for the stepper ramp
#define RAMP_STEPPS         (STEPS_TOTAL/15 * MODE * 2)  // Number of steps for the ramp (STEPS_TOTAL/x)


// Default values if the EEPROM is not programmed
#define ADDR_STEP           1        // DCC address used for the stepper
#define ADDR_LED            2        // DCC address for the LED
#define STEP_INVERS         0
#define LED_INVERS          0        // 0 = Normal, 1 = Invers (Use Invers if transistor Q1 is not used and the LED is connected to +5V)

#define SERIAL_BAUD         115200   // Just for debug with the Nano


#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) // Test with Nano on the Turntable board
   #define DCC_INT_NR       0
   #define DCC_SIGNAL_PIN   2
   #define DISABLE_PIN      6
   #define STEP_PIN         9
   #define DIR_PIN          5
   #define LED_PIN          13

   #define DEBUG            1
#else
   #define DCC_INT_NR       0        //
   #define DCC_SIGNAL_PIN   2        // IC Pin 7             Prog.      ATTiny 85        Prog.
   #define DISABLE_PIN      3        // IC Pin 2                         +-\/-+
   #define STEP_PIN         1        // IC Pin 6             Reset PB5  1|    |8  VCC
   #define DIR_PIN          0        // IC Pin 5    Disable        PB3  2|    |7  PB2    SCK     DCC Inp.
   #define LED_PIN          4        // IC Pin 3    LED        AD2 PB4  3|    |6  PB1    MISO    Step
                                     //                            GND  4|    |5  PB0    MOSI    Dir
   #define DEBUG            0        //                                  +----+
#endif                               //

#define EE_VERSION_STR  "MiniStep"
#define EE_VER_NR       2                                                                                     // 19.03.23:  Old 1
#define EE_CHECK_SIZE   sizeof(EE_VERSION_STR) + 1 // Version string + Ver_Nr

typedef struct
    {
    char     Ver[sizeof(EE_VERSION_STR)];
    uint8_t  Ver_Nr;
    uint16_t Addr_Step;         // DCC address used for the stepper
    uint16_t Addr_Led;          // DCC address for the LED
    uint8_t  Step_Invers;
    uint8_t  LED_Invers;
    int8_t   SwitchPos;                                                                                       // 19.03.23:
  #if STORE_LED_TO_EEPOM
    uint8_t  LED_Value;
  #endif
    } EE_Data_T;

EE_Data_T ee;

NmraDcc  Dcc ;                       // Instance of the NmraDcc class

int8_t   MoveDir          = 0;                                                                                // 20.03.23:  Old: 1

uint32_t Move_Period2     = 1000L * MOVE_TIME / STEPS_TOTAL / MODE / 2; // time for one half micro step [us] => Steps/sec= 500000/Time
uint32_t Period2;
uint32_t Steps_Total      = STEPS_TOTAL; // Number of full steps to move
uint8_t  Mode             = MODE;        // Mode is defined by the mode select jumpers

uint32_t Tot_HSteps       = Steps_Total * 2 * Mode;
uint32_t Act_HSteps       = Tot_HSteps;  // Actual half micro steps
uint32_t End_ACC_Ramp;                   // End step of the acceleration ramp
uint32_t LastTime;
uint8_t  Prog_Mode        = 0;

uint8_t  Boot_Dir_Pin;                                                                                        // 19.03.23:
uint8_t  Old_Dir_Pin  = 2;
uint32_t StartPress;
uint8_t  SameAddr_Allowed = 0;

 #if LED_DEBUG
   uint32_t t_Debug_LED = 0;
#endif

#if DEBUG
  #define printf(Format, ...) printf_proc(F(Format), ##__VA_ARGS__)   // see: https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#else
  #define printf(Format, ...)
#endif

//-------------------------------------------------------
void printf_proc(const __FlashStringHelper *format, ...)
//-------------------------------------------------------
{
  char buf[50];
  va_list ap;
  va_start(ap, format);
  #ifdef __AVR__
     vsnprintf_P(buf, sizeof(buf), (const char *)format, ap); // progmem for AVR
  #else
     vsnprintf  (buf, sizeof(buf), (const char *)format, ap); // for the rest of the world
  #endif
  va_end(ap);
  Serial.print(buf);
}

//----------
void setup()
//----------
{
  #if DEBUG
    Serial.begin(SERIAL_BAUD);
    printf("\nATTiny mini stepper\n");
    printf("Move_Period2=%lius\n", Move_Period2);
    printf("MIN_RAMP_PERIOD2=%lius\n", MIN_RAMP_PERIOD2);
  #endif
  Read_EEPROM();

  // Setup which External Interrupt, the Pin it's associated with that we're using and enable the Pull-Up
  Dcc.pin(DCC_INT_NR, DCC_SIGNAL_PIN, 1);

  // Call the main DCC Init function to enable the DCC Receiver
  Dcc.init( MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0 );

  digitalWrite(DISABLE_PIN, 1);
  pinMode(DISABLE_PIN, OUTPUT);
  pinMode(STEP_PIN,    OUTPUT);
  pinMode(DIR_PIN,     INPUT_PULLUP); // Pin is used as open collector because it's also used to read in the DCC_learn jumper
  pinMode(LED_PIN,     OUTPUT);

  Boot_Dir_Pin = Old_Dir_Pin = digitalRead(DIR_PIN);                                                          // 19.03.23:

  #if STORE_LED_TO_EEPOM
    if (ee.LED_Value)
         digitalWrite(LED_PIN, !ee.LED_Invers);
    else digitalWrite(LED_PIN,  ee.LED_Invers);
  #else
    digitalWrite(LED_PIN,  ee.LED_Invers);
  #endif

  if (ee.SwitchPos ==  2) Start_Move_Stepper( 1); // if the power was lost during then movement               // 20.03.23:
  if (ee.SwitchPos == -2) Start_Move_Stepper(-1);
}

//--------------------------
void Set_Dir_Pin(int8_t Dir)
//--------------------------
{
  if (Dir > 0)
       pinMode(DIR_PIN, INPUT_PULLUP); // Pin is used as open collector
  else {
       digitalWrite(DIR_PIN, 0);
       pinMode(DIR_PIN, OUTPUT);
       }
}

//-----------------------
void Debug_print_EEPROM()
//-----------------------
{
  printf("Addr_Step   %i\n", ee.Addr_Step);
  printf("Addr_Led    %i\n", ee.Addr_Led);
  printf("Step_Invers %i\n", ee.Step_Invers);
  printf("LED_Invers  %i\n", ee.LED_Invers);
#if STORE_LED_TO_EEPOM
  printf("LED_Value   %i\n", ee.LED_Value);
#endif
}

//-----------------
void Write_EEPROM()
//-----------------
// Write the changed bytes to the EEPROM
{
  printf("Updating EEPROM\n");
  Debug_print_EEPROM();
  uint8_t *p = (uint8_t*)&ee;
  for (uint16_t Addr = 0; Addr < sizeof(EE_Data_T); Addr++, p++)
      {
      EEPROM.update(Addr, *p);
      }
}

//----------------
void Read_EEPROM()
//----------------
{
  printf("Read_EEPROM\n");
  strcpy(ee.Ver, EE_VERSION_STR);
  ee.Ver_Nr       = EE_VER_NR;
  // Default values
  ee.Addr_Step    = ADDR_STEP;
  ee.Addr_Led     = ADDR_LED;
  ee.Step_Invers  = STEP_INVERS;
  ee.LED_Invers   = LED_INVERS;

  uint8_t *p = (uint8_t*)&ee;
  uint8_t b;
  uint16_t Addr;

  for (Addr = 0; Addr < sizeof(EE_Data_T); Addr++, p++)
    {
    b = EEPROM.read(Addr);
    if (Addr < EE_CHECK_SIZE)
         {
         printf("%i %c=%02X %02X\n", Addr, b<' ' ? '?':b, b, *p); // Debug
         if (b != *p)
            {
            printf("Writing EEPROM defaults (Head Err @%i)\n", Addr); // Debug
            Write_EEPROM();
            break;
            }
         }
    else *p = b;
    }
  Debug_print_EEPROM();
}

//---------------------------------
void Start_Move_Stepper(int8_t Dir)                                                                           // 20.03.23:  Extracted from notifyDccAccTurnoutOutput
//---------------------------------
// MoveDir must be set to 1 or -1
{
  MoveDir = Dir;
  ee.SwitchPos = 2 * Dir;
  Write_EEPROM();
  #if DISABLE_PIN
    digitalWrite(DISABLE_PIN, 0);
  #endif
  Act_HSteps = 0;
  if (RAMP_STEPPS < Act_HSteps)
       End_ACC_Ramp = Act_HSteps -  RAMP_STEPPS;
  else End_ACC_Ramp = Act_HSteps;
  LastTime = micros();
  Period2 = MIN_RAMP_PERIOD2;
  printf("Start %i\n", MoveDir);
  Set_Dir_Pin(MoveDir);
}

//--------------------------------
void LED_On_Off(uint8_t Direction)
//--------------------------------
{
  if (Direction == 10) // Toggle
     {
     if (ee.LED_Invers)
          Direction =  digitalRead(LED_PIN);
     else Direction = !digitalRead(LED_PIN);
     }
  if (ee.LED_Invers)
       digitalWrite(LED_PIN, !Direction);
  else digitalWrite(LED_PIN,  Direction);
  #if STORE_LED_TO_EEPOM
    ee.LED_Value = Direction;
  #endif
  Write_EEPROM();

  #if LED_DEBUG
      t_Debug_LED = millis();
  #endif
}

//-------------------------------------------------------------------------------------
void notifyDccAccTurnoutOutput( uint16_t Addr, uint8_t Direction, uint8_t OutputPower )
//-------------------------------------------------------------------------------------
// This function is called whenever a normal DCC Turnout Packet is received
{
  //printf("%4li notifyDccAccTurnoutOutput: %i, %i, %02X\n", millis(), Addr, Direction, OutputPower);
  //digitalWrite(LED_PIN, !digitalRead(LED_PIN));

  if (OutputPower > 0)
     {
     switch (Prog_Mode)
        {
        case 1:  ee.Addr_Step = Addr;     Prog_Mode = 2; ee.Step_Invers = Direction; Write_EEPROM(); printf("Addr_Step: %i\n", Addr);
                 break;
        case 2:  if (Addr != ee.Addr_Step || SameAddr_Allowed)
                    {
                    ee.Addr_Led  = Addr;  Prog_Mode = 0; ee.LED_Invers  = Direction; Write_EEPROM(); printf("Addr_Led:  %i\n", Addr);
                    }
                 break;
        }

     if (Addr == ee.Addr_Step)
        {
        int8_t  SwitchPos = ee.SwitchPos;
        if (Direction == ee.Step_Invers)
             { if (MoveDir != -1 && SwitchPos != -1) Start_Move_Stepper(-1);}                                 // 19.03.23:  Added: SwitchPos
        else { if (MoveDir !=  1 && SwitchPos !=  1) Start_Move_Stepper( 1);}                                 //    "
        }
     if (Addr == ee.Addr_Led)
        LED_On_Off(Direction);
     }
}

// It's not possible to disable the writing to the EEPROM in the NmraDcc library
// except by defining the following function
//------------------------------------------------
uint8_t notifyCVWrite( uint16_t CV, uint8_t Value)
//------------------------------------------------
{
  //printf("notifyCVWrite %i %i\n", CV, Value);
  return Value;
}


//-----------------------------
void Check_DCC_Addr_Prog_Pins()
//-----------------------------
// Check if the DCC address programm pins are connected together
{
  uint8_t Act_Dir_Pin = digitalRead(DIR_PIN);
  if (millis() < 3000)                                                                                        // 19.03.23:
       {
       if (Boot_Dir_Pin == PRESSED &&  Act_Dir_Pin == RELEASED)
          {
          Boot_Dir_Pin = RELEASED;
          Prog_Mode = 1;
          }
       }
  else {
       if (Old_Dir_Pin == RELEASED && Act_Dir_Pin == PRESSED)
            StartPress = millis();
       else if (Old_Dir_Pin == PRESSED && Act_Dir_Pin == RELEASED)                                            // 20.03.23:
               {
               uint32_t Duration = millis() - StartPress;
               if (Duration > 100)
                  {
                  if (Prog_Mode == 2)
                       SameAddr_Allowed = 1; // When the button is pressed in programming mode the same addres for LED and stepper is allowed
                  else {
                       if (Duration > 2000)
                            {
                            if (Duration < 5000) LED_On_Off(10); // Toggle the LED by pressing the button for ~3 seconds
                            }
                       else Start_Move_Stepper(ee.SwitchPos * -1); // Toggle the switch position (Button pressed shorter than 2 seconds)
                       }
                  }
               }
       }
  Old_Dir_Pin = Act_Dir_Pin;

  // Flash the LED if the prog mode is active
  static uint32_t Last_LED_time = 0;
  uint32_t t = millis();
  if (Prog_Mode)
     {
     if ((Prog_Mode == 1 && t - Last_LED_time > 500) ||
         (Prog_Mode == 2 && t - Last_LED_time > 1000))
         {
         digitalWrite(LED_PIN, !digitalRead(LED_PIN));
         Last_LED_time = t;
         }
     }
}

//---------
void loop()
//---------
{
  Dcc.process(); // You MUST call the NmraDcc.process() method frequently from the Arduino loop() function for correct library operation

  if (MoveDir)
       {
       if (Act_HSteps < Tot_HSteps)
            {
            if (micros() - LastTime >= Period2)
               {
               if (Act_HSteps < RAMP_STEPPS) // Acceleration ramp active
                    {
                    Period2 = MIN_RAMP_PERIOD2 - (MIN_RAMP_PERIOD2 - Move_Period2) * Act_HSteps / RAMP_STEPPS;
                    if (Period2 < Move_Period2) Period2 = Move_Period2;
                    #if DEBUG
                       //if (Act_HSteps % 50 == 0) printf("Period2:%li\n", Period2);
                    #endif
                    }
               LastTime += Period2;
               digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
               Act_HSteps++;
               }
            }
       else {
            ee.SwitchPos = MoveDir;                                                                           // 19.03.23:
            Write_EEPROM();
            MoveDir = 0;
            printf("Stop\n");
            digitalWrite(DISABLE_PIN, 1);
            Set_Dir_Pin(1);
            }
       }
  else {
       Check_DCC_Addr_Prog_Pins();
       }
 #if LED_DEBUG
   // Debug flash LED
   if (millis() - t_Debug_LED > 3000)
      {
      t_Debug_LED = millis();
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      }
 #endif // LED_DEBUG
}
