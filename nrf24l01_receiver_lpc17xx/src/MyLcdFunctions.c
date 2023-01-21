#include "MyLcdFunctions.h"

// rysuje linie od punktu (x1, y1) do (x2, y2)
void BresenhamLine(const int x1, const int y1, const int x2, const int y2, const int color)
{
	int d, dx, dy, ai, bi, xi, yi;
  int x = x1, y = y1;
	uint16_t colorPrint;
	
  if (x1 < x2)
  {
    xi = 1;
		dx = x2 - x1;
  }
  else
  {
    xi = -1;
    dx = x1 - x2;
  }

  if (y1 < y2)
  {
    yi = 1;
    dy = y2 - y1;
  }
  else
  {
    yi = -1;
    dy = y1 - y2;
  }
	
	
	switch (color){
		case 1:
				colorPrint = LCDYellow;
			break;
		default:
				colorPrint = LCDCyan;
			break;
	}

  lcdWriteReg(ADRX_RAM, x);
  lcdWriteReg(ADRY_RAM, y);
	lcdWriteReg(DATA_RAM, colorPrint);

  if (dx > dy)
  {
		ai = (dy - dx) * 2;
    bi = dy * 2;
    d = bi - dx;

    while (x != x2)
    {
			if (d >= 0)
      {
				x += xi;
        y += yi;
        d += ai;
      }
      else
      {
        d += bi;
        x += xi;
      }
      lcdWriteReg(ADRX_RAM, x);
      lcdWriteReg(ADRY_RAM, y);
      lcdWriteReg(DATA_RAM, colorPrint);
    }
  }
  else
  {
		ai = ( dx - dy ) * 2;
    bi = dx * 2;
    d = bi - dy;

    while (y != y2)
    {
			if (d >= 0)
      {
        x += xi;
        y += yi;
				d += ai;
      }
      else
      {
        d += bi;
        y += yi;
      }
      lcdWriteReg(ADRX_RAM, x);
      lcdWriteReg(ADRY_RAM, y);
      lcdWriteReg(DATA_RAM, colorPrint);
    }
  }
}
 
void printLetter(char let, int row, int col)
{
	unsigned char buffer[16];
	GetASCIICode(0, buffer, let);
	for (uint16_t i=0; i < 8; ++i)
		for (uint16_t j=0; j < 16; ++j)
			if ((buffer[j] & (1<<i)) == (1<<i))
			{
				lcdWriteReg(ADRX_RAM, LCD_MAX_X - (row-1)*15 - j);
			  lcdWriteReg(ADRY_RAM, col*8 - i);
			  lcdWriteReg(DATA_RAM, LCDWhite);
			}
}

void printLine(char* line, int row, int col)
{
	int length = strlen(line);
	for (uint16_t i = 0; i < length; ++i)
		printLetter(line[i], row, col+i);
}

void printText(char* text, int row, int col)
{
	int length = strlen(text);
	char bufToPrint[40]=  "";
	char buf[40] = "";
	int rowIter = row;
	for (int i=0, prev=0; i < length; ++i)
		if (text[i] == ' ' || i == length - 1)
		{
			strncpy(buf, text+prev, i-prev+1);
			buf[i-prev+1] = '\0';
			if (strlen(bufToPrint) + strlen(buf) > 38 - col)
			{
				printLine(bufToPrint, rowIter++, col);
				memset(bufToPrint, '\0', 40);
			}
			prev = i+1;
			strncpy(bufToPrint+strlen(bufToPrint), buf, strlen(buf));
		}
		
	printLine(bufToPrint, rowIter++, col);
}

void clearLeterAtPosition(int row, int col)
{
	for (uint16_t j=0; j < 8; ++j)
		for (uint16_t i=0; i < 15; ++i)
		{
			lcdWriteReg(ADRX_RAM, LCD_MAX_X - (row-1)*15 - i);
			lcdWriteReg(ADRY_RAM, col*8 - j);
			lcdWriteReg(DATA_RAM, LCDBlack);
		}
}

void clearFragment(int rowStart, int colStart, int rowEnd, int colEnd)
{
	for (int i=rowStart; i <= rowEnd; ++i)
		for (int j=colStart; j <= colEnd; ++j)
			clearLeterAtPosition(i, j);
}

void clearScreen()
{
	lcdWriteReg(ADRX_RAM, 0);
	lcdWriteReg(ADRY_RAM, 0);
	for (uint16_t j=0; j < LCD_MAX_Y; ++j)
		for (uint16_t i=0; i < LCD_MAX_X; ++i)
		{
				lcdWriteReg(DATA_RAM, LCDBlack);
		}
}

void printTriangle(int x, int y, int color)
{
	BresenhamLine(LCD_MAX_X - x, y, LCD_MAX_X - (x+15) , y, color);
	BresenhamLine(LCD_MAX_X - (x+15) , y, LCD_MAX_X - (x+8) , y+15, color );
	BresenhamLine(LCD_MAX_X - x, y, LCD_MAX_X - (x + 8) , y+15, color);
}

void drawBorder()
{
	BresenhamLine(10, 10, LCD_MAX_X-10 , 10, 0);
	BresenhamLine(10, LCD_MAX_Y-10, LCD_MAX_X-10 , LCD_MAX_Y-10, 0);
	BresenhamLine(10, LCD_MAX_Y-10, 10 , 10, 0);
	BresenhamLine(LCD_MAX_X-10, LCD_MAX_Y-10, LCD_MAX_X-10 , 10, 0);
}
