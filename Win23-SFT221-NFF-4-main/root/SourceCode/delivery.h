#ifndef DELIVERY_H
#define DELIVERY_H
#define MAX_NUMBER_OF_TRUCKS 3
#define MAX_WEIGHT_CAPACITY 1000	// maximum weight capacity of a truck in kilograms
#define MAX_VOLUME_CAPACITY 36		// maximum volume capacity of a truck in cubic meters
#define MAXIMUM_PACKAGE_CAPACITY 200	//maximum number of packages that can be added in a truck, only for allocating memory

/**
* A package will hold weight, size and destination of that package
*
* weight - weight of the package in kilograms
* size - size of the package in cubic meters
* destination - destination of the package where it needs to be delivered
* truck - pointer of the truck in which this package will be loaded, if there is no
* available truck, the value will be null
* divertedRoute - An array of type Point which will keep the diverted route of the
* package if diverted, otherwise this can be null
*/
struct Package
{
	int weight;
	double size;
	struct Point destination;
	//struct Point* divertedRoute;
	struct Route divertedRoute;
};

/**
* A truck struct to hold data about truck
*
* truckSymbol - a unique identifier for the truck, Y = Yellow, B = Blue, G = Green
* currentWeight - the current weight of loaded boxes in kilograms
* currentVolume - the current volume of loaded boxes in cubic meters
* packages - list of packages that this truck will deliver
* numberOfPackages - number of packages this truck will deliver
*/
struct Truck
{
	char truckSymbol;
	int currentWeight;
	double currentVolume;
	struct Package packages[MAXIMUM_PACKAGE_CAPACITY];	// allocate some memory
	int numberOfPackages;
};

/**
* This function will validate a package weight before place to a truck
* weight - weight of the package in kg
* returns 1 if package is valid otherwise 0
*/
int isValidPackageWeight(int weight);

/**
* This function will validate a package size before place to a truck
* size - size of the package in cubic meter
* returns 1 if package is valid otherwise 0
*/
int isValidPackageSize(double size);

/**
* This function will validate a package before place to a truck
* weight - weight of the package in kg
* size - size of the package in cubic meter
* returns 1 if package is valid otherwise 0
*/
int isValidPackage(int weight, double size);

/**
* This function will validate if destination is correct
*
* Return Destination Point if input is valid, otherwise Point will be -1,-1
*/
struct Point convertDestinationNametoPoint(const char destName[]);

/**
* This function will convert a point to readable destination name
* pt - point
*
* returns array of character of destination name. for example: 8Y
*/
char* convertPointToDestinationName(const struct Point pt);

/**
* This function check if destination name is valid or not
* 
* returns 1 if destination name is valid
*/
int isValidDestinationName(const char destinationName[]);

/**
* This function is to verify if the truck reach destination.
* Reached at destination will be consider when the truck is just
* beside the building, that means if the euclidian distance is 1.00
* p1 - point position where the truck is
* p2 - point position of the destination
*
* returns 1 if true, otherwise 0
**/
int reachedDestination(const struct Point p1, const struct Point p2);

/**
* This function will returns an int array of correspondence truck index with value 1 if has capacity, 0 otherwise
*
* trucks[] - list of trucks that will be checked if has capacity
* numberOfTrucks - size of the trucks array
* pkg - package info of type Package that requires to ship
*
* returns an int array of correspondence truck index with value 1 if has capacity, 0 otherwise
*/
int* getTrucksWithCapacity(struct Truck trucks[], int numberOfTrucks, struct Package pkg);

/**
* This function calculate distance from a route to destination
*
* routeToFollow - The route to from where the distance will be calcualted
* dest - destination Point
*
* returns eucladian distance
*/
double getDistanceToDestination(struct Route* routeToFollow, struct Point dest);

/***
* Return a route(BLUE, GREEN, YELLOW) based on symbol
*/
struct Route* getRouteBasedOnSymbol(char symbol);

/**
* Find which truck has better capacity
*
* return 1 if truck2 has better capacity
*/
int findBetterCapacityTruck(const struct Truck* truck1, const struct Truck* truck2);


/**
* Return the route the truck will follow to deliver the package
*/
struct Route getDiversionPath(struct Route* markedRoute, struct Point dest);

/**
* Return the delivery truck that will deliver the package, Also
* update the capacity of the truck
*/
struct Truck* getDeliveryTruck(struct Truck* trucks, const int weight, const double size, const char destinationName[]);

/**
* Helper function to convert a character to correspondent index
*/
int findAlphaIndex(char c);


void displayHeader();

void processPackage(const int weight, const double size, const char destinationName[], struct Truck* trucks);
#endif

