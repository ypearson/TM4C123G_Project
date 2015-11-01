#include "cstr.h"

int cstrlen(const char *str)
{
    int len = 0;

    while(* (str + len) )
        len++;

    return len;

}

int cstrcmp(const char *s1, const char *s2)
{
    int res = 0;
    int len = 0;

    len = cstrlen(s1) - cstrlen(s2);

    if(!len)
    {
    	while(*s1)
    	{
	        if(*s1++ - *s2++)
	        {
	            res = 1;
	            break;
	        }
    	}
    }
    else
    {
    	res = 1;
    }

    return res;
}

void memclear(uint8_t *pd, uint8_t sz)
{
    uint8_t i;

    for(i = 0; i < sz; i++)
        *(pd+i) = 0;
}
