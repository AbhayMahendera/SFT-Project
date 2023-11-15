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

// test case 1 - blue truck delivery without diversion
void test1_blue_truck_delivery_no_diversion();

// test case 2 - blue truck delivery with diversion
void test2_blue_truck_delivery_with_diversion();

// test case 3 - green truck delivery without diversion
void test3_green_truck_delivery_no_diversion();

// test case 4 - green truck delivery with diversion
void test4_green_truck_delivery_with_diversion();

// test case 5 - yellow truck delivery without diversion
void test5_yellow_truck_delivery_no_diversion();

// test case 6 - yellow truck delivery with diversion
void test6_yellow_truck_delivery_with_diversion();

//test case 7 - no truck to delivery the package as no capacity
void test7_no_truck_for_delivery();

//test case 8 - green truck & verify diversion route 
void test8_green_truck_delivery_verify_diversion_route();

//test case 9 - deny package as invalid weight 
void test9_deny_package_invalid_weight();

//test case 10 - deny package as invalid volume 
void test10_deny_package_invalid_volume();

//test case 11 - deny package as invalid destination 
void test11_deny_package_invalid_destination();

//test case 12 - truck takes shortest route 
void test12_truck_takes_shortest_route();

//test case 13 - better capacity truck takes the package where destination has same distance from two route
void test13_better_capacity_truck_delivers();

//test case 14 - truck stucks, unreachable destination 
void test14_truck_stucks_destination_unreachable();

int passed = 0;
int failed = 0;

int main(void)
{
	baseMap = populateMap();
	blueRoute = getBlueRoute();
	greenRoute = getGreenRoute();
	yellowRoute = getYellowRoute();

	printf("INTEGRATION TEST CASES\n");
	printf("=====================================================\n");

	// test case 1 - blue truck delivery without diversion
	test1_blue_truck_delivery_no_diversion();

	// test case 2 - blue truck delivery with diversion
	test2_blue_truck_delivery_with_diversion();

	// test case 3 - green truck delivery without diversion
	test3_green_truck_delivery_no_diversion();

	// test case 4 - green truck delivery with diversion
	test4_green_truck_delivery_with_diversion();

	// test case 5 - yellow truck delivery without diversion
	test5_yellow_truck_delivery_no_diversion();

	// test case 6 - yellow truck delivery with diversion
	test6_yellow_truck_delivery_with_diversion();

	//test case 7 - no truck to delivery the package as no capacity
	test7_no_truck_for_delivery();

	//test case 8 - green truck & verify diversion route 
	test8_green_truck_delivery_verify_diversion_route();

	//test case 9 - deny package as invalid weight 
	test9_deny_package_invalid_weight();

	//test case 10 - deny package as invalid volume 
	test10_deny_package_invalid_volume();

	//test case 11 - deny package as invalid destination 
	test11_deny_package_invalid_destination();

	//test case 12 - truck takes shortest route 
	test12_truck_takes_shortest_route();

	//test case 13 - better capacity truck takes the package where destination has same distance from two route
	test13_better_capacity_truck_delivers();

	//test case 14 - truck stucks, unreachable destination 
	test14_truck_stucks_destination_unreachable();

	printf("\bTOTAL test cases: %d\n", passed+failed);
	printf("Passed test cases: %d\n", passed);
	printf("Failed test cases: %d\n", failed);
	return 0;
}


// test case 1 - blue truck delivery without diversion
void test1_blue_truck_delivery_no_diversion()
{
	printf("Test 1: test1_blue_truck_delivery_no_diversion >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;

	int weight = 20;
	double size = .5;
	char destinationName[] = "12l";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify BLUE truck got selected for delivery
	//verify no diversion
	//verify current weight
	//verify current volume capacity
	if (selectedTruck != NULL && selectedTruck->truckSymbol == BLUE && selectedTruck->currentWeight == 20 && selectedTruck->currentVolume==.5)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


// test case 2 - blue truck delivery with diversion
void test2_blue_truck_delivery_with_diversion()
{
	printf("Test 2: test2_blue_truck_delivery_with_diversion >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "12N";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify BLUE truck got selected for delivery
	//verify the diversion path
	//verify current weight
	//verify current volume capacity
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	if (selectedTruck != NULL && selectedTruck->truckSymbol == BLUE && lastPkg.divertedRoute.numPoints>0)
	{	
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

// test case 3 - green truck delivery without diversion
void test3_green_truck_delivery_no_diversion()
{
	printf("Test 3: test3_green_truck_delivery_no_diversion >> ");
	trucks[0].currentWeight = 700;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 1;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;

	int weight = 200;
	double size = 1;
	char destinationName[] = "2U";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify GREEN truck got selected for delivery
	//verify no diversion
	//verify current weight
	//verify current volume capacity
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN && selectedTruck->currentWeight == 200 && selectedTruck->currentVolume == 2)
	{
		printf("PASSED\n");
		passed++;

	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


// test case 4 - green truck delivery with diversion
void test4_green_truck_delivery_with_diversion()
{
	printf("Test 4: test4_green_truck_delivery_with_diversion >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "12T";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify GREEN truck got selected for delivery
	//verify the diversion path
	//verify current weight
	//verify current volume capacity
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN && lastPkg.divertedRoute.numPoints ==3)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

// test case 5 - yellow truck delivery without diversion
void test5_yellow_truck_delivery_no_diversion()
{
	printf("Test 5: test5_yellow_truck_delivery_no_diversion >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;

	int weight = 200;
	double size = 1;
	char destinationName[] = "19G";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify YELLOW truck got selected for delivery
	//verify no diversion
	//verify current weight
	//verify YELLOW truck got selected for delivery
	//verify current volume capacity
	if (selectedTruck != NULL && selectedTruck->truckSymbol == YELLOW && selectedTruck->currentWeight == 200 && selectedTruck->currentVolume == 1)
	{
		printf("PASSED\n");
		passed++;

	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


// test case 6 - yellow truck delivery with diversion
void test6_yellow_truck_delivery_with_diversion()
{
	printf("Test 6: test6_yellow_truck_delivery_with_diversion >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 100;
	double size = .5;
	char destinationName[] = "25K";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify the diversion path
	//verify current weight
	//verify current volume capacity
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	if (selectedTruck != NULL && selectedTruck->truckSymbol == YELLOW && lastPkg.divertedRoute.numPoints>0)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}
}

//test case 7 - no truck to delivery the package as no capacity
void test7_no_truck_for_delivery()
{
	printf("Test 7: test7_no_truck_for_delivery >> ");

	trucks[0].currentWeight = 800;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 36;

	trucks[2].currentWeight = 600;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "12l";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify selectedTruck is null
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
		passed++;

	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

//test case 8 - green truck & verify diversion route 
void test8_green_truck_delivery_verify_diversion_route()
{
	printf("Test 8: test8_green_truck_delivery_verify_diversion_route >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 200;
	double size = .5;
	char destinationName[] = "12W";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify GREEN truck got selected for delivery
	//verify the diversion path
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	struct Route deliveryRoute = lastPkg.divertedRoute;
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN && deliveryRoute.numPoints == 3 && deliveryRoute.points[0].row == 9 && deliveryRoute.points[0].col == 22 && deliveryRoute.points[1].row == 10 && deliveryRoute.points[1].col == 22 && deliveryRoute.points[2].row == 11 && deliveryRoute.points[2].col == 22)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

//test case 9 - deny package as invalid weight 
void test9_deny_package_invalid_weight()
{
	printf("Test 9: test9_deny_package_invalid_weight >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 1200;
	double size = .5;
	char destinationName[] = "12W";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	// no truck takes the package as package weight criteria doesnt meet
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

//test case 10 - deny package as invalid volume 
void test10_deny_package_invalid_volume()
{
	printf("Test 10: test10_deny_package_invalid_volume >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 100;
	double size = 2;
	char destinationName[] = "12W";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	// no truck takes the package as package volume criteria doesnt meet
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


//test case 11 - deny package as invalid destination 
void test11_deny_package_invalid_destination()
{
	printf("Test 11: test11_deny_package_invalid_destination >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 100;
	double size = 1;
	char destinationName[] = "27A";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	// no truck takes the package as package destination criteria doesnt meet
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


//test case 12 - truck takes shortest route 
void test12_truck_takes_shortest_route()
{
	printf("Test 12: test12_truck_takes_shortest_route >> ");
	trucks[0].currentWeight = 0;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 0;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 0;
	trucks[2].currentVolume = 0;
	int weight = 500;
	double size = 1;
	char destinationName[] = "8Y";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify selected truck takes the shortest route
	struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
	if (selectedTruck != NULL && selectedTruck->truckSymbol == GREEN && lastPkg.divertedRoute.numPoints == 7)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


//test case 13 - better capacity truck takes the package where destination has same distance from two route
void test13_better_capacity_truck_delivers()
{
	printf("Test 13: test13_better_capacity_truck_delivers >> ");
	trucks[0].currentWeight = 500;
	trucks[0].currentVolume = 2;

	trucks[1].currentWeight = 900;
	trucks[1].currentVolume = 2;

	trucks[2].currentWeight = 400;
	trucks[2].currentVolume = 1;
	int weight = 100;
	double size = 1;
	char destinationName[] = "19N";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	//verify YELLOW truck got selected for delivery as this has better capacity than BLUE although YELLOW and BLUE both truck has same distance to the destination

	if (selectedTruck != NULL && selectedTruck->truckSymbol == YELLOW)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}

//test case 14 - truck stucks, unreachable destination 
void test14_truck_stucks_destination_unreachable()
{
	printf("Test 14: test14_truck_stucks_destination_unreachable >> ");
	trucks[0].currentWeight = 100;
	trucks[0].currentVolume = 0;

	trucks[1].currentWeight = 800;
	trucks[1].currentVolume = 0;

	trucks[2].currentWeight = 200;
	trucks[2].currentVolume = 0;
	int weight = 300;
	double size = 1;
	char destinationName[] = "8Z";
	struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

	// no truck takes the package as package destination is unreachable, truck stuck
	if (selectedTruck == NULL)
	{
		printf("PASSED\n");
		passed++;
	}
	else
	{
		printf("FAILED!\n");
		failed++;
	}

}


