#include "gd32f10x.h"
#include "LCD_ST7735S.h"
#include "font.h"
#include "hz_16x16.h"
#include "hz_32x32.h"
#include "systick.h"

void lcd_gpio_init(void)
{
    rcu_periph_clock_enable(LCD_RCU); //��LCD(RCU_GPIOB)ʱ��
	gpio_init(LCD_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LCD_PIN_CS | LCD_PIN_RES | LCD_PIN_A0 | LCD_PIN_SDA | LCD_PIN_SCK); //��LCD_CS/LCD_A0/LCD_RST/LCD_SDA/LCD_SCK����Ϊ������������֧��50MHz
}

void lcd_st7735s_init(void)
{
    lcd_gpio_init();
    
    SET_LCD_RES; 
    delay_1ms(10);
	CLR_LCD_RES; 
	delay_1ms(10);
	SET_LCD_RES; 
	delay_1ms(200);
    
    lcd_write_register(0x11); //Sleep out 
    delay_1ms(120);   
    
    lcd_write_register(0xB1); 
    lcd_write_data(0x05); 
    lcd_write_data(0x3C);
    lcd_write_data(0x3C); 
    
    lcd_write_register(0xB2); 
    lcd_write_data(0x05); 
    lcd_write_data(0x3C); 
    lcd_write_data(0x3C); 
    
    lcd_write_register(0xB3); 
    lcd_write_data(0x05); 
    lcd_write_data(0x3C); 
    lcd_write_data(0x3C); 
    lcd_write_data(0x05); 
    lcd_write_data(0x3C); 
    lcd_write_data(0x3C); 
    
    lcd_write_register(0xB4);
    lcd_write_data(0x03); 
    
    lcd_write_register(0xC0); 
    lcd_write_data(0x28); 
    lcd_write_data(0x08); 
    lcd_write_data(0x04); 
    
    lcd_write_register(0xC1); 
    lcd_write_data(0XC0); 
    
    lcd_write_register(0xC2); 
    lcd_write_data(0x0D); 
    lcd_write_data(0x00); 
    
    lcd_write_register(0xC3); 
    lcd_write_data(0x8D); 
    lcd_write_data(0x2A); 
    
    lcd_write_register(0xC4); 
    lcd_write_data(0x8D); 
    lcd_write_data(0xEE); 
    
    lcd_write_register(0xC5);
    lcd_write_data(0x1A); 
    
    lcd_write_register(0x36);
    lcd_write_data(0xC0); 
    
    lcd_write_register(0xE0); 
    lcd_write_data(0x04); 
    lcd_write_data(0x22); 
    lcd_write_data(0x07); 
    lcd_write_data(0x0A); 
    lcd_write_data(0x2E); 
    lcd_write_data(0x30); 
    lcd_write_data(0x25); 
    lcd_write_data(0x2A); 
    lcd_write_data(0x28); 
    lcd_write_data(0x26); 
    lcd_write_data(0x2E); 
    lcd_write_data(0x3A); 
    lcd_write_data(0x00); 
    lcd_write_data(0x01); 
    lcd_write_data(0x03); 
    lcd_write_data(0x13); 
    
    lcd_write_register(0xE1); 
    lcd_write_data(0x04); 
    lcd_write_data(0x16); 
    lcd_write_data(0x06); 
    lcd_write_data(0x0D); 
    lcd_write_data(0x2D); 
    lcd_write_data(0x26); 
    lcd_write_data(0x23); 
    lcd_write_data(0x27); 
    lcd_write_data(0x27); 
    lcd_write_data(0x25); 
    lcd_write_data(0x2D); 
    lcd_write_data(0x3B); 
    lcd_write_data(0x00); 
    lcd_write_data(0x01); 
    lcd_write_data(0x04); 
    lcd_write_data(0x13); 
    
    lcd_write_register(0x3A);
    lcd_write_data(0x05);
    
    lcd_write_register(0x29); 
}

void lcd_write_register(unsigned char data)
{
	CLR_LCD_CS;
    CLR_LCD_A0;
 
    for(int i = 0; i < 8; i++)
    {
        if(data & 0x80)
        {
            SET_LCD_SDA;
        }
        else 
        {
            CLR_LCD_SDA;
        }
        CLR_LCD_SCK;
        SET_LCD_SCK;
        data = data << 1;
    }	 
    SET_LCD_CS;
}

void lcd_write_data(unsigned char data)
{
	CLR_LCD_CS;
    SET_LCD_A0;

    for(int i = 0; i < 8; i++)
    {
        if( data & 0x80 )
        {
            SET_LCD_SDA;
        }
        else 
        {
            CLR_LCD_SDA;
        }
        CLR_LCD_SCK;
        SET_LCD_SCK;
        data = data << 1;
    }
    SET_LCD_CS;
}

void lcd_write_data_u16(unsigned short data)
{
    lcd_write_data(data>>8);
    lcd_write_data(data);
}

void lcd_set_address(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{	     
    lcd_write_register(0x2A); 
    lcd_write_data(x1>>8); 
    lcd_write_data(x1&0xFF);
    lcd_write_data(x2>>8); 
    lcd_write_data(x2&0xFF);

    lcd_write_register(0x2B); 
    lcd_write_data(y1>>8); 
    lcd_write_data(y1&0xFF);
    lcd_write_data(y2>>8); 
    lcd_write_data(y2&0xFF);
    
    lcd_write_register(0x2C);
}

void lcd_clear(unsigned short color)
{
    lcd_set_address(0, 0, 130, 162);
    
    for(unsigned char i = 0; i < 130; i++)
    {
        for (unsigned char j = 0; j < 162; j++)
	   	{
            lcd_write_data_u16(color);
	    }
    }
} 

//LCD����
void lcd_draw_point(unsigned short x, unsigned short y, unsigned short color)
{
	 lcd_set_address(x, y, x, y);//���ù��λ�� 
	 lcd_write_data_u16(color);
}

//���ٻ���
//x,y:����
//color:��ɫ
void lcd_fast_draw_point(unsigned short x, unsigned short y, unsigned short color)
{
	lcd_write_data_u16(color);
}	

//LCD������ʾ
void lcd_display_on(void)
{					   
	lcd_write_register(0x29);	//������ʾ
}	 
//LCD�ر���ʾ
void lcd_display_off(void)
{	   
	lcd_write_register(0x28);	//�ر���ʾ
}   

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void lcd_fill(unsigned short sx, unsigned short sy, unsigned short ex, unsigned short ey, unsigned short color)
{          
	unsigned short i, j;
	unsigned short xlen = 0;
	unsigned short ylen = 0;
	
	xlen = ex - sx + 1;
	ylen = ey - sy + 1;
		
	lcd_set_address(sx, sy, ex, ey);
    for(i = 0; i < xlen; i++)
	{
		for(j = 0; j < ylen; j++)
		{
			lcd_write_data_u16(color);
		}
	}		 
}  

//����
//x1,y1:�������
//x2,y2:�յ�����  
void lcd_draw_line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color)
{
	unsigned short t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1; //������������ 
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 
	
	//���õ������� 
	if( delta_x > 0 )
	{
		incx=1; 
	}
	else if( delta_x == 0 )//��ֱ�� 
	{
		incx=0;
	}
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}

	
	if( delta_y > 0 )
	{
		incy=1; 
	}
	else if( delta_y == 0 )//ˮƽ�� 
	{
		incy=0;
	}
	else
	{
		incy = -1;
		delta_y = -delta_y;
	} 
	
	if( delta_x > delta_y )//ѡȡ�������������� 
	{
		distance = delta_x; 
	}
	else
	{
		distance=delta_y; 
	}
	
	for(t = 0; t <= distance + 1; t++ )//������� 
	{  
		lcd_draw_point(uRow, uCol, color);//���� 
		xerr += delta_x ; 
		yerr += delta_y ; 
		if( xerr > distance ) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		
		if( yerr > distance ) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}  

void lcd_draw_rectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color)
{
	lcd_draw_line(x1, y1, x2, y1, color);
	lcd_draw_line(x1, y1, x1, y2, color);
	lcd_draw_line(x1, y2, x2, y2, color);
	lcd_draw_line(x2, y1, x2, y2, color);
}

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void lcd_draw_circle(unsigned short x0, unsigned short y0, unsigned char r, unsigned short color)
{
	int a, b;
	int di;
	a = 0;
	b = r;	  
	di = 3 - ( r<<1 );             //�ж��¸���λ�õı�־
	while( a <= b )
	{
		lcd_draw_point(x0+a, y0-b, color);
 		lcd_draw_point(x0+b, y0-a, color);        
		lcd_draw_point(x0+b, y0+a, color);       
		lcd_draw_point(x0+a, y0+b, color);
		lcd_draw_point(x0-a, y0+b, color);
 		lcd_draw_point(x0-b, y0+a, color);
		lcd_draw_point(x0-a, y0-b, color);
  		lcd_draw_point(x0-b, y0-a, color);
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if( di < 0 )
		{
			di += 4 * a + 6;	 
		} 
		else
		{
			di += 10 + 4 * ( a - b );   
			b--;
		} 						    
	}
} 	

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void lcd_draw_full_circle(unsigned short Xpos, unsigned short Ypos, unsigned short Radius, unsigned short Color)
{
	uint16_t x, y, r = Radius;
	for(y = Ypos - r; y < Ypos + r; y++)
	{
		for(x = Xpos - r;x < Xpos + r; x++)
		{
			if(((x - Xpos) * (x - Xpos) + (y - Ypos) * (y - Ypos)) <= r * r)
			{
				lcd_draw_point(x, y, Color);
			}
		}
	}
}

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void lcd_show_char(unsigned short x, unsigned short y, unsigned char num, unsigned char size, unsigned char mode, unsigned short pen_color, unsigned short back_color)
{  							  
    unsigned char temp, t1, t;
	unsigned short y0 = y;
	unsigned char csize = ( size / 8 + ( (size % 8) ? 1 : 0)) * (size / 2); //�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num = num - ' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	
	for(t = 0; t < csize; t++)
	{   
		if(size == 12)//����1206����
		{
			temp = asc2_1206[num][t]; 
		}
		else if(size == 16)//����1608����
		{
			temp=asc2_1608[num][t];	
		}
		else if(size == 24)	//����2412����
		{
			temp=asc2_2412[num][t];
		}
		else 
			return; //û�е��ֿ�
		
		for(t1 = 0; t1 < 8; t1++)
		{			    
			if( temp & 0x80 )
			{
				lcd_draw_point(x, y, pen_color);
			}
			else if( mode == 0)
			{
				lcd_draw_point(x, y, back_color);
			}
			temp <<= 1;
			y++;
			
			if(y >= 240)//������
			{
				return;	
			}	
			
			if((y-y0) == size)
			{
				y = y0;
				x++;
				if(x>=320)//������
				{
					return;	
				}
				break;
			}
		}  	 
	}  	    	   	 	  
}

//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void lcd_show_string(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char size, unsigned char *p, unsigned short pen_color, unsigned short back_color)
{         
	unsigned char x0 = x;
	width += x;
	height += y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x >= width)
		{
			x = x0;
			y += size;
		}
		
        if(y >= height)//�˳�
		{
			break;
		}
		
        lcd_show_char(x, y, *p, size, 0, pen_color, back_color);
        x += size / 2;
        p++;
    }  
}

//��������ʾ
//˵������������ȡģ��������õ� ָ���ĺ��� ���ִ�С��16x16	 ��32���ֽڴ洢һ������
// 		�ⲿ�ֺ����Ǵ��ڳ���ռ� ���Ժ��ֵĶ���ֱ��Ӱ�����ռ��ʣ����
//      ��Ҫ�����ھ���ʾ����ָ���ĺ�����˵�Ͳ��õ����ֿ��� 
//x  y  Ҫ��ʾ���ֵ�����
//c[2]  ���ֵ����� һ�����������ֽڱ�ʾ
//dcolor ���ֵ���ɫ   bgcolor ������ɫ
void GUI_sprintf_hz1616(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color)
{
	unsigned char i, j, k, m; //������ʱ����
	unsigned short x0, y0;
	x0 = x;
	y0=y;	
	lcd_set_address(x, y, x + 16 - 1, y + 16 - 1); //ѡ������λ��	

	for (k = 0; k < 64; k++) //64��ʾ�Խ����ֿ��еĸ������糬������������
	{                        
		if ((code_GB_16[k].Index[0]==c[0]) && (code_GB_16[k].Index[1]==c[1])) //Ѱ�Ҷ�Ӧ����	 һ��������Ҫ�����ֽ�
		{ 
			for(i = 0; i < 32; i++) //32���ֽ� ÿ���ֽڶ�Ҫһ����һ���㴦�� �����Ǵ�����32X8��
			{								    
				m = code_GB_16[k].Msk[i];							//��ȡ��Ӧ�ֽ�����
				for(j = 0; j < 8; j++) 									//��ʾһ���ֽ�  һ���ֽ�8λ Ҳ����8����
				{
					//�ж��Ƿ���Ҫд���
					if( (m&0x80) == 0x80)
					{
						lcd_fast_draw_point(x, y, pen_color); // ����� ��������ɫ
					}						 	 	
					else 			
					{
						lcd_fast_draw_point(x, y, back_color); //������� Ϊ����ɫ  ����ɫ
					}						
					m <<= 1; //����һλ  �ж���һ��
					x++;
					
					if(x - x0 == 16)
					{
						x = x0;
						y++;
						if(y - y0 >= 16)
						{
							return;
						}
					}
				} 
			}
		}  
	}	
}

//��ʾ�ַ��� 
//x1 y1 ��ʾ�ĳ�ʼλ��
//*str Ҫ��ʾ������
//dcolor ��ʾ�ַ�����ɫ
//bgcolor ��ʾ�ַ��ı�����ɫ  
void GUI_sprintf_hz16x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short pen_color, unsigned short back_color)	  
{  
	unsigned char l = 0;
	while(*str)
	{	
		if(*str>=0x80)
		{
			GUI_sprintf_hz1616(x1 + l * 8, y1, (unsigned char*)str, pen_color, back_color);
			str += 2;
			l += 2;
		}
	}	
}

//��ʾ32x32��������
//(x��y) ����ʾ���ݵ����Ͻ����꣬c[2]��ʾ���ֵ������ֽ�
//dcolor ���ֵ���ɫ   bgcolor ������ɫ
//˵������ָ��λ������ʾһ��32x32�ĺ���
void GUI_sprintf_hz3232(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color)
{
	unsigned char i, j, k;
	unsigned short x0, y0;
	x0 = x;
	y0 = y;	

	lcd_set_address(x, y, x + 32 - 1, y + 32 - 1); //ѡ������λ��	
	
	for (k = 0; k < 100; k++) //�Խ����ֿ⣨k���ֵ�ͺ��ֿ��к��ָ����йأ���ѭ����ѯ����
	{ 
		if ((code_GB_32[k].Index[0]==c[0])&&(code_GB_32[k].Index[1]==c[1])) //Ѱ��Ҫ��ʾ�ĺ���
		{ 
			for(i = 0; i < 128; i++) //1������Ҫ128���ֽڵ�����ʾ
			{
				unsigned char m = code_GB_32[k].Msk[i]; //һ���ֽ�һ���ֽڵ���ʾ
				for(j = 0; j < 8; j++) 
				{
					//�ж��Ƿ���Ҫд���
					if((m&0x80)==0x80) // �����,��������ɫ
					{
						lcd_fast_draw_point(x,y,pen_color);		
					}
					else //�������,Ϊ����ɫ
					{
						lcd_fast_draw_point(x,y,back_color);	
					}
					m<<=1;
					x++;
					if(x - x0 == 32)
					{
						x = x0;
						y++;
						if(y - y0 >= 32)
						{
							return;
						}
					}
				}    
			}
		}  
	}	
}

//��ʾ32x32���� ��32x16 ��ĸ��
//x1��y1����ʾ���ݵ����Ͻ����꣬
//dcolor ���ֵ���ɫ   bgcolor ������ɫ
//*str Ҫ��ʾ������
void GUI_sprintf_hz32x(unsigned short x1, unsigned short y1, unsigned char *str, unsigned short pen_color, unsigned short back_color)	 
{  
	unsigned char l = 0;	  
	while(*str)
	{
		if(*str>=0x80)		 	        
		{
			GUI_sprintf_hz3232(x1 + l * 8, y1, (unsigned char*)str, pen_color, back_color);
			l += 4;
			str += 2;
		}
	}
}
