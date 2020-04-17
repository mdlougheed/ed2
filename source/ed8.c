/* Screen editor:  operating system module
 *		   C/80 version
 *
 * Source:  ed8.c
 * Version: June 19, 1981.
 */

/* define globals */

#include ed1.h


/* all calls to the operating system are made here.
 * only this module will have to be
 * rewritten for a new operating system.
 */

/* CP/M 2.2 versions of syscstat(), syscin(), syscout() */

/* return -1 if no character is ready from the console.
 * otherwise, return the character.
 */

syscstat()
{
	return(bdos(6,-1));
}

/* wait for next character from the console.
 * do not echo it.
 */

syscin()
{
int c;
	while ((c=bdos(6,-1))==0) {
		;
	}
	return(c);
}

/* print character on the console */

syscout(c) char c;
{
	bdos(6,c);
	return(c);
}


/* print character on the printer */

syslout(c) char c;
{
	bdos(5,c);
	return(c);
}

/* open a file */

sysopen(name,mode) char *name, *mode;
{
int file;
int m;
	m=tolower(mode[0]);
	if (m=='r' || m=='w') {
		if ((file=fopen(name,mode))==0) {
			iormode='c';
			return(ERR);
		}
		else {
			iormode=m;
			return(file);
		}
	}
	else {
		iormode='c';
		syserr("fopen: bad mode");
		return(ERR);
	}
}

/* close a file */

sysclose(file) int file;
{
	if (iormode=='w') {
		/* write end of file byte */
		putc(0x1a,file);
	}
	iormode='c';
	fclose(file);
	return(OK);
}

/* read next char from file */

sysrdch(file) int file;
{
int c;
	if (iormode!='r') {
		error ("sysrdch:  read in w mode");
		return(ERR);
	}
	if ((c=getc(file))==-1) {
		return(EOF);
	}
	else if (c==0x1a) {
		return(EOF);
	}
	else if (c=='\n') {
		return (CR);
	}
	else {
		return(c);
	}
}

/* write next char to file */

syspshch(c,file) char c; int file;
{
char ch;
	if (iormode!='w') {
		error("syspshch:  write in r mode");
		return(ERR);
	}
	if (c==CR) {
		ch='\n';
	}
	else {
		ch=c;
	}
	if (putc(ch,file)==-1) {
		error("disk write failed");
		return(ERR);
	}
	else {
		return(c);
	}
}

/* read one char from END of file */

syspopch(file) int file;
{
	error("syspopch() not implemented");
	return(ERR);
}

/* check file name for syntax */

syschkfn(args) char *args;
{
	return(OK);
}

/* copy file name from args to buffer */

syscopfn(args,buffer) char *args, *buffer;
{
int n;
	n=0;
	while (n<(SYSFNMAX-1)) {
		if (args[n]==EOS) {
			break;
		}
		else {
			buffer[n]=args[n];
			n++;
		}
	}
	buffer[n]=EOS;
}

/* move a block of n bytes down (towards HIGH addresses).
 * block starts at source and the first byte goes to dest.
 *	src:[<--n-->]   dest:[       ]
 */

sysmovdn(n,dest,source) int n; char *dest, *source;
{
	if (n>0) {
#asm
	DB 0DDH,0E1H	;POP IX = return address in IX
	POP H		;source in HL
	POP D		;dest in DE
	POP B		;count in BC
	PUSH B		;restore args
	PUSH D
	PUSH H
	DB 0DDH,0E5H	;PUSH IX
	XCHG
	DAD B
	XCHG		;dest+count in DE
	DAD B		;source+count in HL
	INX B		;count+1 in BC
	DB 0EDH,0B8H	;LDDR
#endasm
	}
}

/* move a block of n bytes up (towards LOW addresses).
 * the block starts at source and the first byte goes to dest.
 *	dest:[       ]   src:[<--n-->]
 */

sysmovup(n,dest,source) int n; char *dest, *source;
{
	if (n>0) {
#asm
	DB 0DDH,0E1H	;POP IX = return address in IX
	POP H		;source in HL
	POP D		;dest in DE
	POP B		;count in BC
	PUSH B		;restore args
	PUSH D
	PUSH H
	DB 0DDH,0E5H	;PUSH IX
	DB 0EDH,0B0H	;LDIR
#endasm
	}
}

/*
Interfaces with operating system functions
*/

bdos(c,d) int c,d;
{
#asm
	POP H
	POP D
	POP B
	PUSH B
	PUSH D
	PUSH H
	CALL 5
#endasm
}
