

typedef struct
{
     char UTC[16];
     double Latitude;
	   char NS[16];
     double Longitude;
	   char EW[16];
     char Fix[16];
		 char Real_Time_Kinematic[16];
     char satellites[16];
     char Horizontal[16];
     char Altitude[16];
	   char sea_level[16];
     char Height[16];
     char checksum[16];
}str_gps;


void GPS_read(char* gps_buffer, str_gps* gps);
