# A* Pathfinding Dojo

This project is a grid-based A* (A-star) pathfinding algorithm implementation in C++. It includes a test runner that parses ASCII grids from text files, runs the A* search to find the shortest path, and validates the result against expected costs.

You must implement the A* function and return the cost of the path found.
If path is not found return `-1`, else the cost of the path.

The path cost is the number of times you move. If you have a single cell in your path that is not the start nor end cell then your path is of length `2`. Find more info in the test files.


## Requirements

* A C++ compiler that supports C++17 (e.g., `g++`).
* A Bash or POSIX-compliant shell to run the build script.

## Usage

You can build and run the algorithm using the included `run.sh` script.

### Running Basic Tests

By default, running the script with no arguments will compile the code and execute the scenarios in `basic_tests.txt`.

```bash
./run.sh
```

### Running Specific Test Files

You can specify a different test file as an argument to the script. For example, to run the advanced tests:

```bash
./run.sh advanced_tests.txt
```

## Adding Custom Tests

You can create your own test files or add to the existing ones. The parser reads a custom text format.

### Test File Format Example

```text
Name: My Custom Test
Cost: 14
GRID_START
S.#...#...
..#.#...#.
....#.....
.#.....#..
...#.#....
#......#G.
GRID_END
```

* **Name**: A descriptive name for the test scenario.
* **Cost**: The expected number of steps for the optimal (shortest) path. If no path exists, set expected cost to `-1`.
* **GRID_START** / **GRID_END**: Boundaries for the ASCII grid.
* **Grid Characters**: 
  * `S`: Start position
  * `G`: Goal position
  * `#`: Wall (impassable)
  * `.` or `_` (or any other character): Empty passable space

If the path found has the expected `Cost`, the test passes. If it's higher (sub-optimal) or lower (which shouldn't happen with A* and an optimal heuristic), it prints a warning.
