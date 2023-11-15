#include "pch.h"
#include "mapping_r.h"
#include "delivery_r.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(PackageTest)
	{

	public:
		//TEST CASES FOR PACKAGE
		TEST_METHOD(PackageTest1_Invalid_Weight)
		{

			int weight = -1;
			bool expected = false;
			bool result = isValidPackageWeight(weight);
			Assert::AreEqual(expected, result);
		
		}
		
		TEST_METHOD(PackageTest2_Weight_TOO_MUCH)
		{
			int weight = 1100;
			bool expected = false;
			bool result = isValidPackageWeight(weight);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(PackageTest3_Weight_ZERO)
		{
			int weight = 0;
			bool expected = false;
			bool result = isValidPackageWeight(weight);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(PackageTest4_Weight_VALID)
		{
			int weight = 100;
			bool expected = true;
			bool result = isValidPackageWeight(weight);
			Assert::AreEqual(expected, result);
		}
		
		TEST_METHOD(PackageTest5_Size_Invalid)
		{
			double size = -1;
			bool expected = false;
			bool result = isValidPackageSize(size);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(PackageTest6_Size_Valid)
		{
			double size = .5;
			bool expected = true;
			bool result = isValidPackageSize(size);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(PackageTest7_Weight_Size_inValid)
		{
			int weight = 0;
			double size = .5;
			bool expected = false;
			bool result = isValidPackage(weight, size);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(PackageTest8_Weight_Size_Valid)
		{
			int weight = 100;
			double size = .5;
			bool expected = true;
			bool result = isValidPackage(weight, size);
			Assert::AreEqual(expected, result);
		}

	};

	TEST_CLASS(DestinationTest){
	public:
		//DESTINATION NAME UPDATE
		TEST_METHOD(DestinationTest1_valid_Destination_Name)
		{
			char destinationName[] = "8y";
			char expectedRow = 7;
			char expectedCol = 24;
			struct Point dest = convertDestinationNametoPoint(destinationName);
			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(DestinationTest2_INVALID_Destination_Name)
		{
			char destinationName[] = "10z";
			char expectedRow = -1;
			char expectedCol = -1;
			struct Point dest = convertDestinationNametoPoint(destinationName);
			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(DestinationTest3_INVALID_Destination_Name)
		{
			char destinationName[] = "30B";
			char expectedRow = -1;
			char expectedCol = -1;
			struct Point dest = convertDestinationNametoPoint(destinationName);
			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(DestinationTest4_valid_Destination_Name)
		{
			char destinationName[] = "7B";
			char expectedRow = 6;
			char expectedCol = 1;
			struct Point dest = convertDestinationNametoPoint(destinationName);
			Assert::AreEqual(expectedRow, dest.row);
			Assert::AreEqual(expectedCol, dest.col);
		}

		TEST_METHOD(DestinationTest5_valid_Destination_Point)
		{
			Point pt = { 6,1 };
			char expected[3] = { 7,'B' };
			char* destName = convertPointToDestinationName(pt);
			Assert::AreEqual(expected, destName);
		}
		
		TEST_METHOD(DestinationTest6_INVALID_Destination_Point)
		{

			Point pt = { 26,1 };
			char* destName = convertPointToDestinationName(pt);
			Assert::AreEqual('\0', destName[0]);
			Assert::AreEqual('\0', destName[1]);
		}


	};

	TEST_CLASS(TruckTest)
	{
	public:

		TEST_METHOD(TruckTest1_GREEN_YELLOW_Truck_validCapacity)
		{
			int weight = 200;
			double size = 1;
			struct Point dest = { 7, 24 };
			struct Package pkg = { weight, size, dest };
			Truck trucks[3] = {
								{
									BLUE, 1000,0, NULL
								},
								{
									GREEN, 0,0, NULL
								},
								{
									YELLOW, 700,0, NULL
								}
							  };
			
			int* truckIndxs = getTrucksWithCapacity(trucks, 3, pkg);

			// method getTrucksWithCapacity
			Assert::IsTrue(truckIndxs[0]==0);	//no capacity on blue truck
			Assert::IsTrue(truckIndxs[1]==1);
			Assert::IsTrue(truckIndxs[1]==1);
		}
		
		TEST_METHOD(TruckTest1_BLUE_TRUCK_betterCapacity)
		{
			Truck trucks[3] = {
					{
						BLUE, 200,0, NULL
					},
					{
						GREEN, 500,0, NULL
					},
					{
						YELLOW, 700,0, NULL
					}
			};

			int truckIhasBetterCapacity = findBetterCapacityTruck(&trucks[0], &trucks[1]);

			Assert::AreEqual(0, truckIhasBetterCapacity);
		}
	};

	TEST_CLASS(DestinationDistanceTest)
	{
	public:
		//DESTINATION TESTS
		TEST_METHOD(DestinationDistanceTest1_)
		{
			// TODO implement tests here
			// method: getDistanceToDestination
			Assert::IsTrue(true);
		}
		
		TEST_METHOD(DestinationDistanceTest2_)
		{
			// TODO implement tests here
			// method: reachedDestination
			Assert::IsTrue(true);
		}
	};
	
	TEST_CLASS(DiversionPathTest)
	{
	public:

		TEST_METHOD(DiversionPathTest1_)
		{
			// TODO implement tests here
			// method: getDiversionPath
			Assert::IsTrue(true);
		}
		
	};

}
