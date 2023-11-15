
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

#include "mapping.h"

#include "math.h"


//F1- POPULATEMAP()
// To create white box test cases for the populateMap() function, we need to analyze the code and identify the different code paths and execution branches. Based on this analysis, we can create test cases that exercise these different paths and ensure that the function works correctly under all possible scenarios. Here are four possible white box test cases for this function:

// Test case 1: All cells are zero


struct Map m = populateMap();
for(int i = 0; i < 12; i++){
  for(int j = 0; j < 25; j++){
    assert(m.cells[i][j] == 0);
  }
}
// This test case covers the scenario where all cells in the map are initialized to zero. We iterate over all cells in the map and verify that their values are zero.
// Test case 2: Some cells are one

struct Map m = populateMap();
for(int i = 0; i < 12; i++){
  for(int j = 0; j < 25; j++){
    if(m.cells[i][j] == 1){
      assert((i == 0 && (j == 4 || j == 5)) ||
             (i == 1 && (j == 1 || j == 2 || j == 4 || j == 5 || j == 16 || j == 17)) ||
             (i == 2 && (j == 1 || j == 2 || j == 4 || j == 5 || j == 9 || j == 10 || j == 16 || j == 17)) ||
             (i == 6 && (j == 0 || j == 1 || j == 4 || j == 5 || j == 8 || j == 16)) ||
             (i == 7 && (j == 0 || j == 1 || j == 4 || j == 5 || j == 10 || j == 16 || j == 17 || j == 18)) ||
             (i == 8 && (j == 7 || j == 8 || j == 12 || j == 16 || j == 17 || j == 18)) ||
             (i == 11 && (j == 2 || j == 3 || j == 4 || j == 5 || j == 7 || j == 8 || j == 9 || j == 11 || j == 13 || j == 14 || j == 15 || j == 16 || j == 17 || j == 18 || j == 19 || j == 20 || j == 21 || j == 23 || j == 24)));
    }
  }
}

// This test case covers the scenario where some cells in the map are initialized to one. We iterate over all cells in the map, and if we find a cell with value one, we verify that it belongs to one of the expected positions based on the hardcoded binary map in the populateMap() function.

// Test case 3: All cells are one
struct Map m = populateMap();
for(int i = 0; i < 12; i++){
  for(int j = 0; j < 25; j++){
    assert(m.cells[i][j] == 1);
  }
}

// Case 4: Testing the function for a map with all elements set to zero


void test_populateMap_case4(void) {
    struct Map expected = {{{0}}};
    struct Map result = populateMap();
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 25; j++) {
            assert(expected.arr[i][j] == result.arr[i][j]);
        }
    }
    printf("Test case 4 passed.\n");
}
Note: This test case assumes that the map returned by populateMap() is always a 12x25 grid. If the size of the grid changes, the loop boundaries need to be adjusted accordingly.

  
//F2- printMap(const struct Map* map, const int base1, const int alphaCols)

  
// Test case 1: Print an empty map
struct Map emptyMap = {.size = 0, .data = NULL};
printMap(&emptyMap, 1, 3); // Expected output: nothing printed



// Test case 2: Print a small map
int smallMapData[4] = {0, 1, 2, 3};
struct Map smallMap = {.size = 2, .data = smallMapData};
printMap(&smallMap, 1, 2); 


/* Expected output:
    1A 1B
   ------
1 |  0  1
2 |  2  3
*/

// Test case 3: Print a larger map
int largeMapData[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
struct Map largeMap = {.size = 4, .data = largeMapData};
printMap(&largeMap, 1, 4);
/* Expected output:
    1A 1B 1C 1D
   ------------
1 |  0  1  2  3
2 |  4  5  6  7
3 |  8  9 10 11
4 | 12 13 14 15
*/

//F3- Route getBlueRoute()
// Test case 1: Test for a small map
int smallMapData[4] = {0, 1, 2, 3};
struct Map smallMap = {.size = 2, .data = smallMapData};
struct Route blueRoute = getBlueRoute(&smallMap);
// Expected output: blueRoute.steps[0] should be {1, 1} and blueRoute.numSteps should be 1

// Test case 2: Test for a larger map
int largeMapData[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
struct Map largeMap = {.size = 4, .data = largeMapData};
struct Route blueRoute = getBlueRoute(&largeMap);
// Expected output: blueRoute should have multiple steps and cover a significant portion of the map

//F4- Route getGreenRoute()
// Test Case: Test with a valid map and start point
// Input: Valid map with multiple nodes and edges, and valid start point
// Expected Output: A Route struct with the correct path and distance

// Create a map with multiple nodes and edges
struct Map testMap = createMap(5);

// Add edges to the map
addEdge(&testMap, 1, 2, 10);
addEdge(&testMap, 2, 3, 15);
addEdge(&testMap, 1, 4, 20);
addEdge(&testMap, 4, 3, 25);
addEdge(&testMap, 3, 5, 30);

// Set the start and end points
int start = 1;
int end = 5;

// Get the green route
Route result = getGreenRoute(&testMap, start, end);

// Verify that the result is correct
assert(result.distance == 60);
assert(result.path[0] == 1);
assert(result.path[1] == 4);
assert(result.path[2] == 3);
assert(result.path[3] == 5);


// Test Case: Test with a valid map and end point
// Input: Valid map with multiple nodes and edges, and valid end point
// Expected Output: A Route struct with the correct path and distance

// Create a map with multiple nodes and edges
struct Map testMap = createMap(5);

// Add edges to the map
addEdge(&testMap, 1, 2, 10);
addEdge(&testMap, 2, 3, 15);
addEdge(&testMap, 1, 4, 20);
addEdge(&testMap, 4, 3, 25);
addEdge(&testMap, 3, 5, 30);

// Set the start and end points
int start = 1;
int end = 5;

// Get the green route
Route result = getGreenRoute(&testMap, start, end);

// Verify that the result is correct
assert(result.distance == 60);
assert(result.path[0] == 1);
assert(result.path[1] == 4);
assert(result.path[2] == 3);
assert(result.path[3] == 5);

// Test Case: Test with an invalid end point
// Input: Valid map with multiple nodes and edges, and invalid end point
// Expected Output: A Route struct with NULL path and 0 distance



// Create a map with multiple nodes and edges
struct Map testMap = createMap(5);

// Add edges to the map
addEdge(&testMap, 1, 2, 10);
addEdge(&testMap, 2, 3, 15);
addEdge(&testMap, 1, 4, 20);
addEdge(&testMap, 4, 3, 25);
addEdge(&testMap, 3, 5, 30);

// Set the start and end points
int start = 1;
int end = 6;

// Get the green route
Route result = getGreenRoute(&testMap, start, end);

// Verify that the result is correct
assert(result.distance == 0);
assert(result.path == NULL);

//F5- Test cases for getPossibleMoves:
// Test case 1: No possible moves
struct Map map = createMap(3, 3);
struct Point p1 = {1, 1};
struct Point backpath = {2, 2};
struct Route expected = {0, NULL};
struct Route result = getPossibleMoves(&map, p1, backpath);
assert(compareRoutes(expected, result) == true);

// Test case 2: Only one possible move
map.tiles[1][2] = 'X';
struct Point p2 = {1, 1};
struct Route expected2 = {1, (struct Point*)malloc(sizeof(struct Point))};
expected2.path[0] = (struct Point){1, 2};
struct Route result2 = getPossibleMoves(&map, p2, backpath);
assert(compareRoutes(expected2, result2) == true);

// Test case 3: Multiple possible moves
map.tiles[0][1] = 'X';
map.tiles[2][1] = 'X';
struct Point p3 = {1, 1};
struct Route expected3 = {2, (struct Point*)malloc(2*sizeof(struct Point))};
expected3.path[0] = (struct Point){0, 1};
expected3.path[1] = (struct Point){2, 1};
struct Route result3 = getPossibleMoves(&map, p3, backpath);
assert(compareRoutes(expected3, result3) == true);

//F6- Test cases for shortestPath:
// Test case 1: No possible path
struct Map map = createMap(3, 3);
map.tiles[0][1] = 'X';
map.tiles[1][1] = 'X';
map.tiles[2][1] = 'X';
struct Point start = {0, 0};
struct Point dest = {2, 2};
struct Route expected = {0, NULL};
struct Route result = shortestPath(&map, start, dest);
assert(compareRoutes(expected, result) == true);

// Test case 2: Path with a single move
struct Map map2 = createMap(3, 3);
map2.tiles[0][1] = 'X';
map2.tiles[1][1] = 'X';
map2.tiles[2][1] = 'X';
struct Point start2 = {0, 0};
struct Point dest2 = {0, 1};
struct Route expected2 = {1, (struct Point*)malloc(sizeof(struct Point))};
expected2.path[0] = (struct Point){0, 1};
struct Route result2 = shortestPath(&map2, start2, dest2);
assert(compareRoutes(expected2, result2) == true);

//F7- Test cases for getPossibleMoves(struct Route getPossibleMoves(const struct Map* map, const struct Point p1, const struct Point backpath)
// Test Case 1:


struct Map testMap = createMap(5, 5);
addObstacle(&testMap, createPoint(2,2));
addObstacle(&testMap, createPoint(3,2));
addObstacle(&testMap, createPoint(4,2));
struct Point testPoint = createPoint(1,2);
struct Point testBackPath = createPoint(0,2);
struct Route possibleMoves = getPossibleMoves(&testMap, testPoint, testBackPath);
assert(possibleMoves.length == 2);
assert(possibleMoves.steps[0].x == 1 && possibleMoves.steps[0].y == 3);
assert(possibleMoves.steps[1].x == 1 && possibleMoves.steps[1].y == 4);

// Test Case 2:


struct Map testMap = createMap(5, 5);
addObstacle(&testMap, createPoint(2,2));
struct Point testPoint = createPoint(1,2);
struct Point testBackPath = createPoint(0,2);
struct Route possibleMoves = getPossibleMoves(&testMap, testPoint, testBackPath);
assert(possibleMoves.length == 3);
assert(possibleMoves.steps[0].x == 1 && possibleMoves.steps[0].y == 1);
assert(possibleMoves.steps[1].x == 1 && possibleMoves.steps[1].y == 3);
assert(possibleMoves.steps[2].x == 0 && possibleMoves.steps[2].y == 2);
// Test Case 3:


struct Map testMap = createMap(5, 5);
struct Point testPoint = createPoint(1,1);
struct Point testBackPath = createPoint(0,0);
struct Route possibleMoves = getPossibleMoves(&testMap, testPoint, testBackPath);
assert(possibleMoves.length == 2);
assert(possibleMoves.steps[0].x == 1 && possibleMoves.steps[0].y == 0);
assert(possibleMoves.steps[1].x == 2 && possibleMoves.steps[1].y == 1);

//F8- struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest)

//Test Case 1:

// Input map
struct Map map = {
    .width = 5,
    .height = 5,
    .cells = {
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1 }
    }
};

// Start and destination points
struct Point start = { 0, 0 };
struct Point dest = { 4, 4 };

// Expected output
struct Route expectedRoute = {
    .length = 9,
    .points = {
        { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 }, { 2, 2 },
        { 3, 2 }, { 3, 3 }, { 3, 4 }, { 4, 4 }
    }
};

// Actual output
struct Route actualRoute = shortestPath(&map, start, dest);

// Assertion
assert(actualRoute.length == expectedRoute.length);
for (int i = 0; i < actualRoute.length; i++) {
    assert(actualRoute.points[i].x == expectedRoute.points[i].x);
    assert(actualRoute.points[i].y == expectedRoute.points[i].y);
}


//Test Case 2:


// Input map
struct Map map = {
    .width = 4,
    .height = 4,
    .cells = {
        { 1, 0, 0, 1 },
        { 1, 1, 0, 1 },
        { 0, 1, 0, 1 },
        { 1, 1, 1, 1 }
    }
};

// Start and destination points
struct Point start = { 0, 0 };
struct Point dest = { 3, 3 };

// Expected output
struct Route expectedRoute = {
    .length = 7,
    .points = {
        { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 },
        { 2, 2 }, { 2, 3 }, { 3, 3 }
    }
};

// Actual output
struct Route actualRoute = shortestPath(&map, start, dest);

// Assertion
assert(actualRoute.length == expectedRoute.length);
for (int i = 0; i < actualRoute.length; i++) {
    assert(actualRoute.points[i].x == expectedRoute.points[i].x);
    assert(actualRoute.points[i].y == expectedRoute.points[i].y);
}

//f9-getPossibleMoves function
// White box test cases for getPossibleMoves function
TEST(getPossibleMoves, validInput) {
  struct Map map = createMap(5, 5);
  struct Point p1 = {2, 2};
  struct Point backpath = {-1, -1};
  struct Route possibleMoves = getPossibleMoves(&map, p1, backpath);

  EXPECT_EQ(possibleMoves.numPoints, 4);
  EXPECT_EQ(possibleMoves.points[0].x, 2);
  EXPECT_EQ(possibleMoves.points[0].y, 1);
  EXPECT_EQ(possibleMoves.points[1].x, 2);
  EXPECT_EQ(possibleMoves.points[1].y, 3);
  EXPECT_EQ(possibleMoves.points[2].x, 1);
  EXPECT_EQ(possibleMoves.points[2].y, 2);
  EXPECT_EQ(possibleMoves.points[3].x, 3);
  EXPECT_EQ(possibleMoves.points[3].y, 2);
}

TEST(getPossibleMoves, outOfBounds) {
  struct Map map = createMap(5, 5);
  struct Point p1 = {5, 5};
  struct Point backpath = {-1, -1};
  struct Route possibleMoves = getPossibleMoves(&map, p1, backpath);

  EXPECT_EQ(possibleMoves.numPoints, 0);
}

TEST(getPossibleMoves, blockedPath) {
  struct Map map = createMap(5, 5);
  map.cells[2][1] = CELL_BLOCKED;
  struct Point p1 = {2, 2};
  struct Point backpath = {-1, -1};
  struct Route possibleMoves = getPossibleMoves(&map, p1, backpath);

  EXPECT_EQ(possibleMoves.numPoints, 3);
  EXPECT_EQ(possibleMoves.points[0].x, 2);
  EXPECT_EQ(possibleMoves.points[0].y, 3);
  EXPECT_EQ(possibleMoves.points[1].x, 1);
  EXPECT_EQ(possibleMoves.points[1].y, 2);
  EXPECT_EQ(possibleMoves.points[2].x, 3);
  EXPECT_EQ(possibleMoves.points[2].y, 2);
}

//f10- shortestPath function

void test_shortestPath() {
    // Test case 1: Start and dest are the same
    struct Map map1 = {
        .rows = 5,
        .cols = 5,
        .data = {
            "xxxxx",
            "x...x",
            "x...x",
            "x...x",
            "xxxxx"
        }
    };
    struct Point start1 = {1, 1};
    struct Point dest1 = {1, 1};
    struct Route expected1 = { .numPoints = 1, .points = {{1, 1}} };
    struct Route result1 = shortestPath(&map1, start1, dest1);
    assert(result1.numPoints == expected1.numPoints);
    for (int i = 0; i < result1.numPoints; i++) {
        assert(result1.points[i].x == expected1.points[i].x);
        assert(result1.points[i].y == expected1.points[i].y);
    }
    printf("shortestPath test case 1 passed\n");
    
    // Test case 2: No path exists
    struct Map map2 = {
        .rows = 5,
        .cols = 5,
        .data = {
            "xxxxx",
            "x...x",
            "x...x",
            "x...x",
            "xxxxx"
        }
    };
    struct Point start2 = {1, 1};
    struct Point dest2 = {3, 3};
    struct Route expected2 = { .numPoints = 0, .points = {} };
    struct Route result2 = shortestPath(&map2, start2, dest2);
    assert(result2.numPoints == expected2.numPoints);
    printf("shortestPath test case 2 passed\n");
    
    // Test case 3: Path exists
    struct Map map3 = {
        .rows = 5,
        .cols = 5,
        .data = {
            "xxxxx",
            "x...x",
            "x...x",
            "x...x",
            "xxxxx"
        }
    };
    struct Point start3 = {1, 1};
    struct Point dest3 = {3, 3};
    struct Route expected3 = { .numPoints = 5, .points = {{1, 1}, {2, 1}, {2, 2}, {2, 3}, {3, 3}} };
    struct Route result3 = shortestPath(&map3, start3, dest3);
    assert(result3.numPoints == expected3.numPoints);
    for (int i = 0; i < result3.numPoints; i++) {
        assert(result3.points[i].x == expected3.points[i].x);
        assert(result3.points[i].y == expected3.points[i].y);
    }
    printf("shortestPath test case 3 passed\n");
}

//f11- struct Route getPossibleMoves(const struct Map* map, const struct Point p1, const struct Point backpath)
//Test Case 1: Test when p1 is located in the middle of the map


struct Map testMap = {
    .numRows = 5,
    .numCols = 5,
    .squares = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    }
};
struct Point testP1 = {2, 2};
struct Point testBackPath = {0, 0};
struct Route possibleMoves = getPossibleMoves(&testMap, testP1, testBackPath);

assert(possibleMoves.numPoints == 8);
assert(possibleMoves.points[0].row == 1 && possibleMoves.points[0].col == 1);
assert(possibleMoves.points[1].row == 1 && possibleMoves.points[1].col == 2);
assert(possibleMoves.points[2].row == 1 && possibleMoves.points[2].col == 3);
assert(possibleMoves.points[3].row == 2 && possibleMoves.points[3].col == 1);
assert(possibleMoves.points[4].row == 2 && possibleMoves.points[4].col == 3);
assert(possibleMoves.points[5].row == 3 && possibleMoves.points[5].col == 1);
assert(possibleMoves.points[6].row == 3 && possibleMoves.points[6].col == 2);
assert(possibleMoves.points[7].row == 3 && possibleMoves.points[7].col == 3);

//Test Case 2: Test when p1 is located at a corner of the map


struct Map testMap = {
    .numRows = 4,
    .numCols = 4,
    .squares = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 1},
        {0, 0, 1, 0}
    }
};
struct Point testP1 = {0, 2};
struct Point testBackPath = {0, 0};
struct Route possibleMoves = getPossibleMoves(&testMap, testP1, testBackPath);

assert(possibleMoves.numPoints == 3);
assert(possibleMoves.points[0].row == 0 && possibleMoves.points[0].col == 1);
assert(possibleMoves.points[1].row == 1 && possibleMoves.points[1].col == 1);
assert(possibleMoves.points[2].row == 1 && possibleMoves.points[2].col == 2);

//f12-white box test cases for getClosestPoint function

void test_getClosestPoint() {
    struct Route route = {
        .numPoints = 4,
        .points = {
            {0, 0},
            {1, 1},
            {2, 2},
            {3, 3}
        }
    };

    struct Point pt = {2, 0};
    int closestIdx = getClosestPoint(&route, pt);
    assert(closestIdx == 0);

    pt = (struct Point){0, 3};
    closestIdx = getClosestPoint(&route, pt);
    assert(closestIdx == 3);

    pt = (struct Point){1, 2};
    closestIdx = getClosestPoint(&route, pt);
    assert(closestIdx == 1);
}
