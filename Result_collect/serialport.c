#include<stdio.h>
#include<windows.h>
 
int main()
{
	FILE *fp;
	if ((fp = fopen("com6", "r")) == NULL)
	{
		printf("cannot open com!\n");
	}
	else
		printf("open com successful!\n");

    FILE * result;
    result = fopen("result.txt", "a+");
  
    if(!result) 
    printf("cannot open the file!");

	char str;
 
	while (1)
	{
		fscanf(fp, "%c", &str);
		printf("%c ", str);

        fputc(str, result);
 
		Sleep(100);
	}

    fclose(result);

    printf("successful close the file!");
 
	return 0;
}