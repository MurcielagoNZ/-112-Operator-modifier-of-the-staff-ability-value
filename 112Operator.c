#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MaxL 10000
#define MaxN 1000

FILE *inf, *ouf;

char S[MaxL], t[MaxL], inputFileName[MaxN], backupFileName[MaxN];
int min = 101, i, space = 0, count = 0;
double points;

double randomPoints()
{
	if (min != 100)
		return((double) (rand() % (1000000 - min * 10000) + min * 10000) / 1000000);
	else
		return(100);
}

void change(char item[])
{
	if (!strstr(S, "0.0,"))
	{
		for (i = 0; i < strcspn(S, "\""); i++)
			fprintf(ouf, " ");
		fprintf(ouf, "\"%s\": %.7f,\n", item, points);
		printf("New %s = %f\n", item, points);
		count++;
	}
	else
		fputs(S, ouf);
}

void main(int argc, char *argv[])
{
	//get file name and make backup file name
	if (argc > 1)
		strcpy(inputFileName, argv[1]);
	else
	{
		printf("Input file name:\n");
		gets(inputFileName);
	}

	if (strchr(inputFileName, '\"'))
	{
		space = 1;
		strcpy(inputFileName, inputFileName + 1);
		inputFileName[strlen(inputFileName) - 1] = 0;
	}

	strcpy(backupFileName, inputFileName);
	strcat(backupFileName, ".old");

	while (min < 0 || min>100)
	{
		printf("Input min points (0 ~ 100):\n");
		scanf("%d", &min);
	}

	//make backup file
	strcpy(t, "copy ");
	if (space) strcat(t, "\"");
	strcat(t, inputFileName);
	if (space) strcat(t, "\"");
	strcat(t, " ");
	if (space) strcat(t, "\"");
	strcat(t, backupFileName);
	if (space) strcat(t, "\"");
	system(t);

	inf = fopen(backupFileName, "r");
	if (inf)
	{
		ouf = fopen(inputFileName, "w");
		printf("Old file backed up as: %s\n\n", backupFileName);
	}
	else
	{
		printf("File backup error! May need \"run as administrator\"\nor copy us to other folder!\n");
		system("pause");
		return(-1);
	}

	srand(time(NULL));
	while (fgets(S, MaxL, inf) != NULL)
	{
		memset(t, 0, sizeof(t));
		points = randomPoints();

		if (strstr(S, "firstAid"))
			change("firstAid");
		else if (strstr(S, "accuracy"))
			change("accuracy");
		else if (strstr(S, "drivingSkill"))
			change("drivingSkill");
		else if (strstr(S, "technicalSkill"))
			change("technicalSkill");
		else
			fputs(S, ouf);
	}

	fclose(inf);
	fclose(ouf);
	printf("\nAll done. \nTotal changed items: %d\n", count);
	system("pause");
}