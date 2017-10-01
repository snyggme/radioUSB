void OLED_writeCommand(char c); 
void OLED_writeData(char c);
void OLED_goHome(void); 
void OLED_goTo(int x, int y); 
unsigned short OLED_Color565(unsigned char r, unsigned char g, unsigned char b); 
void OLED_drawLine(short x0, short y0, short x1, short y1, unsigned short color);
void OLED_drawPixel(short x, short y, unsigned short color);
void OLED_pushColor(unsigned short color);
void OLED_Init();
void OLED_Reset();
void OLED_SPI_Init();
void OLED_FillScreen(unsigned short color);
void OLED_FillRect(short x0, short y0, short x1, short y1, unsigned short color);

void PrintText8x8( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color );
void PrintText6x8R( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color );
void PrintText8x12( char txt[], char text_len, char text_x, char text_y, char text_erase, unsigned short color, unsigned short back_color );

void DrawPicture( const unsigned char pict[], int x_origin, int y_origin, unsigned short color );
