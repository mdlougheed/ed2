/*
Screen editor:  terminal output module
Source:  ed6.c
This file was created by the configuration program:
Version 2:  September 6, 1981.
*/

#include ed1.h

/*
This I/O section is designed for multiple terminals.
Include the following #define for VT100/ANSI escape
sequences, and comment it out for ADM-3A (Kaypro) escape sequences.
*/

/*
#define VT100
*/

/*
Define the current coordinates of the cursor.
*/

/*
Return the current coordinates of the cursor.
*/

outgetx()
{
	return(outx);
}

outgety()
{
	return(outy);
}

/*
Output one printable character to the screen.
*/

outchar(c) char c;
{
	syscout(c);
	outx++;
	return(c);
}

/*
Position cursor to position x,y on screen.
0,0 is the top left corner.
*/

outxy(x,y) int x,y;
{
	outx=x;
	outy=y;
#ifdef VT100
	syscout(27);
	syscout('[');
	syscout(++y/10+'0');
	syscout(y%10+'0');
	syscout(';');
	syscout(++x/10+'0');
	syscout(x%10+'0');
	syscout('H');
#else
	syscout(27);
	syscout('=');
	syscout(y+32);
	syscout(x+32);
#endif
}

/*
Erase the entire screen.
Make sure the rightmost column is erased.
*/

outclr()
{
#ifdef VT100
	syscout(27);
	syscout('[');
	syscout('H');
	syscout(27);
	syscout('[');
	syscout('J');
#else
	syscout(26);
#endif
}

/*
Delete the line on which the cursor rests.
Leave the cursor at the left margin.
*/

outdelln()
{
	outxy(0,outy);
	outdeol();
}

/*
Delete to end of line.
Assume the last column is blank.
*/

outdeol()
{
#ifdef VT100
	syscout(27);
	syscout('[');
	syscout('K');
#else
	syscout(24);
#endif
}

/*
Return yes if terminal has indicated hardware scroll.
*/

outhasup()
{
	return(YES);
}

outhasdn()
{
	return(YES);
}

/*
Scroll the screen up.
Assume the cursor is on the bottom line.
*/

outsup()
{
	syscout(10);
}

/*
Scroll screen down.
Assume the cursor is on the top line.
*/

outsdn()
{
#ifdef VT100
	syscout(27);
	syscout('[');
	syscout('H');
	syscout(27);
	syscout('M');
#else
	syscout(30); 
	syscout(27);
	syscout('E');
#endif
	outxy(outx,outy);
}
