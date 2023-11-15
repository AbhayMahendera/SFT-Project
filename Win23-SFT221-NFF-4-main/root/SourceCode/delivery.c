#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mapping.h"
#include "delivery.h"

int reachedDestination(const struct Point p1, const struct Point p2)
{
	double positionDistance = distance(&p1, &p2);
	return positionDistance == 1;
}

int isValidPackageWeight(int weight)
{
	return (weight > 0 && weight <= MAX_WEIGHT_CAPACITY);
}

int isValidPackageSize(double size)
{
	return (size == .25 || size == .5 || size == 1.0);
}

int isValidPackage(int weight, double size)
{
	return (isValidPackageWeight(weight) && isValidPackageSize(size));
}

struct Point convertDestinationNametoPoint(const char arr[])
{
	struct Point dest = { -1,-1 };


	// TODO - parse destName and convert to a valid point

	int i = 0, num = 0;
	char ch = '\0';

	while (arr[i])
	{
		if (isdigit(arr[i]))
		{
			num = num * 10 + (arr[i] - '0');
		}
		else if (isalpha(arr[i]))
		{
			ch = arr[i];
		}
		i++;
	}

	if (ch != '\0')
	{
		ch = tolower(ch);
	}

	if (num > 0 && num <= 25 && isalpha(ch) && ch != 'z')
	{
		dest.row = num - 1;
		dest.col = findAlphaIndex(ch);
	}

	return dest;
}

char* convertPointToDestinationName(const struct Point pt)
{
	char destName[3] = { 0 };
	int row;
	char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	if (pt.row >= 0 && pt.row < 25 && pt.col >= 0 && pt.col < 25)
	{
		row = pt.row + 1;
		//destName[0] = row + '0';
		destName[0] = row;
		destName[1] = letters[pt.col];
		//	destName[2] = '\0';
	}/*
	else
	{
		destName[0] = '\0';
	}*/
	return destName;
}

int isValidDestinationName(const char destinationName[])
{
	struct Point dest = convertDestinationNametoPoint(destinationName);
	return (dest.col != -1 && dest.row != -1);
}
/**
* Helper function to convert a character to correspondent index
*/
int findAlphaIndex(char c)
{
	char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	int size = sizeof(letters) / sizeof(char);
	c = tolower(c);
	for (int i = 0; i < size; i++)
	{
		if (tolower(letters[i]) == c)
		{
			return i;
		}
	}
	return -1;  // If letter is not found
}

int* getTrucksWithCapacity(struct Truck trucks[], int numberOfTrucks, struct Package pkg)
{
	int idxs[3] = { 0 };
	for (int i = 0; i < numberOfTrucks; i++)
	{
		if ((MAX_WEIGHT_CAPACITY - trucks[i].currentWeight) >= pkg.weight &&
			(MAX_VOLUME_CAPACITY - trucks[i].currentVolume) >= pkg.size)
		{
			idxs[i] = 1;
		}
	}
	return idxs;
}

double getDistanceToDestination(struct Route* route, struct Point dest)
{

	int closestPoint = getClosestPoint(route, dest);
	double distanceFromClosestPoint = distance(&route->points[closestPoint], &dest);
	return distanceFromClosestPoint;
}


struct Route* getRouteBasedOnSymbol(char symbol)
{
	struct Route routeToFollow;
	switch (symbol)
	{
	case BLUE:
		routeToFollow = getBlueRoute();
		break;
	case GREEN:
		routeToFollow = getGreenRoute();
		break;
	case YELLOW:
		routeToFollow = getYellowRoute();
	}
	return &routeToFollow;
}


int findBetterCapacityTruck(const struct Truck* truck1, const struct Truck* truck2)
{
	double truck1WeightCapacityPercent = ((MAX_WEIGHT_CAPACITY - truck1->currentWeight) / MAX_WEIGHT_CAPACITY) * 100;
	double truck1WeightVolumePercent = ((MAX_VOLUME_CAPACITY - truck1->currentVolume) / MAX_VOLUME_CAPACITY) * 100;
	double truck1Capacity = (truck1WeightCapacityPercent + truck1WeightVolumePercent) / 2;


	double truck2WeightCapacityPercent = ((MAX_WEIGHT_CAPACITY - truck2->currentWeight) / MAX_WEIGHT_CAPACITY) * 100;
	double truck2WeightVolumePercent = ((MAX_VOLUME_CAPACITY - truck2->currentVolume) / MAX_VOLUME_CAPACITY) * 100;
	double truck2Capacity = (truck2WeightCapacityPercent + truck2WeightVolumePercent) / 2;

	return truck2Capacity > truck1Capacity;
}

struct Route getDiversionPath(const struct Route* selectedRoute, struct Point dest)
{
	struct Map baseMap = populateMap();

	//TODO: investigate practical closest point when there is a building in-between
	int closestPointIndex = getClosestPoint(selectedRoute, dest);
	struct Point closestPoint = selectedRoute->points[closestPointIndex];

	struct Map routeMap = addRoute(&baseMap, selectedRoute);
	struct Route diversionPath = shortestPath(&routeMap, closestPoint, dest);	//BUG: This line changes selectedRoute, find and fix

	//add destination point to the route too
	addPtToRoute(&diversionPath, dest);
	return diversionPath;
}

struct Truck* getDeliveryTruck(struct Truck* trucks, const int weight, const double size, const char destinationName[])
{
	struct Truck* selectedTruck = { 0 };

	if (isValidPackage(weight, size) && isValidDestinationName(destinationName))
	{
		//2. convert destination name to a point(row,col)
		struct Point dest = convertDestinationNametoPoint(destinationName);
		//printf("destPoint %d, %d", dest.row, dest.col);

		//3. initialize the package
		struct Package pkg = { weight, size, dest };

		//5. find out which trucks has capacity to load the package
		//int numberOfTrucks = sizeof(trucks) / sizeof(trucks[0]);
		int* truckIndxs = getTrucksWithCapacity(trucks, MAX_NUMBER_OF_TRUCKS, pkg);	//related index will have 1 value if has capacity

		//6. Loop through the indexes and find which candidate truck has shortest distance
		int shortestDistance = 99999;
		//Truck* selectedTruck = NULL;

		//int totalPackageLoaded = 0;
		for (int i = 0; i < MAX_NUMBER_OF_TRUCKS; i++)
		{
			//means this truck has capacity
			if (truckIndxs[i] == 1)
			{
				//get the route for the truck	
				struct Route* routeToFollow;
				routeToFollow = getRouteBasedOnSymbol(trucks[i].truckSymbol);

				//find distance to the destination point from selected route(blue or green or yellow)
				double distance = getDistanceToDestination(routeToFollow, dest);
				if (distance < shortestDistance)
				{
					//current truck has the shortest distance to the destination
					selectedTruck = &trucks[i];
					shortestDistance = distance;
				}
				else if (distance == shortestDistance)
				{
					//seems two truck has equidistance, find which one has better capacity
					int truckIhasBetterCapacity = findBetterCapacityTruck(selectedTruck, &trucks[i]);
					if (truckIhasBetterCapacity)
					{
						selectedTruck = &trucks[i];
					}
				}

			}
		}	// end of for loop

		//7. if the package will be shipped(w/without diversion) or not ship today
		if (selectedTruck == NULL)
		{
			//no route found for this package, will ship tomorrow
		}
		else
		{
			//	printf("truck: %d, ", selectedTruck->truckSymbol);

			if (shortestDistance == 1)
			{
				//	printf("no diversion\n");

			}
			else
			{
				//	printf("divert: ");
				struct Route diversionPath;

				//8. get diversion route
				struct Route* selectedRoute;
				selectedRoute = getRouteBasedOnSymbol(selectedTruck->truckSymbol);
				//diversionPath = getDiversionPath(selectedRoute, dest);
				pkg.divertedRoute = getDiversionPath(selectedRoute, dest);

				//add diversion route information to the package
				//pkg.divertedRoute = &diversionPath;
			}

			//9. update truck info(capacity, add the package)
			if (pkg.divertedRoute.numPoints < MAX_ROUTE)
			{
				selectedTruck->currentWeight += pkg.weight;
				selectedTruck->currentVolume += pkg.size;

				//add the package to the truck
				if (selectedTruck->numberOfPackages < MAXIMUM_PACKAGE_CAPACITY)
				{
					selectedTruck->packages[selectedTruck->numberOfPackages] = pkg;
					selectedTruck->numberOfPackages++;
				}
			}
			else
			{
				//although truck has capacity but route couldn't be found
				selectedTruck = NULL;
			}

		}
	}
	return selectedTruck;
}

void displayHeader()
{
	printf("=================\n");
	printf("Seneca Deliveries\n");
	printf("=================\n\n");
}

void processPackage(const int weight, const double size, const char destinationName[], struct Truck* trucks)
{
	int validInput = 1;

	if (validInput && !isValidPackageWeight(weight))
	{
		validInput = 0;
		printf("Invalid weight (must be 1-1000 Kg.)\n");
	}

	if (validInput && !isValidPackageSize(size))
	{
		validInput = 0;
		printf("Invalid size\n");
	}

	if (validInput && !isValidDestinationName(destinationName))
	{
		validInput = 0;
		printf("Invalid destination\n");
	}

	if (validInput)
	{
		struct Truck* deliveryTruck = getDeliveryTruck(trucks, weight, size, destinationName);

		if (deliveryTruck != NULL)
		{
			printf("Ship on ");
			switch (deliveryTruck->truckSymbol)
			{
				case BLUE:
					printf("BLUE LINE, ");
					break;
				case GREEN:
					printf("GREEN LINE, ");
					break;			
				case YELLOW:
						printf("YELLOW LINE, ");
						break;
			}

			int packageIdx = deliveryTruck->numberOfPackages - 1;
			struct Package pkg = deliveryTruck->packages[packageIdx];
			if (pkg.divertedRoute.numPoints==0)
			{
				printf("no diversion\n");
			}
			else
			{
				printf("divert: ");
				//struct Point* divertedRoute = pkg.divertedRoute;
				//print the route
				for (int i = 0; i < pkg.divertedRoute.numPoints-1; i++)
				{
					//char* destName = convertPointToDestinationName(divertedRoute[i]);
					char* destName = convertPointToDestinationName(pkg.divertedRoute.points[i]);
					printf("%d%c, ", destName[0], destName[1]);
				}
				printf("%s\n", destinationName);

			}
		}
		else
		{
			printf("Ships tomorrow\n");
		}
	}
}
