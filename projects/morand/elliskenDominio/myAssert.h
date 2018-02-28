#ifndef _MYASSERT_H
#define _MYASSERT_H
#include <stdlib.h>

int myAssert(int res, char * file, int line){
	if (res == 1){
		return 0;
	}
	else {
	 	 printf("*** Did not pass assert test in file '%s' line %d.***\n\n", file, line);
 		 return 0; //maybe change to 0
	}
}
#endif