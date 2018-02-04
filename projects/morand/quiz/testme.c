#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	char randString[] = "[]{}() ax";
	int n = rand() % 9;
	char randChar = randString[n];
     // For acceptable range of ASCII characters
    // use formula for range [M, N]
    // M + (rand()% N - M + 1)

	 // In this case specifically,
	 // we need ASCII numbers 32 - 125, which are characters
	 //'space' through closing curly brace }


   //char randChar = 32 + (rand()% (125 - 32 + 1));
    return randChar;
}

char * inputString()
{
	char randString2[] = "reset\0";
	char randChar;
	char myString[6];
	int i;
	for(i = 0; i < 6; i++){
		int p = rand() % 6;
		char myChar = randString2[p];
		myString[i] = myChar;
	}
	static char * myStr;
	myStr = myString;
	//printf("%s", myString);
	// For acceptable range of ASCII characters
	// use formula for range [M, N]
    // M + (rand()% N - M + 1)

    // In this case specifically,
	// we need ASCII numbers 10 - 116, which are characters
	// 'line feed' and 't'

	//static preserves memory irrespective of fxn boundary
	//static char randString[6];
	//char randChar;
	//int i;
	//for(i = 0; i < 6; i++){
	//	randChar = 10 + (rand() % (116 - 10 + 1));
	//	randString[i] = randChar;
	//}
	//return randString;
	return myStr;
}

void testme()
{
  int tcCount = 0;
  char * s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
