/* camlog.h  VERSION 21.05.17 BY J D WHITE */
/* shared between camera.ino,  datalogESP.ino & datalog_pc.c*/
#define PIXELS 768
#define PIXCOL 32
#define PIXROW 24
#define S_PACKET 192
#define N_PACKET 4
#define TMIN 160
#define TMAX 410   /* TMIN+250, Tmid 310  */
#define WST 280    /* cutoff if below no person */
#define NODATA 127
#define DELAY_CAMERA_PACKET_SEND 100  /* ms to delay between packets to logger*/
#define MODE_TIMECHECK 99 /* indicates data stored on logger to check clock times */
#define IMAGE_RATE 5000 /* send one image every IMAGE_RATE ms */

struct PacketDataCamera{
	int jmode;
	unsigned char id;  // sequenced number of packet  0 < N_PACKET
	char motion;
	unsigned char celcius[S_PACKET];
};

struct CelciusStat{
	int nhigh;
	int nlow;
	double max;
	double min;
	double mean;	
	double sd;
};