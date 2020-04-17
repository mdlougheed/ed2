/*
This module contains library functions missing from C/80
*/


itoa(n,s) int n; char *s;
{
	static char *p;

	p = s;
	if (n == 0) *p++ = '0';
	else {
 		if (n < 0) { *p++ = '-'; n = -n; }
		itoarec(n,&p);
	}
	*p = '\0';
}

itoarec(n,p) int n; char **p;
{
	if (n) {
		itoarec(n/10,p);
		*(*p)++ = (n%10) + '0';
	}
}

isupper(c) char c;
{
	return (c>='A' && c<='Z');
}

islower(c) char c;
{
	return (c>='a' && c<='z');
}

isalpha(c) char c;
{
	return (isupper(c) || islower(c));
}

isdigit(c) char c;
{
	return (c>='0' && c<='9');
}

isspace(c) char c;
{
	return (c=='\t' || c=='\n' || c==' ');
}

toupper(c) char c;
{
	return (islower(c)? c&0xDF : c);
}

tolower(c) char c;
{
	return (isupper(c)? c|0x20 : c);
}

/*
max(a,b) int a,b;
{
	return (a>b? a : b);
}
*/

/*
min(a,b) int a,b;
{
	return (a<b? a : b);
}
*/

abs(i) int i;
{
	return (i<0? -i : i);
}

strcpy(dest,source) char *dest,*source;
{
	while (*dest++ = *source++) {
		;
	}
}

strcat(dest,source) char *dest,*source;
{
	while (*dest++) {
		;
	}
	strcpy(--dest,source);
}

