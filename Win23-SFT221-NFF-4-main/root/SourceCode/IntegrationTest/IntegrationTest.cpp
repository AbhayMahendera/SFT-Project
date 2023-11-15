#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "delivery_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest
{
	TEST_CLASS(IntegrationTest)
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

		TEST_METHOD(test1_blue_truck_delivery_no_diversion)
		{
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

			////verify BLUE truck got selected for delivery
			////verify no diversion
			////verify current weight
			////verify current volume capacity

			char ExpectedTruckSymbol = 2;
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(20, selectedTruck->currentWeight);
			Assert::AreEqual(.5, selectedTruck->currentVolume);
		}

		TEST_METHOD(test2_blue_truck_delivery_with_diversion)
		{
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

			char ExpectedTruckSymbol = 2;
			struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(true, lastPkg.divertedRoute.numPoints > 0);

		}

		TEST_METHOD(test3_green_truck_delivery_no_diversion)
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
			Assert::AreEqual(200, selectedTruck->currentWeight);
			Assert::AreEqual(2.0, selectedTruck->currentVolume);
		}

		TEST_METHOD(test4_green_truck_delivery_with_diversion)
		{
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

			char ExpectedTruckSymbol = 4;
			struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(true, lastPkg.divertedRoute.numPoints > 0);

		}

		TEST_METHOD(test5_yellow_truck_delivery_no_diversion)
		{
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

			char ExpectedTruckSymbol = 8;
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(200, selectedTruck->currentWeight);
			Assert::AreEqual(1.0, selectedTruck->currentVolume);
		}

		TEST_METHOD(test6_yellow_truck_delivery_with_diversion)
		{
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

			char ExpectedTruckSymbol = 8;
			struct Package lastPkg = selectedTruck->packages[selectedTruck->numberOfPackages - 1];
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(true, lastPkg.divertedRoute.numPoints > 0);

		}

		TEST_METHOD(test7_no_truck_for_delivery)
		{
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

			Assert::IsNull(selectedTruck);
		}

		TEST_METHOD(test8_green_truck_delivery_verify_diversion_route)
		{
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

			char ExpectedTruckSymbol = 4;
			Assert::AreEqual(ExpectedTruckSymbol, selectedTruck->truckSymbol);
			Assert::AreEqual(3, lastPkg.divertedRoute.numPoints);
		}

		TEST_METHOD(test9_deny_package_invalid_weight)
		{
			int weight = 1200;
			double volume = .5;
			int result = isValidPackage(weight, volume);
			Assert::IsFalse(result);
		}		
		
		TEST_METHOD(test10_deny_package_invalid_volume)
		{
			int weight = 500;
			double volume = 2;
			int result = isValidPackage(weight, volume);
			Assert::IsFalse(result);
		}

		TEST_METHOD(test11_deny_package_invalid_destination)
		{
			char destinationName[] = "8Z";
			bool result = isValidDestinationName(destinationName);
			Assert::IsFalse(result);
		}		
		
		TEST_METHOD(test12_truck_takes_shortest_route)
		{
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

			char expectedTruck = 4;
			Assert::AreEqual(expectedTruck, selectedTruck->truckSymbol);
			Assert::AreEqual(7, lastPkg.divertedRoute.numPoints);

		}
		
		TEST_METHOD(test13_better_capacity_truck_delivers)
		{
			trucks[0].currentWeight = 500;
			trucks[0].currentVolume = 2;

			trucks[1].currentWeight = 900;
			trucks[1].currentVolume = 2;

			trucks[2].currentWeight = 400;
			trucks[2].currentVolume = 1;

			struct Truck* truck1 = &trucks[0];
			struct Truck* truck2 = &trucks[1];

			int result = findBetterCapacityTruck(truck1,truck2);

			//truck2 doesnt has better capacity
			Assert::AreEqual(0, result);
		}
		
		TEST_METHOD(test14_truck_stucks_destination_unreachable)
		{
			char destinationName[] = "8Z";
			struct Point invalidDest = { -1,-1 };
			struct Point dest = convertDestinationNametoPoint(destinationName);
			
			//destination is not valid which is unreachable
			Assert::AreEqual(invalidDest.row, dest.row);
			Assert::AreEqual(invalidDest.col, dest.col);
		}

	};

}

