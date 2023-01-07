#include "gd32f10x.h"
#include "LCD_ST7735S.h"
#include "font.h"
#include "hz_16x16.h"
#include "hz_32x32.h"
#include "systick.h"

void lcd_gpio_init(void)
{
    rcu_periph_clock_enable(LCD_RCU); //打开LCD(RCU_GPIOB)时钟
	gpio_init(LCD_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LCD_PIN_CS | LCD_PIN_RES | LCD_PIN_A0 | LCD_PIN_SDA | LCD_PIN_SCK); //将LCD_CS/LCD_A0/LCD_RST/LCD_SDA/LCD_SCK配置为推挽输出，最高支持50MHz
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

//LCD画点
void lcd_draw_point(unsigned short x, unsigned short y, unsigned short color)
{
	 lcd_set_address(x, y, x, y);//设置光标位置 
	 lcd_write_data_u16(color);
}

//快速画点
//x,y:坐标
//color:颜色
void lcd_fast_draw_point(unsigned short x, unsigned short y, unsigned short color)
{
	lcd_write_data_u16(color);
}	

//LCD开启显示
void lcd_display_on(void)
{					   
	lcd_write_register(0x29);	//开启显示
}	 
//LCD关闭显示
void lcd_display_off(void)
{	   
	lcd_write_register(0x28);	//关闭显示
}   

//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
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

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void lcd_draw_line(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned short color)
{
	unsigned short t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1; //计算坐标增量 
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 
	
	//设置单步方向 
	if( delta_x > 0 )
	{
		incx=1; 
	}
	else if( delta_x == 0 )//垂直线 
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
	else if( delta_y == 0 )//水平线 
	{
		incy=0;
	}
	else
	{
		incy = -1;
		delta_y = -delta_y;
	} 
	
	if( delta_x > delta_y )//选取基本增量坐标轴 
	{
		distance = delta_x; 
	}
	else
	{
		distance=delta_y; 
	}
	
	for(t = 0; t <= distance + 1; t++ )//画线输出 
	{  
		lcd_draw_point(uRow, uCol, color);//画点 
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

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void lcd_draw_circle(unsigned short x0, unsigned short y0, unsigned char r, unsigned short color)
{
	int a, b;
	int di;
	a = 0;
	b = r;	  
	di = 3 - ( r<<1 );             //判断下个点位置的标志
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
		//使用Bresenham算法画圆     
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

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
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

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void lcd_show_char(unsigned short x, unsigned short y, unsigned char num, unsigned char size, unsigned char mode, unsigned short pen_color, unsigned short back_color)
{  							  
    unsigned char temp, t1, t;
	unsigned short y0 = y;
	unsigned char csize = ( size / 8 + ( (size % 8) ? 1 : 0)) * (size / 2); //得到字体一个字符对应点阵集所占的字节数	
 	num = num - ' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	
	for(t = 0; t < csize; t++)
	{   
		if(size == 12)//调用1206字体
		{
			temp = asc2_1206[num][t]; 
		}
		else if(size == 16)//调用1608字体
		{
			temp=asc2_1608[num][t];	
		}
		else if(size == 24)	//调用2412字体
		{
			temp=asc2_2412[num][t];
		}
		else 
			return; //没有的字库
		
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
			
			if(y >= 240)//超区域
			{
				return;	
			}	
			
			if((y-y0) == size)
			{
				y = y0;
				x++;
				if(x>=320)//超区域
				{
					return;	
				}
				break;
			}
		}  	 
	}  	    	   	 	  
}

//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void lcd_show_string(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char size, unsigned char *p, unsigned short pen_color, unsigned short back_color)
{         
	unsigned char x0 = x;
	width += x;
	height += y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x >= width)
		{
			x = x0;
			y += size;
		}
		
        if(y >= height)//退出
		{
			break;
		}
		
        lcd_show_char(x, y, *p, size, 0, pen_color, back_color);
        x += size / 2;
        p++;
    }  
}

//程序汉字显示
//说明：汉字是用取模软件制作好的 指定的汉字 汉字大小是16x16	 即32个字节存储一个汉字
// 		这部分汉字是存在程序空间 所以汉字的多少直接影响程序空间的剩余量
//      主要方便于就显示几个指定的汉字来说就不用调用字库了 
//x  y  要显示汉字的坐标
//c[2]  汉字的数据 一个汉字两个字节表示
//dcolor 汉字的颜色   bgcolor 背景颜色
void GUI_sprintf_hz1616(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color)
{
	unsigned char i, j, k, m; //定义临时变量
	unsigned short x0, y0;
	x0 = x;
	y0=y;	
	lcd_set_address(x, y, x + 16 - 1, y + 16 - 1); //选择坐标位置	

	for (k = 0; k < 64; k++) //64表示自建汉字库中的个数，如超过，可以扩增
	{                        
		if ((code_GB_16[k].Index[0]==c[0]) && (code_GB_16[k].Index[1]==c[1])) //寻找对应汉字	 一个汉字需要两个字节
		{ 
			for(i = 0; i < 32; i++) //32个字节 每个字节都要一个点一个点处理 所以是处理了32X8次
			{								    
				m = code_GB_16[k].Msk[i];							//读取对应字节数据
				for(j = 0; j < 8; j++) 									//显示一个字节  一个字节8位 也就是8个点
				{
					//判断是否是要写入点
					if( (m&0x80) == 0x80)
					{
						lcd_fast_draw_point(x, y, pen_color); // 如果是 给字体颜色
					}						 	 	
					else 			
					{
						lcd_fast_draw_point(x, y, back_color); //如果不是 为背景色  给颜色
					}						
					m <<= 1; //左移一位  判断下一点
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

//显示字符串 
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示字符的颜色
//bgcolor 显示字符的背景颜色  
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

//显示32x32单个汉字
//(x，y) 是显示内容的左上角坐标，c[2]表示汉字的两个字节
//dcolor 汉字的颜色   bgcolor 背景颜色
//说明：在指定位置上显示一个32x32的汉字
void GUI_sprintf_hz3232(unsigned short x, unsigned short y, unsigned char c[2], unsigned short pen_color, unsigned short back_color)
{
	unsigned char i, j, k;
	unsigned short x0, y0;
	x0 = x;
	y0 = y;	

	lcd_set_address(x, y, x + 32 - 1, y + 32 - 1); //选择坐标位置	
	
	for (k = 0; k < 100; k++) //自建汉字库（k最大值和汉字库中汉字个数有关），循环查询内码
	{ 
		if ((code_GB_32[k].Index[0]==c[0])&&(code_GB_32[k].Index[1]==c[1])) //寻找要显示的汉字
		{ 
			for(i = 0; i < 128; i++) //1个汉字要128个字节点来显示
			{
				unsigned char m = code_GB_32[k].Msk[i]; //一个字节一个字节的显示
				for(j = 0; j < 8; j++) 
				{
					//判断是否是要写入点
					if((m&0x80)==0x80) // 如果是,给字体颜色
					{
						lcd_fast_draw_point(x,y,pen_color);		
					}
					else //如果不是,为背景色
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

//显示32x32汉字 和32x16 字母串
//x1，y1是显示内容的左上角坐标，
//dcolor 汉字的颜色   bgcolor 背景颜色
//*str 要显示的数据
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
