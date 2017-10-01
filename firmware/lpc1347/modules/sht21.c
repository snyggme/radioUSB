/*
 * sht21.c
 *
 *  Created on: 22 џэт. 2016 у.
 */
#include "includes.h"

#define SHT21_I2C_ADDR 		0x40
#define SHT21_I2C_ADDR_W 	0x80
#define SHT21_I2C_ADDR_R 	0x81

#define SCL_UP		I2C_SCL = 1
#define SCL_DOWN	I2C_SCL = 0

#define SCL_OUT		I2C_SCL_OUT()
#define SCL_IN		I2C_SCL_IN()

#define SDA_UP		I2C_SDA = 1
#define SDA_DOWN	I2C_SDA = 0

#define SDA_OUT		I2C_SDA_OUT()
#define SDA_IN		I2C_SDA_IN()

#define SCL_VAL		I2C_SCL & 0x01
#define SDA_VAL		I2C_SDA & 0x01

#define I2C_DELAY1      i2c_delay( 20 )
#define I2C_DELAY2	i2c_delay( 20 )

#define ACK		0
#define NACK	1

#define CMD_GET_TEMPERATURE_HM 		0xE3
#define CMD_GET_HUMIDITY_HM 		0xE5

#define CMD_GET_TEMPERATURE_NOHM 	0xF3
#define CMD_GET_HUMIDITY_NOHM 		0xF5

#define CMD_SOFT_RESET 		0xFE

char data_req_flags;

static void i2c_start(void);
static void i2c_stop(void);
static int i2c_wait();
static unsigned char i2c_write8(unsigned char c);
static unsigned char i2c_read8(unsigned char acknack);

static int sht21_start_meas(unsigned char cmd);
static unsigned short sht21_end_read();

        
extern volatile unsigned char Sec_Reg;
extern volatile unsigned char Min_Reg;
extern volatile unsigned char Hr_Reg;
extern volatile unsigned char DOW_Reg;
extern volatile unsigned char DOM_Reg;
extern volatile unsigned char Mon_Reg;
extern volatile unsigned char Yr_Reg;
extern volatile unsigned char Cont_Reg;

extern volatile short RTC[20];

void i2c_delay( int d )
{
  while( d > 1 )
    d--;
}

void sht21_init()
{
  I2C_SCL_OUT();
  I2C_SDA_OUT();
}

unsigned short MeasTemp()
{
  unsigned short res = 0;

  sht21_start_meas(CMD_GET_TEMPERATURE_HM);
//  res = sht21_end_read();
  
  return res;
}

unsigned short MeasHumid()
{
  unsigned short res = 0;

  sht21_start_meas(CMD_GET_HUMIDITY_HM);
//  res = sht21_end_read();
  
  return res;
}

unsigned short readMeas()
{
  unsigned short res;

  res = sht21_end_read();

  return res;
}
char sht21_soft_reset()
{
    if (!i2c_wait())
    	return 0;

	i2c_start();
	if (i2c_write8( SHT21_I2C_ADDR_W ) != ACK)
	{
		i2c_stop();
		return 0;
	}
	if (i2c_write8( CMD_SOFT_RESET ) != ACK)
	{
		i2c_stop();
		return 0;
	}

	i2c_stop();
        
        return 1;
}

static int sht21_start_meas(unsigned char cmd)
{
    if (!i2c_wait())
    	return 0;

	i2c_start();
	if (i2c_write8(SHT21_I2C_ADDR << 1) != ACK)
	{
		i2c_stop();
		return 0;
	}
	if (i2c_write8(cmd) != ACK)
	{
		i2c_stop();
		return 0;
	}

	i2c_start();
	if (i2c_write8((SHT21_I2C_ADDR << 1) | 1) != ACK)
	{
		i2c_stop();
		return 0;
	}
	SCL_IN;
	SCL_UP;

	return 1;
}

static unsigned short sht21_end_read()
{
	unsigned short t;
	t = (unsigned short)i2c_read8(ACK) << 8;
	t |= i2c_read8(NACK);
	i2c_stop();
	t &= ~0x03;
	return t;
}

static void i2c_start(void)
{
	SDA_OUT;
	SCL_OUT;
    SDA_UP;
    I2C_DELAY1;
    SCL_UP;
    I2C_DELAY1;

    SDA_DOWN;
    I2C_DELAY2;
    SCL_DOWN;
}

static void i2c_stop(void)
{
	SDA_OUT;
	SDA_DOWN;
    I2C_DELAY1;
    SCL_UP;
    I2C_DELAY1;
    SDA_UP;
    SCL_IN;
    I2C_DELAY2;
    SDA_IN;
}

static int i2c_wait()
{
	int t;
    SDA_UP;
    SDA_IN;
    I2C_DELAY1;
    t = 100;
    while(t--)
    	if (SDA_VAL)
    		return 1;
    return 0;
}

static unsigned char i2c_write8(unsigned char c)
{
	unsigned char ack;
    char i;

    SDA_OUT;
    SCL_OUT;
    for(i = 8; i; i--)
    {
      if( c & 0x80 )
    	  SDA_UP;
      else
    	  SDA_DOWN;
      I2C_DELAY1;
      SCL_UP;
      I2C_DELAY2;
      c <<= 1;
      SCL_DOWN;
    }

    // ack/nack detection
    SDA_UP;
    SDA_IN;
    I2C_DELAY1;
	SCL_UP;
	I2C_DELAY1;
    if (SDA_VAL)
    	ack = NACK;
    else
    	ack = ACK;

    SCL_DOWN;
	I2C_DELAY1;

	return ack;
}

static unsigned char i2c_read8(unsigned char acknack)
{
	unsigned char dat;
    char i;

    dat = 0;
    SDA_UP;
    SDA_IN;
    SCL_OUT;
    for(i = 8; i; i--)
    {
        dat <<= 1;
    	I2C_DELAY2;
    	SCL_UP;
    	I2C_DELAY1;
        if (SDA_VAL)
          dat |= 0x01;

        SCL_DOWN;
    }

    // ack_nack transmit
    SDA_OUT;
    if( acknack == NACK )
   	  SDA_UP;
    else
   	  SDA_DOWN;
    I2C_DELAY1;
    SCL_UP;
    I2C_DELAY2;
    SCL_DOWN;
    I2C_DELAY1;

    return dat;
}


//-----------------------------------------------------------------
#define     M41T81_SLAVE_ADDR       0xD0  
  
// Regiast address  
#define     M41T81_seconds_fraction 0x00  
#define     M41T81_seconds          0x01  
#define     M41T81_Minutes          0x02  
#define     M41T81_Hours            0x03  
#define     M41T81_Week             0x04  
#define     M41T81_Day              0x05  
#define     M41T81_Month            0x06  
#define     M41T81_Year             0x07  
#define     M41T81_AlarmMonth       0x0a  
#define     M41T81_AlarmDate        0x0b  
#define     M41T81_AlarmHour        0x0c  
#define     M41T81_AlarmMinutes     0x0d  
#define     M41T81_AlarmSeconds     0x0e  
#define     M41T81_ST               0x01  
#define     M41T81_HT               0x0C  
#define     M41T81_AFE              0x0A  
#define     M41T81_ABE              0x0A  
#define     M41T81_AF               0x0F  
#define     M41T81_PRT1             0x0e  
#define     M41T81_PRT2             0x0d  
#define     M41T81_PRT3             0x0c  
#define     M41T81_PRT4             0x0b  
#define     M41T81_PRT5             0x0b  
#define     M41T81_FLAGS               0x0F  
  
// signal  position  
#define     M41T81_positionST       0x80  
#define     M41T81_positionHT       0x40  
#define     M41T81_positionAFE      0x80  
#define     M41T81_positionABE      0x20  
#define     M41T81_positionAF       0x40  
#define     M41T81_positionPRT1     0x80  
#define     M41T81_positionPRT2     0x80  
#define     M41T81_positionPRT3     0x80  
#define     M41T81_positionPRT4     0x80  
#define     M41T81_positionPRT5     0x40  

unsigned char bcdToDec(unsigned char bcd) 
{
	return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

unsigned char decToBCD(unsigned char dec) 
{
	return ((dec / 10) << 4) + (dec % 10);
}
void RTC_Restart()
{
  RTC_Write_Sec1( 0x80 );
  RTC_Write_Sec1( 0x00 );
}
void RTC_Init()
{
  RTC_Write_Min( 0 );
  RTC_Write_Hour( 0 );
}


void RTC_Halt_Clear( )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_HT))
	   	          		i2c_stop();

        	       		     if (i2c_write8(0x00))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}

void RTC_OF_Clear( )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_FLAGS))
	   	          		i2c_stop();

        	       		     if (i2c_write8(0x00))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}
void RTC_Write_Sec1( char sec )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_seconds))
	   	          		i2c_stop();

        	       		     if (i2c_write8(sec))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}

void RTC_Write_Sec( char sec )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_seconds))
	   	          		i2c_stop();

        	       		     if (i2c_write8(decToBCD(sec)))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}

void RTC_Write_Min( char min )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_Minutes))
	   	          		i2c_stop();

        	       		     if (i2c_write8(decToBCD(min)))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}
void RTC_Write_Hour( char hour )
{
  
		       		     i2c_start();
		       		     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	          		i2c_stop();    

		       	 	     if (i2c_write8(M41T81_Hours))
	   	          		i2c_stop();

        	       		     if (i2c_write8(decToBCD(hour)))
	   	          		i2c_stop();

		       		     i2c_stop();
  
}

void RTC_GetAll()
{
  		       		     i2c_start();           	 	
				     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	   	 		i2c_stop(); 

		       		     if (i2c_write8(0))
	      	   	 		i2c_stop();
        
		       		     i2c_start();                     	
                                     if (i2c_write8(M41T81_SLAVE_ADDR+1))  	                                   
	   	   	 		i2c_stop();
                                     
                                     for( int i = 0; i < 0x14; i++ )
                                     {
                                       RTC[i] = i2c_read8(0);
                                     }
  
                       		     i2c_stop();
}

void RTC_GetData()
{
  		       		     i2c_start();           	 	
				     if (i2c_write8(M41T81_SLAVE_ADDR))
	   	   	 		i2c_stop(); 

		       		     if (i2c_write8(M41T81_seconds))
	      	   	 		i2c_stop();
        
		       		     i2c_start();                     	
                                     if (i2c_write8(M41T81_SLAVE_ADDR+1))  	                                   
	   	   	 		i2c_stop();
        
		       		     Sec_Reg = (i2c_read8(0));
		       		     Min_Reg = (i2c_read8(0));
		       		     Hr_Reg =  (i2c_read8(0));
		       		     DOW_Reg = i2c_read8(0);
                       		     DOM_Reg = i2c_read8(0);
		       		     Mon_Reg = i2c_read8(0);
		       		     Yr_Reg =  i2c_read8(0);
		       		     Cont_Reg = i2c_read8(1);
                       		     i2c_stop();

}