#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int newRand = rand();
	if ((newRand % 10 + 1) == 1) {
		return '[';
	}
	else if ((newRand % 10 + 1) == 2) {
		return '(';
	}
	else if ((newRand % 10 + 1) == 3) {
		return '{';
	}
	else if ((newRand % 10 + 1) == 4) {
		return ' ';
	}
	else if ((newRand % 10 + 1) == 5) {
		return 'a';
	}
	else if ((newRand % 10 + 1) == 6) {
		return 'x';
	}
	else if ((newRand % 10 + 1) == 7) {
		return '}';
	}
	else if ((newRand % 10 + 1) == 8) {
		return ')';
	}
	else if ((newRand % 10 + 1) == 9) {
		return ']';
	}
	else {
		return ' ';
	}
}

char *inputString()
{
	char * inputString = malloc(4 * sizeof(char));
	int newRand[6];
	for (int i = 0; i < 5; i++) {
		newRand[i] = rand();
	}

	for (int i = 0; i < 5; i++) {
		if ((newRand[i] % 4 + 1) == 1) {
			inputString[i] = 'r';
		}
		else if ((newRand[i] % 4 + 1) == 2) {
			inputString[i] = 'e';
		}
		else if ((newRand[i] % 4 + 1) == 3) {
			inputString[i] = 's';
		}
		else if ((newRand[i] % 4 + 1) == 4) {
			inputString[i] = 't';
		}
	}

	inputString[5] = '\0';
    return inputString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  s = inputString();
  printf("%s", s);
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
