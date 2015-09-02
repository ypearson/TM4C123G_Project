#include "string.h"

int cstrcmp(const char *s1, const char *s2)
{
    int res = 0;
    int len = 0;
    const char *s = s1;

    while(*s)
    {
    	s++;
    	len++;
    }
    s = s2;

    while(*s)
    {
    	s++;
    	len--;
    }

    if( !(len) )
    {
    	while(*s1)
    	{
	        if(*s1 - *s2)
	        {
	            res = 1;
	            break;
	        }
	        s1++;
	        s2++;
    	}
    }
    else
    {
    	res = 1;
    }

    return res;
}