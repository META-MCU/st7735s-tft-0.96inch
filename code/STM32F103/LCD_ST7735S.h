#ifndef _LCD_ST7735S_H_
#define _LCD_ST7735S_H_

#define LCD_PORT GPIOE
#define LCD_PIN_CS GPIO_Pin_11
#define LCD_PIN_RES GPIO_Pin_8
#define LCD_PIN_A0 GPIO_Pin_10
#define LCD_PIN_SDA GPIO_Pin_12
#define LCD_PIN_SCL GPIO_Pin_9

#define SET_LCD_CS 	GPIO_SetBits(LCD_PORT, LCD_PIN_CS)
#define SET_LCD_RES GPIO_SetBits(LCD_PORT, LCD_PIN_RES)
#define SET_LCD_A0 	GPIO_SetBits(LCD_PORT, LCD_PIN_A0)
#define SET_LCD_SDA GPIO_SetBits(LCD_PORT, LCD_PIN_SDA)
#define SET_LCD_SCL GPIO_SetBits(LCD_PORT, LCD_PIN_SCL)

#define	CLR_LCD_CS  GPIO_ResetBits(LCD_PORT, LCD_PIN_CS)
#define	CLR_LCD_RES  GPIO_ResetBits(LCD_PORT, LCD_PIN_RES)
#define	CLR_LCD_A0  GPIO_ResetBits(LCD_PORT, LCD_PIN_A0)
#define	CLR_LCD_SDA  GPIO_ResetBits(LCD_PORT, LCD_PIN_SDA)
#define	CLR_LCD_SCL  GPIO_ResetBits(LCD_PORT, LCD_PIN_SCL)

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
#define BROWN	0XBC40 //��ɫ
#define BRRED	0XFC07 //�غ�ɫ
#define GRAY	0X8430 //��ɫ
#define DARKBLUE	0X01CF	//����ɫ
#define LIGHTBLUE	0X7D7C	//ǳ��ɫ  
#define GRAYBLUE	0X5458 //����ɫ

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

void LCD_DisplayOn(void); //����ʾ
void LCD_DisplayOff(void); //����ʾ
void LCD_Draw_Circle(unsigned short x0, unsigned short y0, unsigned char r, unsigned short color); //��Բ
void LCD_DrawFullCircle(unsigned short Xpos, unsigned short Ypos, unsigned short Radius, unsigned short Color);
void LCD_Fill(unsigned short sx, unsigned short sy, unsigned short ex, unsigned short ey, unsigned short color); //�������
void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color); //����
void LCD_DrawRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color); //������
void LCD_ShowChar(unsigned short x, unsigned short y, unsigned char num, unsigned char size, unsigned char mode, unsigned short pen_color, unsigned short back_color); //дASCII�ַ�
void LCD_ShowString(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char size, unsigned char *p, unsigned short pen_color, unsigned short back_color); //дASCII�ַ���

void GUI_sprintf_hz1616(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color);
void GUI_sprintf_hz16x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short dcolor, unsigned short bgcolor);

void GUI_sprintf_hz3232(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color);
void GUI_sprintf_hz32x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short pen_color, unsigned short back_color);

#endif
