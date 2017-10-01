#ifndef SHT21_H_INCLUDED
#define SHT21_H_INCLUDED

void sht21_init();
unsigned short MeasTemp();
unsigned short MeasHumid();
unsigned short readMeas();
char sht21_soft_reset();



#define MES_TEMP 	0x01
#define MES_HUM		0x02

void RTC_Write_Sec( char sec );
void RTC_Write_Sec1( char sec );

void RTC_Write_Min( char min );
void RTC_Write_Hour( char hour );
void RTC_GetData();
void RTC_Restart();
void RTC_Init();
void RTC_GetAll();


#endif
