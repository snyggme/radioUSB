#include "includes.h"

//-------Pictures---------------
#include "logo1_black.h"
#include "logo1_green.h"
#include "logo2_green.h"
#include "logo2_blue.h"


//------------------------------

const char SCR1_STR1[] = { "ÊÎÍÒÐÀÊÒÍÎÅ" };
const char SCR1_STR2[] = { "ÏÐÎÈÇÂÎÄÑÒÂÎ" };
const char SCR1_STR3[] = { "ÝËÅÊÒÐÎÍÈÊÈ" };

const char SCR2_STR1[] = { "ÌÎÍÒÀÆ" };
const char SCR2_STR2[] = { "ÏÅ×ÀÒÍÛÕ" };
const char SCR2_STR3[] = { "ÏËÀÒ" };

const char SCR3_STR1[] = { "4,5 òûñ. ì" };
const char SCR3_STR11[] = { "2" };
const char SCR3_STR2[] = { "ÇÀÂÎÄÑÊÈÕ" };
const char SCR3_STR3[] = { "È ÎÔÈÑÍÛÕ" };
const char SCR3_STR4[] = { "ÏËÎÙÀÄÅÉ" };

const char LOGO2_STR1[] = { "A-KOHTPAKT" };

extern volatile uint32_t AnimPhase;
extern volatile uint32_t Screen1_Start;
extern volatile uint32_t Screen2_Start;
extern volatile uint32_t Screen3_Start;
extern volatile uint32_t Logo1_Start;
extern volatile uint32_t Sensors_Start;

extern volatile unsigned char Sec_Reg;
extern volatile unsigned char Min_Reg;
extern volatile unsigned char Hr_Reg;
extern volatile unsigned char DOW_Reg;
extern volatile unsigned char DOM_Reg;
extern volatile unsigned char Mon_Reg;
extern volatile unsigned char Yr_Reg;
extern volatile unsigned char Cont_Reg;

extern volatile short tempr_full;
extern volatile short RH_full;

extern volatile short RTC[20];

int Screen1_Phase = 0;
int Screen2_Phase = 0;
int Screen3_Phase = 0;
int Sensors_Phase = 0;
int Logo1_Phase = 0;

#define LOGO_2

char ShowScreen1()
{
	char end_of_show = 0;

	if (Screen1_Start == 0)
		return end_of_show;

	switch (Screen1_Phase)
	{
		case 0:
		{
			OLED_FillScreen(OLED_Color565(255, 255, 255));
		}
		break;
		case 1:
		{
			PrintText6x8R((char *)SCR1_STR1, 11, 15, 10, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			PrintText6x8R((char *)SCR1_STR2, 12, 12, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			PrintText6x8R((char *)SCR1_STR3, 11, 15, 50, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		}
		break;
		case 2:
		{
			OLED_FillRect(0, 10, 95, 20, OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR1, 11, 15, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			PrintText6x8R((char *)SCR1_STR2, 12, 12, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			OLED_FillRect(0, 50, 95, 60, OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR3, 11, 15, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		}
		break;
		case 3:
		{
			OLED_FillRect(0, 15, 95, 25, OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR1, 11, 15, 20, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			PrintText6x8R((char *)SCR1_STR2, 12, 12, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

			OLED_FillRect(0, 45, 95, 55, OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR3, 11, 15, 40, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		}
		break;
		case 10:
		{
			PrintText6x8R((char *)SCR1_STR1, 11, 15, 20, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR2, 12, 12, 30, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR3, 11, 15, 40, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
		}
		break;
		case 20:
		{
			PrintText6x8R((char *)SCR1_STR1, 11, 15, 20, 0, OLED_Color565(0, 0, 255), OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR2, 12, 12, 30, 0, OLED_Color565(0, 0, 255), OLED_Color565(255, 255, 255));
			PrintText6x8R((char *)SCR1_STR3, 11, 15, 40, 0, OLED_Color565(0, 0, 255), OLED_Color565(255, 255, 255));
		}
		break;
		case 30:
		{
			Screen1_Start = 0;
			end_of_show = 1;
		}
			break;
	}

	if (Screen1_Start)
	{
		Screen1_Phase++;
		if (Screen1_Phase > 1000)
		{
			Screen1_Start = 0;
			Screen1_Phase = 0;
		}

	}
	else
		Screen1_Phase = 0;

	return end_of_show;
}

char ShowScreen2()
{
	char end_of_show = 0;

	if (Screen2_Start == 0)
		return end_of_show;

	switch (Screen2_Phase)
	{
	case 0:
	{
		OLED_FillScreen(OLED_Color565(255, 255, 255));
	}
		break;
	case 1:
	{
		PrintText6x8R((char *)SCR2_STR1, 6, 30, 10, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		PrintText6x8R((char *)SCR2_STR2, 8, 24, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		PrintText6x8R((char *)SCR2_STR3, 4, 36, 50, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 2:
	{
		OLED_FillRect(0, 10, 95, 20, OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR1, 6, 30, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		PrintText6x8R((char *)SCR2_STR2, 8, 24, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		OLED_FillRect(0, 50, 95, 60, OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR3, 4, 36, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 3:
	{
		OLED_FillRect(0, 15, 95, 25, OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR1, 6, 30, 20, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		PrintText6x8R((char *)SCR2_STR2, 8, 24, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

		OLED_FillRect(0, 45, 95, 55, OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR3, 4, 36, 40, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 10:
	{
		PrintText6x8R((char *)SCR2_STR1, 6, 30, 20, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR2, 8, 24, 30, 0, OLED_Color565(0, 255, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR3, 4, 36, 40, 0, OLED_Color565(0, 255, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 20:
	{
		PrintText6x8R((char *)SCR2_STR1, 6, 30, 20, 0, OLED_Color565(0, 0, 255), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR2, 8, 24, 30, 0, OLED_Color565(0, 200, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR2_STR3, 4, 36, 40, 0, OLED_Color565(0, 200, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 30:
	{
		Screen2_Start = 0;
		end_of_show = 1;
	}
		break;
	}

	if (Screen2_Start)
	{
		Screen2_Phase++;
		if (Screen2_Phase > 1000)
		{
			Screen2_Start = 0;
			Screen2_Phase = 0;
		}

	}
	else
		Screen2_Phase = 0;

	return end_of_show;
}

char ShowScreen3()
{
	char end_of_show = 0;

	if (Screen3_Start == 0)
		return end_of_show;

	switch (Screen3_Phase)
	{
	case 0:
	{
		OLED_FillScreen(OLED_Color565(255, 255, 255));
	}
		break;
	case 1:
	{
		PrintText6x8R((char *)SCR3_STR1, 10, 15, 15, 0, OLED_Color565(200, 200, 200), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR11, 1, 75, 13, 0, OLED_Color565(200, 200, 200), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR2, 9, 21, 25, 0, OLED_Color565(200, 200, 200), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR3, 9, 21, 35, 0, OLED_Color565(200, 200, 200), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR4, 8, 24, 45, 0, OLED_Color565(200, 200, 200), OLED_Color565(255, 255, 255));
	}
		break;
	case 2:
	{
		PrintText6x8R((char *)SCR3_STR1, 10, 15, 15, 0, OLED_Color565(100, 100, 100), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR11, 1, 75, 13, 0, OLED_Color565(100, 100, 100), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR2, 9, 21, 25, 0, OLED_Color565(100, 100, 100), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR3, 9, 21, 35, 0, OLED_Color565(100, 100, 100), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR4, 8, 24, 45, 0, OLED_Color565(100, 100, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 3:
	{
		PrintText6x8R((char *)SCR3_STR1, 10, 15, 15, 0, OLED_Color565(50, 50, 50), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR11, 1, 75, 13, 0, OLED_Color565(50, 50, 50), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR2, 9, 21, 25, 0, OLED_Color565(50, 50, 50), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR3, 9, 21, 35, 0, OLED_Color565(50, 50, 50), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR4, 8, 24, 45, 0, OLED_Color565(50, 50, 50), OLED_Color565(255, 255, 255));
	}
		break;
	case 10:
	{
		PrintText6x8R((char *)SCR3_STR1, 10, 15, 15, 0, OLED_Color565(180, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR11, 1, 75, 13, 0, OLED_Color565(180, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR2, 9, 21, 25, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR3, 9, 21, 35, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR4, 8, 24, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 20:
	{
		PrintText6x8R((char *)SCR3_STR1, 10, 15, 15, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR11, 1, 75, 13, 0, OLED_Color565(255, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR2, 9, 21, 25, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR3, 9, 21, 35, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
		PrintText6x8R((char *)SCR3_STR4, 8, 24, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 30:
	{
		Screen3_Start = 0;
		end_of_show = 1;
	}
		break;
	}

	if (Screen3_Start)
	{
		Screen3_Phase++;
		if (Screen3_Phase > 1000)
		{
			Screen3_Start = 0;
			Screen3_Phase = 0;
		}

	}
	else
		Screen3_Phase = 0;

	return end_of_show;
}

char ShowLogo()
{
#ifdef LOGO_1
  return ShowLogo1();
#endif

#ifdef LOGO_2
  return ShowLogo2();
#endif
}

char ShowLogo1()
{
	char end_of_show = 0;

	if (Logo1_Start == 0)
		return end_of_show;

	switch (Logo1_Phase)
	{
	case 0:
	{
		OLED_FillScreen(OLED_Color565(255, 255, 255));
	}
		break;
	case 1:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(250, 255, 250));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(200, 200, 200));
	}
		break;
	case 2:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(200, 255, 200));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(160, 160, 160));
	}
		break;
	case 3:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(150, 255, 150));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(120, 120, 120));
	}
		break;
	case 4:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(100, 255, 100));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(100, 100, 100));
	}
		break;
	case 5:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(50, 240, 50));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(50, 50, 50));
	}
		break;
	case 6:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(0, 230, 0));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(0, 0, 0));
	}
		break;
	case 30:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(50, 230, 50));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(50, 50, 50));
	}
		break;
	case 31:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(120, 230, 120));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(120, 120, 120));
	}
		break;
	case 32:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(200, 230, 200));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(200, 200, 200));
	}
		break;
	case 33:
	{
		DrawPicture(logo1_green, 18, 2, OLED_Color565(250, 250, 250));
		DrawPicture(logo1_black, 18, 2, OLED_Color565(250, 250, 250));
	}
		break;
	case 40:
	{
		Logo1_Start = 0;
		end_of_show = 1;
	}
		break;
	}

	if (Logo1_Start)
	{
		Logo1_Phase++;
		if (Logo1_Phase > 1000)
		{
			Logo1_Start = 0;
			Logo1_Phase = 0;
		}

	}
	else
		Logo1_Phase = 0;

	return end_of_show;
}


char ShowLogo2()
{
	char end_of_show = 0;

	if (Logo1_Start == 0)
		return end_of_show;

	switch (Logo1_Phase)
	{
	case 0:
	{
		OLED_FillScreen(OLED_Color565(255, 255, 255));
	}
		break;
	case 1:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(200, 255, 200));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(250, 250, 100));
//		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 2:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(150, 255, 150));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(200, 200, 100));
//		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 3:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(100, 255, 100));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(150, 150, 100));
//		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 4:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(50, 255, 50));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(100, 100, 100));
//		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 5:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(10, 255, 10));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(50, 50, 100));
//		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 6:
	{
		DrawPicture(logo2_green, 13, 2, OLED_Color565(0, 255, 0));
		DrawPicture(logo2_blue, 13, 2, OLED_Color565(0, 0, 100));
		PrintText6x8R((char *)LOGO2_STR1, 10, 18, 56, 0, OLED_Color565(0, 0, 100), OLED_Color565(255, 255, 255));
	}
		break;
	case 30:
	{
	}
		break;
	case 31:
	{
	}
		break;
	case 32:
	{
	}
		break;
	case 33:
	{
	}
		break;
	case 40:
	{
		Logo1_Start = 0;
		end_of_show = 1;
	}
		break;
	}

	if (Logo1_Start)
	{
		Logo1_Phase++;
		if (Logo1_Phase > 1000)
		{
			Logo1_Start = 0;
			Logo1_Phase = 0;
		}

	}
	else
		Logo1_Phase = 0;

	return end_of_show;
}

#define SENS_TXT_OFFSET 10

void ShowTime()
{
    char len;
    char info[20];
              
    OLED_FillScreen(OLED_Color565(255, 255, 255));
    len = sprintf( info, "%hhX %hhX %hhX %hhX  %hhX", RTC[0], RTC[1], RTC[2], RTC[3], RTC[4] );
    PrintText6x8R(info, len, 1, 1, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

    len = sprintf( info, "%hhX %hhX %hhX %hhX  %hhX", RTC[5], RTC[6], RTC[7], RTC[8], RTC[9] );
    PrintText6x8R(info, len, 1, 12, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

    len = sprintf( info, "%hhX %hhX %hhX %hhX  %hhX", RTC[0x0A], RTC[0x0B], RTC[0x0C], RTC[0x0D]  );
    PrintText6x8R(info, len, 1, 24, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

    len = sprintf( info, "%hhX %hhX %hhX %hhX  %hhX", RTC[0x0E], RTC[0x0F], RTC[0x10], RTC[0x11], RTC[0x13] );
    PrintText6x8R(info, len, 1, 36, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
}

char ShowSensors()
{
    char len;
    char info[20];
  
	char end_of_show = 0;

	if (Sensors_Start == 0)
		return end_of_show;

	switch (Sensors_Phase)
	{
	case 0:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
          
	}
		break;
	case 10:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 20:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 30:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 40:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 50:
	{
              OLED_FillScreen(OLED_Color565(255, 255, 255));
              len = sprintf( info, "RH = %d%%", RH_full );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 15, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "T  = %dC", tempr_full/10 );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 30, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));

              len = sprintf( info, "%02d:%02d.%02d", Hr_Reg, Min_Reg, Sec_Reg );
              PrintText8x12(info, len, SENS_TXT_OFFSET, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
              PrintText8x12(info, len, SENS_TXT_OFFSET+1, 45, 0, OLED_Color565(0, 0, 0), OLED_Color565(255, 255, 255));
	}
		break;
	case 55:
	{
		Sensors_Start = 0;
		end_of_show = 1;
	}
		break;
	}

	if (Sensors_Start)
	{
		Sensors_Phase++;
		if (Sensors_Phase > 1000)
		{
			Sensors_Start = 0;
			Sensors_Phase = 0;
		}

	}
	else
		Sensors_Phase = 0;

	return end_of_show;
}

