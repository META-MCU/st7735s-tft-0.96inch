#ifndef _LCD_ST7735S_H_
#define _LCD_ST7735S_H_

#define LCD_PORT GpioPortB
#define LCD_PIN_SCK GpioPin11
#define LCD_PIN_SDA GpioPin12
#define LCD_PIN_RES GpioPin13
#define LCD_PIN_A0 GpioPin14
#define LCD_PIN_CS GpioPin15

#define SET_LCD_CS 	Gpio_SetIO(LCD_PORT, LCD_PIN_CS)
#define SET_LCD_RES Gpio_SetIO(LCD_PORT, LCD_PIN_RES)
#define SET_LCD_A0 	Gpio_SetIO(LCD_PORT, LCD_PIN_A0)
#define SET_LCD_SDA Gpio_SetIO(LCD_PORT, LCD_PIN_SDA)
#define SET_LCD_SCK Gpio_SetIO(LCD_PORT, LCD_PIN_SCK)

#define	CLR_LCD_CS  Gpio_ClrIO(LCD_PORT, LCD_PIN_CS)
#define	CLR_LCD_RES  Gpio_ClrIO(LCD_PORT, LCD_PIN_RES)
#define	CLR_LCD_A0  Gpio_ClrIO(LCD_PORT, LCD_PIN_A0)
#define	CLR_LCD_SDA  Gpio_ClrIO(LCD_PORT, LCD_PIN_SDA)
#define	CLR_LCD_SCK  Gpio_ClrIO(LCD_PORT, LCD_PIN_SCK)

#define WHITE	0xFFFF
#define BLACK	0x0000	  
#define BLUE	0x001F  
#define BRED	0XF81F
#define GRED	0XFFE0
#define GBLUE	0X07FF
#define RED		0xF800
#define MAGENTA	0xF81F
#define GREEN	0x07E0
#define CYAN	0x7FFF
#define YELLOW	0xFFE0
#define BROWN	0XBC40 //×ØÉ«
#define BRRED	0XFC07 //×ØºìÉ«
#define GRAY	0X8430 //»ÒÉ«
#define DARKBLUE	0X01CF	//ÉîÀ¶É«
#define LIGHTBLUE	0X7D7C	//Ç³À¶É«  
#define GRAYBLUE	0X5458 //»ÒÀ¶É«

void lcdGpioInit(void);
void lcdInit(void);
void lcdSelectRegister(unsigned char data);
void lcdWriteDataU8(unsigned char data);
void lcdWriteDataU16(unsigned short data);

void lcdSetAddress(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
void lcdClear(unsigned short color);

void LCD_DrawPoint(unsigned short x, unsigned short y, unsigned short color);

void Lcd_Init(void);
void LCD_Clear(unsigned short color);

void LCD_DisplayOn(void); //¿ªÏÔÊ¾
void LCD_DisplayOff(void); //¹ØÏÔÊ¾
void LCD_Draw_Circle(unsigned short x0, unsigned short y0, unsigned char r, unsigned short color); //»­Ô²
void LCD_DrawFullCircle(unsigned short Xpos, unsigned short Ypos, unsigned short Radius, unsigned short Color);
void LCD_Fill(unsigned short sx, unsigned short sy, unsigned short ex, unsigned short ey, unsigned short color); //Ìî³äÇøÓò
void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color); //»­Ïß
void LCD_DrawRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color); //»­¾ØÐÎ
void LCD_ShowChar(unsigned short x, unsigned short y, unsigned char num, unsigned char size, unsigned char mode, unsigned short pen_color, unsigned short back_color); //Ð´ASCII×Ö·û
void LCD_ShowString(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char size, unsigned char *p, unsigned short pen_color, unsigned short back_color); //Ð´ASCII×Ö·û´®

void GUI_sprintf_hz1616(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color);
void GUI_sprintf_hz16x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short dcolor, unsigned short bgcolor);

void GUI_sprintf_hz3232(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color);
void GUI_sprintf_hz32x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short pen_color, unsigned short back_color);

#endif
