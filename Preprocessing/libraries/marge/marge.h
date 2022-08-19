#define ROOM 0  // Define the system room number.
#define VERSION 210506

#define DBUG 0  // set to 1 for Serial Monitor Output
#define BAUDRATE 115200

#define MMODE_REMOTE 8 // only in remoteTx: Select modes
#define MODE_OFF 0
#define MODE_24 1
#define MODE_DEMO 2
#define MODE_MANUAL 3
#define MODE_CLEAN 4
#define MODE_STEP 5    // diagnositic use
#define MODE_CLOCK 6
#define MODE_SETCLOCK 7

// FOLLOWING NOT ON REMOTE UNIT
#define MODE_EMERGENCY 9 // sys to manual/full power
#define ALERT_SWITCH3 10 // Flip status between OFF/AUTO)
#define ALERT_MOTION 11 // PIR motion sensor: motion detected.
#define DATA_IRCAMERA 12 // data coming from bed sensor (Expect; 769 data points) --> data logging.
#define DATA_WHIZPAD 13  // HSU BED SIGNALS --> convert to dataTransfer (BED, STATUS[0,1,2,3])

#define MCHANNEL 8   // Number of output light channels
#define CH_RED 0
#define CH_GREEN 1
#define CH_BLUE 2
#define CH_WW 3
#define CH_IB 4
#define CH_UNDEF  5
#define CH_AMBER_BASE 6
#define CH_UV 7

struct LightStatus{int jmode; int sec;int j[MCHANNEL];}; //  j: manual light intensities
struct LightStatus current, dataTransfer, ls_prev;

/* START camera data... for LCD display.*/
#define TMIN 160 /* minimum temperature in 0.1 C scale */
#define CODE_HOLDER 192  /*MLX pixels divided by number of byte per integer (4 for ESP32) */ 
#define DATA_ARRAY 48
struct IRCamera{ 
  int jmode;
  int motion;
  int start_bit;
  int ir[DATA_ARRAY];
  };
/* END camera data...*/

#define RESOLUTION 16  
#define OFF 0
#define FULL 65535
#define HALF 32768

#if CONTROLLER == 200715 // Generic controller pin assignment
#define PIN_R 15
#define PIN_G 2
#define PIN_B 14
#define PIN_WW 16
#define PIN_IB 17
#define PIN_UN 5
#define PIN_AMBER_BASE 18
#define PIN_UV 19
#elif CONTROLLER == 210519 // Sparkfun (new PCB) controller pin assignment v2-2021/04/09
#define PIN_R 16
#define PIN_G 17
#define PIN_B 4
#define PIN_WW 2
#define PIN_IB 15
#define PIN_UN 5
#define PIN_AMBER_BASE 18
#define PIN_UV 23
#elif CONTROLLER == 20201020//ONLY AIEN  v1-2020/10/20
#define PIN_R 17
#define PIN_G 4
#define PIN_B 0
#define PIN_WW 2
#define PIN_IB 15
#define PIN_UN 5
#define PIN_AMBER_BASE 18
#define PIN_UV 23
#endif
/* REMOTE models */
#if REMOTE_CONTROLLER  == 20 // DOIT ESP32
#define BUT_LEFT 16
#define BUT_DOWN  5
#define BUT_RIGHT 17
#define BUT_UP 18  
#define BUT_SELECT 4
#elif REMOTE_CONTROLLER  == 21 // Sparkfun Thing ESP32
#define BUT_LEFT 19
#define BUT_DOWN  23
#define BUT_RIGHT 18
#define BUT_UP 5  
#define BUT_SELECT 15
#endif
