#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "delivery.h"


int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
    int weight;
    double size;
    char destinationName[4];
    char exitChar = 'x';

    //initialize all trucks 
    struct Truck trucks[3] = {
        {
            BLUE, 0,0, NULL,0
        },
        {
            GREEN, 0,0, NULL,0
        },
        {
            YELLOW, 0,0, NULL,0
        }
    };

	//struct Map routeMap = addRoute(&baseMap, &blueRoute);
	//printMap(&routeMap, 1, 1);

    displayHeader();

    while (1)
    {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        int scanfResult = scanf("%d %lf %s", &weight, &size, &destinationName);
        int exitProgram = weight==0 && size==0 && destinationName[0]==exitChar && destinationName[1]=='\0';

        if (scanfResult != 3)
        {
            //error: invalid input entered
            printf("Invalid input\n");
            // Clear the input buffer to avoid any further issues
            while (getchar() != '\n');
        }else if(exitProgram)
        {
            break;
        }
        else
        {
            processPackage(weight, size, destinationName, trucks);
        }
    }

    printf("Thanks for shipping with Seneca!");
	return 0;
}