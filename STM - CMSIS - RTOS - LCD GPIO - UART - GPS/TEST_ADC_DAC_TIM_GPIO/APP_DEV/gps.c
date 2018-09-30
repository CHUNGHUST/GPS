
#include <string.h>
#include <stdlib.h>     /* atof */
#include "gps.h"

char frame[]="$GPGGA"; 
char gps_data[24][32];

void GPS_read(char* gps_buffer, str_gps* gps)
{
	int var,info;
	info = 0;
	var = 0;	
	
 	for(int i=0; i<100 && *gps_buffer != 0 && var<24 && info<32 ; i++)
	{
		if(*gps_buffer == ',')
		{
			var++;
			info = 0;
		}				
		else
		{
			gps_data[var][info] = *gps_buffer ;
			gps_data[var][info+1] = 0;
		 info++;
		}			
		gps_buffer++;
	}
		
	if(strcmp (frame,&gps_data[0][0]) == 0)
	{
		if(gps_data[3][0] == 'N')
		{
			gps->Latitude = atof(&gps_data[2][0]);
		}
		else if (gps_data[3][0] == 'S')
		{
		  gps->Latitude = -1* atof(&gps_data[2][0]);
		}
			 
		if(gps_data[5][0] == 'E')
		{
		  gps->Longitude = atof(&gps_data[4][0]);
		}
		else if (gps_data[5][0] == 'W')
		{
		  gps->Longitude = -1 * atof(&gps_data[4][0]);
		}						
	}
}


