// Lighting schedule 
#define SVERSION 210615
#define WAKE 23400   // 06:30
#define SLEEP 79200  // 22:00
#define MOTION_HOLD_SEC 300
#define MINTERVAL 21
#define HALF 32767
const struct LightStatus schedule[MINTERVAL]={
// *, sec , R , G , B , WW , IB , User , Amber , UV 
  { 0,0,    {OFF,OFF,OFF,OFF,OFF,OFF,13107,OFF}},
  { 1,WAKE, {OFF,OFF,OFF,OFF,OFF,OFF,13107,OFF}},
  { 2,25200,{22937,OFF,OFF,45874,11796,OFF,OFF,OFF}},
  { 3,28800,{22937,OFF,OFF,45874,11796,OFF,OFF,OFF}},
  { 4,32400,{51117,OFF,OFF,52428,52428,OFF,OFF,OFF}},
  { 5,36000,{51117,OFF,OFF,52428,52428,OFF,OFF,OFF}},
  { 6,39600,{FULL,HALF,HALF,FULL,45874,OFF,OFF,OFF}},
  { 7,43200,{FULL,HALF,HALF,FULL,45874,OFF,OFF,OFF}},
  { 8,45000,{FULL,HALF,HALF,FULL,FULL,OFF,OFF,OFF}},
  { 9,46800,{FULL,HALF,HALF,FULL,FULL,OFF,OFF,OFF}},
  {10,50400,{FULL,HALF,HALF,FULL,FULL,OFF,OFF,OFF}},
  {11,54000,{HALF,OFF,OFF,62258,45874,OFF,OFF,OFF}},
  {12,57600,{HALF,OFF,OFF,62258,45874,OFF,OFF,OFF}},
  {13,61200,{OFF,OFF,OFF,FULL,6553,OFF,OFF,OFF}},
  {14,64800,{OFF,OFF,OFF,FULL,6553,OFF,OFF,OFF}},
  {15,68400,{19660,OFF,OFF,HALF,OFF,OFF,OFF,OFF}},
  {16,72000,{19660,OFF,OFF,HALF,OFF,OFF,OFF,OFF}},
  {17,75600,{19660,OFF,OFF,HALF,OFF,OFF,OFF,OFF}},
  {18,77400,{19660,OFF,OFF,HALF,OFF,OFF,OFF,OFF}},
  {19,SLEEP,{OFF,OFF,OFF,OFF,OFF,OFF,13107,OFF}},
  {20,86400,{OFF,OFF,OFF,OFF,OFF,OFF,13107,OFF}}
};