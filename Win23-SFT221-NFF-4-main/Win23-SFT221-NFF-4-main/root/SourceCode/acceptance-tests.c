#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "mapping.h"
#include "delivery.h"

struct Map baseMap;
struct Route blueRoute;
struct Route greenRoute;
struct Route yellowRoute;
struct Point startPoint = { 0, 0 };
struct Point prevPoint = { -1, -1 };

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

// Acceptance criteria# R001 - package must meet specific sizes
//=========================================================
// 
// test case T001 - verify valid package size
void test1_verify_valid_package_size();

// test case T002 - verify invalid package size
void test2_verify_invalid_package_size();

// Acceptance criteria# R002 - package must meet weight constraints
//==============================================================
// test case T003 - verify valid package weight
void test3_verify_valid_package_weight();

// test case T004 - verify invalid package weight
void test4_verify_invalid_package_weight();


//Acceptance criteria# R003 - package must have a valid destination
//===========================================================
// test case T005 - verify valid package destination name
void test5_verify_valid_package_destination_name();

// test case T006 - verify invalid package destination
void test6_verify_invalid_package_destination_name();

//Acceptance criteria# R004 - package should be pickup by the truck of a route that is closer to the destination
// test case T007 - verify closer route blue truck delivers package
void test7_verify_closer_route_blue_truck_deliver_package();

// test case T008 - verify closer route green truck delivers package
void test8_verify_closer_route_green_truck_deliver_package();

// test case T009 - verify closer route yellow truck delivers package
void test9_verify_closer_route_yellow_truck_deliver_package();

//Acceptance criteria# R005 - package should be pickup by the truck of a route that has better capacity if the distance is same from two trucks
// test case T010 - truck with better capacity will deliver the package
void test10_verify_truck_with_better_capacity_delivers();

//Acceptance criteria# R006 - package should be deliver on next day if no truck has capacity anymore
// test case T011 - no truck has room, deliver on next day
void test11_no_capacity_deliver_next_day();

//Acceptance criteria# R007 - truck should take diversion if destination not near route
// test case T012 - truck should divert from route if destination few blocks away from route
void test12_truck_divert_to_reach_dest();

int main(void)
{
	baseMap = populateMap();
	blueRoute = getBlueRoute();
	greenRoute = getGreenRoute();
	yellowRoute = getYellowRoute();

	printf("Acceptance criteria# R001 - package must meet specific sizes\n");
	printf("=========================================================\n");
	// test case T001 - verify valid package size
	test1_verify_valid_package_size();

	// test case T002 - verify invalid package size
	test2_verify_invalid_package_size();

	printf("\nAcceptance criteria# R002 - package must meet weight constraints\n");
	printf("=========================================================\n");
	// test case T003 - verify valid package weight
	test3_verify_valid_package_weight();

	// test case T004 - verify invalid package weight
	test4_verify_invalid_package_weight();

	printf("\nAcceptance criteria# R003 - package must have a valid destination\n");
	printf("=========================================================\n");
	// test case T005 - verify valid package destination name
	test5_verify_valid_package_destination_name();

	// test case T006 - verify invalid package destination
	test6_verify_invalid_package_destination_name();

	//Acceptance criteria# R004 - package should be pickup by the truck of a route that is closer to the destination

	printf("\nAcceptance criteria# R004 - package should be deliver by the truck of a route that is closer to the destination\n");
	printf("=========================================================\n");
	// test case T007 - verify closer route blue truck delivers package
	test7_verify_closer_route_blue_truck_deliver_package();	
	
	// test case T008 - verify closer route green truck delivers package
	test8_verify_closer_route_green_truck_deliver_package();	
	
	// test case T009 - verify closer route yellow truck delivers package
	test9_verify_closer_route_yellow_truck_deliver_package();


	printf("\nAcceptance criteria# R005 - package should be pickup by the truck of a route that has better capacity if the distance is same from two trucks\n");
	printf("=========================================================\n");
	// test case T010 - truck with better capacity will deliver the package
	test10_verify_truck_with_better_capacity_delivers();	
	

	printf("\nAcceptance criteria# R006 - package should be deliver on next day if no truck has capacity anymore\n");
	printf("=========================================================\n");
	// test case T011 - no truck has room, deliver on next day
	test11_no_capacity_deliver_next_day();
	
	printf("\nAcceptance criteria# R007 - truck should take diversion if destination not near route\n");
	printf("=========================================================\n");
	// test case T012 - truck should divert from route if destination few blocks away from route
	test12_truck_divert_to_reach_dest();


	return 0;
}

// test case T001 - verify valid package size
void test1_verify_valid_package_size()
{
	printf("test1_verify_valid_package_size >> ");

	int result1 = isValidPackageSize(.25);
	int result2 = isValidPackageSize(.5);
	int result3 = isValidPackageSize(1);
	if (result1 && result2 && result3)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}

}

// test case T002 - verify invalid package size
void test2_verify_invalid_package_size()
{
	printf("test2_verify_invalid_package_size >> ");

	int result1 = isValidPackageSize(-1);
	int result2 = isValidPackageSize(0);
	int result3 = isValidPackageSize(2);
	if (!result1 && !result2 && !result3)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}

}

// test case T003 - verify valid package weight
void test3_verify_valid_package_weight()
{
	printf("test3_verify_valid_package_weight >> ");

	int result1 = isValidPackageWeight(20);
	int result2 = isValidPackageWeight(100);
	int result3 = isValidPackageWeight(500);
	if (result1 && result2 && result3)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}

}

// test case T004 - verify invalid package weight
void test4_verify_invalid_package_weight()
{
	printf("test4_verify_invalid_package_weight >> ");

	int result1 = isValidPackageWeight(-1);
	int result2 = isValidPackageWeight(0);
	int result3 = isValidPackageWeight(MAX_WEIGHT_CAPACITY+1);
	if (!result1 && !result2 && !result3)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}
}


// test case T005 - verify valid package destination name
void test5_verify_valid_package_destination_name()
{
	printf("test5_verify_valid_package_destination_name >> ");

	char destinationName[] = "8y";
	char expectedRow = 7;
	char expectedCol = 24;
	struct Point dest = convertDestinationNametoPoint(destinationName);

	if (dest.col!= -1 && dest.row != -1)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}

}


// test case T006 - verify invalid package destination
void test6_verify_invalid_package_destination_name()
{
	printf("test6_verify_invalid_package_destination_name >> ");

	char destinationName[] = "30B";
	char expectedRow = -1;
	char expectedCol = -1;
	struct Point dest = convertDestinationNametoPoint(destinationName);

	if (dest.col == -1 && dest.row == -1)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");
	}
}


// test case T007 - verify closer route blue truck delivers package
void test7_verify_closer_route_blue_truck_deliver_package()
{
	printf("test7_verify_closer_route_blue_truck_deliver_package >> ");

	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "16Y";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify BLUE delivers the package as destination is closer to blue route
	if (selectedTruck != NULL && selectedTruck->truckSymbol == BLUE)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}

// test case T008 - verify closer route green truck delivers package
void test8_verify_closer_route_green_truck_deliver_package()
{
	printf("test8_verify_closer_route_green_truck_deliver_package >> ");

	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "9W";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify GREEN delivers the package as destination is closer to green route
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}


// test case T009 - verify closer route yellow truck delivers package
void test9_verify_closer_route_yellow_truck_deliver_package()
{
	printf("test9_verify_closer_route_yellow_truck_deliver_package >> ");

	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "22L";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify YELLOW delivers the package as destination is closer to blue route
	if (selectedTruck != NULL && selectedTruck->truckSymbol == YELLOW)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}



// test case T010 - truck with better capacity will deliver the package
void test10_verify_truck_with_better_capacity_delivers()
{
	printf("test10_verify_truck_with_better_capacity_delivers >> ");

	trucks[0].currentWeight = 500;
	trucks[0].currentVolume = 10;

	trucks[1].currentWeight = 500;
	trucks[1].currentVolume = 2;

	trucks[2].currentWeight = 500;
	trucks[2].currentVolume = 4;
	
	int weight = 200;
	double size = 1;
	char destinationName[] = "19N";
	
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify YELLOW truck delivers the package as it has better capacity although
	//distance to destination is same from YELLOW and BLUE TRUCK
	if (selectedTruck != NULL && selectedTruck->truckSymbol == YELLOW)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}


// test case T011 - no truck has room, deliver on next day
void test11_no_capacity_deliver_next_day()
{
	printf("test11_no_capacity_deliver_next_day >> ");

	trucks[0].currentWeight = 500;
	trucks[0].currentVolume = 10;

	trucks[1].currentWeight = 500;
	trucks[1].currentVolume = 2;

	trucks[2].currentWeight = 500;
	trucks[2].currentVolume = 4;
	int weight = 600;
	double size = 1;
	char destinationName[] = "19N";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//no truck has room, deliver tomorrow
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}


// test case T012 - truck should divert from route if destination few blocks away from route
void test12_truck_divert_to_reach_dest()
{
	printf("test12_truck_divert_to_reach_dest >> ");

	trucks[0].currentWeight = 100;
	trucks[0].currentVolume = 10;

	trucks[1].currentWeight = 200;
	trucks[1].currentVolume = 2;

	trucks[2].currentWeight = 50;
	trucks[2].currentVolume = 3;
	int weight = 100;
	double size = 1;
	char destinationName[] = "3V";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//GREEN truck is near to the destination but few blocks away, it must divert from route
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN && lastPkg.divertedRoute.numPoints > 0)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("FAILED!\n");

	}

}




