#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	char relyFileName[256] = "gcc -o Main Main.c ";
	
	for(i = 1; i < argc; i++)
	{
		strcat(relyFileName, argv[i]);
		strcat(relyFileName, " ");
	}
	
	system(relyFileName);
	system("Main > Text.txt");
	system("start notepad++ Text.txt");
	
	return 0;
}