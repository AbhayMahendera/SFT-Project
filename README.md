# Seneca Deliveries Project

## Learning Outcomes
- Design and build a solution to a small problem.
- Design testing for the problem.

## Project Description

You have been hired by a local delivery company that operates three different trucks on three distinct routes in your part of the city. The city map is represented as a 25 by 25 square grid. The delivery company has offices at square 1A, and three trucks initially follow a common path (blue) before branching out into different routes (yellow and green). The goal is to optimize package delivery by considering truck capacity, distance to destination, and available space.

### Shipment Details
When a customer comes in with a shipment, they provide:
- Weight of the shipment in kilograms.
- Size of the box required in cubic meters.
- Destination of the box specified by a row number and column letter within the black rectangles (buildings).

### Truck Specifications
- All trucks can hold up to 1500 kilograms of cargo.
- Trucks can carry 48 cubic meters of boxes in 1/2, 1, and 2 cubic meter sizes.
- Boxes are square, with the same dimensions on all sides.

### Delivery Process
1. Find a truck that can hold the shipment and is close to the destination.
2. Consider the distance a truck must divert from its route to deliver the package.
3. Trucks cannot drive through black buildings on the map.
4. If two trucks are equidistant, choose the one with more available space (consider weight and volume).

### Measuring Distance
- Euclidean distance is used to determine the closest truck to the destination.
- A* algorithm is employed to find the shortest path between two points, considering buildings.

## Shortest Path Algorithm
- A* algorithm uses Euclidean distance as a heuristic to determine the best route.
- The algorithm can get stuck at the edge of the map or in a corner of a building.

## Overall Algorithm
1. Follow the route for each truck.
2. Calculate the Euclidean distance to the destination for each truck.
3. Select the minimum Euclidean distance for each truck.
4. Calculate the shortest path from each truck's position to the destination.
5. If a truck cannot find a path to the destination, choose another available truck.
6. Select the truck with the shortest path from its route to the destination.
7. Attempt to add the package to the selected truck.
8. If the truck cannot hold the package, try the next closest truck.
9. If no truck can take the package, store it at the depot until the next day.


## Test Automation
To automate testing, copy the script into the `.git/hooks` directory in your repository. Ensure the script is named `pre-push` in the hooks directory.

**Note**: Follow the agile development process, update code documentation, and use Jira for issue tracking. Meet regularly to discuss project progress.



 **Refer to** [Project Instructions.pdf](https://github.com/AbhayMahendera/SFT-Project/blob/main/Project%20Instructions.pdf)
