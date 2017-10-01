#include "includes.h"

#include "fonts.h"
#include <math.h>

#define SSD1331_COLORORDER_RGB
// #define SSD1331_COLORORDER_BGR

#if defined SSD1331_COLORORDER_RGB && defined SSD1331_COLORORDER_BGR
  #error "RGB and BGR can not both be defined for SSD1331_COLORODER."
#endif

// Timing Delays
#define SSD1331_DELAYS_HWFILL		(3)
#define SSD1331_DELAYS_HWLINE       (1)

#define OLED_WIDTH 		96
#define OLED_HEIGHT 		64

#define OLED_ROTATE             


// SSD1331 Commands
#define SSD1331_CMD_DRAWLINE 		0x21
#define SSD1331_CMD_DRAWRECT 		0x22
#define SSD1331_CMD_FILL 			0x26
#define SSD1331_CMD_SETCOLUMN 		0x15
#define SSD1331_CMD_SETROW    		0x75
#define SSD1331_CMD_CONTRASTA 		0x81
#define SSD1331_CMD_CONTRASTB 		0x82
#define SSD1331_CMD_CONTRASTC		0x83
#define SSD1331_CMD_MASTERCURRENT 	0x87
#define SSD1331_CMD_SETREMAP 		0xA0
#define SSD1331_CMD_STARTLINE 		0xA1
#define SSD1331_CMD_DISPLAYOFFSET 	0xA2
#define SSD1331_CMD_NORMALDISPLAY 	0xA4
#define SSD1331_CMD_DISPLAYALLON  	0xA5
#define SSD1331_CMD_DISPLAYALLOFF 	0xA6
#define SSD1331_CMD_INVERTDISPLAY 	0xA7
#define SSD1331_CMD_SETMULTIPLEX  	0xA8
#define SSD1331_CMD_SETMASTER 		0xAD
#define SSD1331_CMD_DISPLAYOFF 		0xAE
#define SSD1331_CMD_DISPLAYON     	0xAF
#define SSD1331_CMD_POWERMODE 		0xB0
#define SSD1331_CMD_PRECHARGE 		0xB1
#define SSD1331_CMD_CLOCKDIV 		0xB3
#define SSD1331_CMD_PRECHARGEA 		0x8A
#define SSD1331_CMD_PRECHARGEB 		0x8B
#define SSD1331_CMD_PRECHARGEC 		0x8C
#define SSD1331_CMD_PRECHARGELEVEL 	0xBB
#define SSD1331_CMD_VCOMH 			0xBE

/********************************** low level pin interface */
inline void spiwrite(char c) 
{
  
//  while( SSP1SR_bit.BSY );
  SSP1DR = c;
  while( SSP1SR_bit.BSY );
  
}

void OLED_SPI_Init()
{
  // Configure port and pins
  // * - MISO/MOSI/SCLK GPIO controlled by peripheral
  // * - CS_n GPIO controlled manually, set to 1
  IOCON_PIO0_22 = 0x03; // MISO 0x83
  IOCON_PIO0_21 = 0x02; // MOSI 0x02
  IOCON_PIO1_15 = 0x03; // SCK 0x03

  SYSAHBCLKCTRL_bit.SSP1 = 1; // Enable clock for SSP
  SSP1CLKDIV = 0x02; // Clock devider
  PRESETCTRL_bit.SSP1_RST_N = 1; // Reset SSP
    
  SSP1CR0_bit.DSS = 0x07; // 8 bit transfer
  SSP1CR0_bit.FRF = 0x00; // SPI format
  SSP1CR0_bit.CPOL = 0x01; // Polarity between frames
  SSP1CR0_bit.CPHA = 0x01; // Clock out phase
  SSP1CR0_bit.SCR = 0x01; // Serial clock rate
    
  SSP1CR1_bit.LBM = 0x00; // Loopback
  SSP1CR1_bit.SSE = 0x01;
  SSP1CR1_bit.MS = 0x01; // Master select
  SSP1CR1_bit.SOD = 0x00;
    
  SSP1CPSR = 0x0F; // Prescaler (2,4,6...) - 72/18 = 4 ÌÃö
}

void OLED_writeCommand(char c) 
{
    OLED_DC  = 0;
    OLED_CS  = 0;
    
    spiwrite( c );
    
    OLED_CS  = 1;
}


void OLED_writeData(char c) 
{
    OLED_DC  = 1;
    OLED_CS  = 0;
    
    spiwrite( c );
    
    OLED_CS  = 1;
} 

/***********************************/

void OLED_goHome(void) 
{
  OLED_goTo(0,0);
}

void OLED_goTo(int x, int y) 
{
  if ((x >= OLED_WIDTH) || (y >= OLED_HEIGHT)) return;
#ifdef OLED_ROTATE
  x = OLED_WIDTH - x;
  y = OLED_HEIGHT - y;
#endif  
  // set x and y coordinate
  OLED_writeCommand(SSD1331_CMD_SETCOLUMN);
  OLED_writeCommand(x);
  OLED_writeCommand(OLED_WIDTH-1);

  OLED_writeCommand(SSD1331_CMD_SETROW);
  OLED_writeCommand(y);
  OLED_writeCommand(OLED_WIDTH-1);
}

void OLED_goTo_Origin(int x, int y) 
{
  if ((x >= OLED_WIDTH) || (y >= OLED_HEIGHT)) return;
  // set x and y coordinate
  OLED_writeCommand(SSD1331_CMD_SETCOLUMN);
  OLED_writeCommand(x);
  OLED_writeCommand(OLED_WIDTH-1);

  OLED_writeCommand(SSD1331_CMD_SETROW);
  OLED_writeCommand(y);
  OLED_writeCommand(OLED_WIDTH-1);
}

unsigned short OLED_Color565(unsigned char r, unsigned char g, unsigned char b) 
{
  unsigned short c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;

  return c;
}

void OLED_delay( int i )
{
    for ( ; i > 1; i--)
      OLED_RES = 0;
}

void OLED_FillScreen(unsigned short color)
{
//  OLED_goHome();
   int i, j;

   for( j = 0; j < 64; j++ )
   {
      OLED_goTo_Origin(0,j);
      
      for( i = 0; i < 96; i++ )
      {
        OLED_pushColor( color );
      }
   }
}

void OLED_FillRect(short x0, short y0, short x1, short y1, unsigned short color) 
{
   int i, j;

   for( j = y0; j < y1; j++ )
   {
//      OLED_goTo(x0,j);
      OLED_goTo_Origin(0, OLED_HEIGHT - j);
      
      for( i = 0; i < OLED_WIDTH; i++ )
      {
        OLED_pushColor( color );
      }
   }
}

void OLED_drawLine(short x0, short y0, short x1, short y1, unsigned short color) 
{	
  // Boundary check
  if ((y0 >= OLED_HEIGHT) && (y1 >= OLED_HEIGHT))
	return;
  if ((x0 >= OLED_WIDTH) && (x1 >= OLED_WIDTH))
	return;	
  if (x0 >= OLED_WIDTH)
    x0 = OLED_WIDTH - 1;
  if (y0 >= OLED_HEIGHT)
    y0 = OLED_HEIGHT - 1;
  if (x1 >= OLED_WIDTH)
    x1 = OLED_WIDTH - 1;
  if (y1 >= OLED_HEIGHT)
    y1 = OLED_HEIGHT - 1;
  
  OLED_writeCommand(SSD1331_CMD_DRAWLINE);
  OLED_writeCommand(x0);
  OLED_writeCommand(y0);
  OLED_writeCommand(x1);
  OLED_writeCommand(y1);
  OLED_delay(SSD1331_DELAYS_HWLINE);  
  
  OLED_writeCommand((unsigned char)((color >> 11) << 1));
  OLED_writeCommand((unsigned char)((color >> 5) & 0x3F));
  OLED_writeCommand((unsigned char)((color << 1) & 0x3F));
  
  OLED_delay(SSD1331_DELAYS_HWLINE);  
}

void OLED_drawPixel(short x, short y, unsigned short color)
{
    if ((x < 0) || (x >= OLED_WIDTH) || (y < 0) || (y >= OLED_HEIGHT)) return;

    OLED_goTo(x, y);
  
  // setup for data
    OLED_DC  = 1;
    OLED_CS  = 0;
  
    spiwrite(color >> 8);    
    spiwrite(color);
  
    OLED_CS  = 1;
}

void OLED_pushColor(unsigned short color) {
  // setup for data
    OLED_DC  = 1;
    OLED_CS  = 0;
  
    spiwrite(color >> 8);    
    spiwrite(color);
  
    OLED_CS  = 1;
}

void OLED_Init()
{
  OLED_CS_DIR |= OLED_CS_MASK;
  OLED_CLK_DIR |= OLED_CLK_MASK;
  OLED_DIN_DIR |= OLED_DIN_MASK;
  OLED_DC_DIR |= OLED_DC_MASK;
  OLED_RES_DIR |= OLED_RES_MASK;
  
  OLED_CS  = 1;
  OLED_CLK = 1;
  OLED_DIN = 1;
  OLED_DC  = 1;
  OLED_RES = 0;
  
    int i;
    for ( i = 1000; i > 1; i--)
      OLED_RES = 0;

    OLED_RES = 1;
    for ( i = 1000; i > 1; i--)
      OLED_RES = 1;

    // set pin directions
    // Initialization Sequence
    OLED_writeCommand(SSD1331_CMD_DISPLAYOFF);  // 0xAE
    OLED_writeCommand(SSD1331_CMD_SETREMAP); 	// 0xA0
#if defined SSD1331_COLORORDER_RGB
    OLED_writeCommand(0x72);			// RGB Color
#else
    OLED_writeCommand(0x76);			// BGR Color
#endif
    OLED_writeCommand(SSD1331_CMD_STARTLINE); 	// 0xA1
    OLED_writeCommand(0x0);
    OLED_writeCommand(SSD1331_CMD_DISPLAYOFFSET);// 0xA2
    OLED_writeCommand(0x0);
    OLED_writeCommand(SSD1331_CMD_NORMALDISPLAY);// 0xA4
    OLED_writeCommand(SSD1331_CMD_SETMULTIPLEX); // 0xA8
    OLED_writeCommand(0x3F);  			// 0x3F 1/64 duty
    OLED_writeCommand(SSD1331_CMD_SETMASTER);  	// 0xAD
    OLED_writeCommand(0x8E);
    OLED_writeCommand(SSD1331_CMD_POWERMODE);  	// 0xB0
    OLED_writeCommand(0x0B);
    OLED_writeCommand(SSD1331_CMD_PRECHARGE);  	// 0xB1
    OLED_writeCommand(0x31);
    OLED_writeCommand(SSD1331_CMD_CLOCKDIV);  	// 0xB3
    OLED_writeCommand(0xF0);  // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    OLED_writeCommand(SSD1331_CMD_PRECHARGEA);  // 0x8A
    OLED_writeCommand(0x64);
    OLED_writeCommand(SSD1331_CMD_PRECHARGEB);  // 0x8B
    OLED_writeCommand(0x78);
    OLED_writeCommand(SSD1331_CMD_PRECHARGEA);  // 0x8C
    OLED_writeCommand(0x64);
    OLED_writeCommand(SSD1331_CMD_PRECHARGELEVEL);// 0xBB
    OLED_writeCommand(0x3A);
    OLED_writeCommand(SSD1331_CMD_VCOMH);  	// 0xBE
    OLED_writeCommand(0x3E);
    OLED_writeCommand(SSD1331_CMD_MASTERCURRENT);// 0x87
    OLED_writeCommand(0x06);
    OLED_writeCommand(SSD1331_CMD_CONTRASTA);  	// 0x81
    OLED_writeCommand(0x91);
    OLED_writeCommand(SSD1331_CMD_CONTRASTB);  	// 0x82
    OLED_writeCommand(0x50);
    OLED_writeCommand(SSD1331_CMD_CONTRASTC);  	// 0x83
    OLED_writeCommand(0x7D);
    OLED_writeCommand(SSD1331_CMD_DISPLAYON);	//--turn on oled panel    
}

void OLED_Reset()
{
  OLED_RES = 0;
  
  int i;
  for ( i = 1000; i > 1; i--)
    OLED_RES = 0;

  OLED_RES = 1;
}

void PrintText8x8( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color )
{
	int t_x, char_pos;
	unsigned char mask, i, j, k;

	t_x = text_x - 8;													// Temporary text position

	for( i = 0; i < text_len; i++ )
	{
		t_x += 8;														// Set to the next character

		if( t_x > OLED_WIDTH - 8 )										// Go to the next string
		{
			t_x = 2;
			text_y += 9;
		}

		if( text_erase )
			OLED_FillRect( t_x, text_y, t_x + 8,text_y + 8, back_color );	// Erase background if necessary

		char_pos = txt[i]*8;

		for( j = 0; j < 8; j++ )
		{
			mask = 0x01;
			
			for( k = 0; k < 8; k++ )
			{
				if( font6x8[ char_pos + j ] & mask )			// Check pixel by mask
					OLED_drawPixel( t_x + k, text_y + j, color);	// Set pixel by selected color

				mask <<= 1;												// Prepare for next pixel
			}
		}
	}

	text_x = t_x + 8;													// Update current text position
}

void PrintText6x8R( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color )
{
	int t_x, char_pos;
	unsigned char mask, i, j, k;

	t_x = text_x - 6;													// Temporary text position

	for( i = 0; i < text_len; i++ )
	{
		t_x += 6;														// Set to the next character

		if( t_x > OLED_WIDTH - 5 )										// Go to the next string
		{
			t_x = 2;
			text_y += 9;
		}

		if( text_erase )
			OLED_FillRect( t_x, text_y, t_x + 6, text_y + 8, back_color );	// Erase background if necessary

		char_pos = txt[i]*6;

		for( j = 0; j < 6; j++ )
		{
			mask = 0x01;
			
			for( k = 0; k < 8; k++ )
			{
				if( Font_6x8_Data[ char_pos + j ] & mask )			// Check pixel by mask
					OLED_drawPixel( t_x + j, text_y + k, color);	// Set pixel by selected color

				mask <<= 1;												// Prepare for next pixel
			}
		}
	}

	text_x = t_x + 6;													// Update current text position
}

void PrintText8x12( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color )
{
	int t_x, char_pos;
	unsigned char mask, i, j, k;

	t_x = text_x - 9;													// Temporary text position

	for( i = 0; i < text_len; i++ )
	{
		t_x += 9;														// Set to the next character

		if( t_x > OLED_WIDTH - 8 )										// Go to the next string
		{
			t_x = 2;
			text_y += 13;
		}

		if( text_erase )
			OLED_FillRect( t_x, text_y, t_x + 8,text_y + 12, back_color );	// Erase background if necessary

		char_pos = txt[i]*12;

		for( j = 0; j < 12; j++ )
		{
			mask = 0x01;
			
			for( k = 0; k < 8; k++ )
			{
				if( font8x12[ char_pos + j ] & mask )					// Check pixel by mask
					OLED_drawPixel( t_x + k, text_y + j, color);		// Set pixel by selected color

				mask <<= 1;												// Prepare for next pixel
			}
		}
	}

	text_x = t_x + 9;													// Update current text position
}
void DrawPicture( const unsigned char pict[], int x_origin, int y_origin, unsigned short color )
{
	int p_x, p_y, b_x;
	unsigned char mask, i, j, k;

	p_x = pict[1] + pict[2]*256;
	p_y = pict[3] + pict[4]*256;
	b_x = (int)ceil( p_x / 8.0); // @@@

	for( i = 0; i < p_y; i++ )
	{
		for( j = 0; j < b_x; j++ )
		{
			mask = 0x80;
			for( k = 0; k < 8; k++ )
			{
				if( (j*8 + k) >= p_x )
					break;

				if( pict[5 + j + i*b_x] & mask )
					OLED_drawPixel( x_origin + j*8 + k, y_origin + i, color);		// Set pixel by selected color

				mask >>= 1;
			}
		}
	}
}