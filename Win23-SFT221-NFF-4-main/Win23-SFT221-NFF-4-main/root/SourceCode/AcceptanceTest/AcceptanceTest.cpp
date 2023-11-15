#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "delivery_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AcceptanceTest
{
	TEST_CLASS(AcceptanceTest)
	{
	public:
		
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

		struct Map baseMap = populateMap();
		struct Route blueRoute = getBlueRoute();
		struct Route greenRoute = getGreenRoute();
		struct Route yellowRoute = getYellowRoute();

		TEST_METHOD(test1_verify_valid_package_size)
		{
			int result1 = isValidPackageSize(.25);
			int result2 = isValidPackageSize(.5);
			int result3 = isValidPackageSize(1);

			Assert::AreEqual(1, result1);
			Assert::AreEqual(1, result2);
			Assert::AreEqual(1, result3);
		}

		TEST_METHOD(test2_verify_invalid_package_size)
		{
			int result1 = isValidPackageSize(-1);
			int result2 = isValidPackageSize(0);
			int result3 = isValidPackageSize(2);

			Assert::AreEqual(0, result1);
			Assert::AreEqual(0, result2);
			Assert::AreEqual(0, result3);
		}

		TEST_METHOD(test3_verify_valid_package_weight)
		{
			int result1 = isValidPackageWeight(20);
			int result2 = isValidPackageWeight(100);
			int result3 = isValidPackageWeight(500);

			Assert::AreEqual(1, result1);
			Assert::AreEqual(1, result2);
			Assert::AreEqual(1, result3);
		}

		TEST_METHOD(test4_verify_invalid_package_weight)
		{
			int result1 = isValidPackageWeight(-1);
			int result2 = isValidPackageWeight(0);
			int result3 = isValidPackageWeight(MAX_WEIGHT_CAPACITY + 1);

			Assert::AreEqual(0, result1);
			Assert::AreEqual(0, result2);
			Assert::AreEqual(0, result3);
		}

		TEST_METHOD(test5_verify_valid_package_destination_name)
		{
			char destinationName[] = "8y";
			char expectedRow = 7;
			char expectedCol = 24;
			struct Point dest = convertDestinationNametoPoint(destinationName);

			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(test6_verify_invalid_package_destination_name)
		{
			char destinationName[] = "30B";
			char expectedRow = -1;
			char expectedCol = -1;
			struct Point dest = convertDestinationNametoPoint(destinationName);

			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(test7_verify_closer_route_blue_truck_deliver_package)
		{
			trucks[0].currentWeight = 0;
			trucks[0].currentVolume = 0;

			trucks[1].currentWeight = 0;
			trucks[1].currentVolume = 0;

			trucks[2].currentWeight = 0;
			trucks[2].currentVolume = 0;
			int weight = 500;
			double size = 1;
			char destinationName[] = "16Y";
			char ExpectedTruckSymbol = 2;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);

		}

		TEST_METHOD(test8_verify_closer_route_green_truck_deliver_package)
		{
			trucks[0].currentWeight = 0;
			trucks[0].currentVolume = 0;

			trucks[1].currentWeight = 0;
			trucks[1].currentVolume = 0;

			trucks[2].currentWeight = 0;
			trucks[2].currentVolume = 0;
			int weight = 500;
			double size = 1;
			char destinationName[] = "9W";
			char ExpectedTruckSymbol = 4;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);

		}

		TEST_METHOD(test9_verify_closer_route_yellow_truck_deliver_package)
		{
			trucks[0].currentWeight = 0;
			trucks[0].currentVolume = 0;

			trucks[1].currentWeight = 0;
			trucks[1].currentVolume = 0;

			trucks[2].currentWeight = 0;
			trucks[2].currentVolume = 0;
			int weight = 500;
			double size = 1;
			char destinationName[] = "22L";
			char ExpectedTruckSymbol = 8;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);

		}

		TEST_METHOD(test10_verify_truck_with_better_capacity_delivers)
		{
			trucks[0].currentWeight = 500;
			trucks[0].currentVolume = 10;

			trucks[1].currentWeight = 500;
			trucks[1].currentVolume = 2;

			trucks[2].currentWeight = 500;
			trucks[2].currentVolume = 4;
			int weight = 200;
			double size = 1;
			char destinationName[] = "19N";
			char ExpectedTruckSymbol = 8;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);
			//verify YELLOW truck delivers the package as it has better capacity although
			//distance to destination is same from YELLOW and BLUE TRUCK

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
		}

		TEST_METHOD(test11_no_capacity_deliver_next_day)
		{
			trucks[0].currentWeight = 500;
			trucks[0].currentVolume = 10;

			trucks[1].currentWeight = 300;
			trucks[1].currentVolume = 2;

			trucks[2].currentWeight = 500;
			trucks[2].currentVolume = 4;
			int weight = 600;
			double size = 1;
			char destinationName[] = "19N";
			char ExpectedTruckSymbol = 4;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
		}

		TEST_METHOD(test12_truck_divert_to_reach_dest)
		{
			trucks[0].currentWeight = 100;
			trucks[0].currentVolume = 10;

			trucks[1].currentWeight = 200;
			trucks[1].currentVolume = 2;

			trucks[2].currentWeight = 50;
			trucks[2].currentVolume = 4;
			int weight = 100;
			double size = 1;
			char destinationName[] = "3V";
			char ExpectedTruckSymbol = 4;
			struct Truck* selectedTruck = getDeliveryTruck(trucks, weight, size, destinationName);

			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
		}
		
		TEST_METHOD(test13_truck_no_divert_to_reach_dest)
		{
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

			char ExpectedTruckSymbol = 4;
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);

			struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
			//no diversion
			Assert::AreEqual(0, lastPkg.divertedRoute.numPoints);

		}
	
	};
}
