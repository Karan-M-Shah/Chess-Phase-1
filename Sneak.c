#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "SneakyRooks.h"

int baseline(void)
{
	int i, success = 1;

	int numRooks = 3;
	int boardSize = 4;

	char *safeRooks[3];
	char *unsafeRooks[3];

	safeRooks[0] = "a3";
	safeRooks[1] = "b1";
	safeRooks[2] = "d4";

	unsafeRooks[0] = "a3";
	unsafeRooks[1] = "c3";
	unsafeRooks[2] = "d4";

	// Randomly toggle between calling the function on the safe rooks and the
	// unsafe rooks.
	for (i = 0; i < 32; i++)
	{
		if (rand() % 2 == 0)
		{
			if (allTheRooksAreSafe(safeRooks, numRooks, boardSize) != 1)
				return 0;  // failwhale
		}
		else
		{
			if (allTheRooksAreSafe(unsafeRooks, numRooks, boardSize) != 0)
				return 0;  // failwhale
		}
	}

	return success;
}

int main(void)
{
	int success = 1;

	Coordinate rook;
	rook.col = 0;
	rook.row = 0;
	parseCoordinateString("fancy58339", &rook);

	if (rook.col != 2768999 || rook.row != 58339)
		success = 0;

	printf("%s\n", success ? "Hooray!" : "failwhale :(");

	return 0;
}


int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
    int i;
    int row[10000] = { 0 };
    int col[10000] = { 0 };
    Coordinate *rookCoordinate = malloc(numRooks * sizeof(*rookCoordinate));
    for(i = 0; i < numRooks; i++)
    {
        rookCoordinate[i].col = 0;
        rookCoordinate[i].row = 0;
    }
    for(i = 0; i < numRooks; i++)
    {
        parseCoordinateString(rookStrings[i], rookCoordinate);
        //printf("%d %d\n", rookCoordinate[i].col, rookCoordinate[i].row);
        row[rookCoordinate[i].row]++;
        col[rookCoordinate[i].col]++;
        if(row[rookCoordinate[i].row] > 1 || col[rookCoordinate[i].col] > 1)
            return 0;
    }

    return 1;
}

void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
    int length = strlen(rookString);
    int i = 0;
    int multiplier = 1;
    int counter = 0;
    int counter2 = 0;
    char col[10];
    char row[10];
    int structnum = 0;

    while(rookCoordinate[i].col != 0 && rookCoordinate[i].row != 0)
    {
            structnum++;
            i++;
    }
    for(i = 0; i < 10; i++)
    {
        col[i] = '0';
        row[i] = ' ';
    }

    for(i = 0; i < length; i++)
    {
        if(isalpha(rookString[i]))
        {
            col[counter] = rookString[i];
            counter++;
        }
        else
        {
            row[counter2] = rookString[i];
            counter2++;
        }
    }

length = 0;
i = 0;
while(i < 10 && col[i] != '0')
{
    i++;
    length++;
}

  for(i = length-1; i >= 0; i--)
  {
  	rookCoordinate[structnum].col += (col[i] - 96) * multiplier;
    multiplier*=26;
  }

rookCoordinate[structnum].row = atoi(row);
}
