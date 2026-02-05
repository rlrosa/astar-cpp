#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

// Alias for coordinates (x, y)
using Point = pair<int, int>;

// ==========================================
// PART 1: THE ENVIRONMENT
// ==========================================

struct Grid {
    int width, height;
    set<Point> walls;

    Grid(int w, int h, const vector<Point>& w_list) : width(w), height(h) {
        for(auto p : w_list) walls.insert(p);
    }

    bool in_bounds(Point id) const {
        return 0 <= id.first && id.first < width && 0 <= id.second && id.second < height;
    }

    bool passable(Point id) const {
        return walls.find(id) == walls.end();
    }

    vector<Point> neighbors(Point id) const {
        int x = id.first;
        int y = id.second;
        vector<Point> results = {{x+1, y}, {x, y-1}, {x-1, y}, {x, y+1}};
        if ((x + y) % 2 == 0) reverse(results.begin(), results.end());
        vector<Point> valid;
        for(auto p : results) {
            if (in_bounds(p) && passable(p)) valid.push_back(p);
        }
        return valid;
    }

    int cost(Point from, Point to) const { return 1; }

    void draw(const vector<Point>& path, Point start, Point goal) {
        set<Point> path_set(path.begin(), path.end());
        cout << "Map (" << width << "x" << height << "):\n";
        for(int y=0; y<height; ++y) {
            string line = "";
            for(int x=0; x<width; ++x) {
                Point p = {x, y};
                if (p == start) line += "S ";
                else if (p == goal) line += "G ";
                else if (walls.count(p)) line += "# ";
                else if (path_set.count(p)) line += ". ";
                else line += "_ ";
            }
            cout << line << endl;
        }
        cout << endl;
    }
};

// ==========================================
// PART 2: YOUR SOLUTION
// ==========================================

class Solution {
public:
    // TODO: Add helper methods (heuristic, etc.)

    vector<Point> find_path(Grid& grid, Point start, Point goal) {
        // TODO: Implement A* logic
        // Return path as vector of points, or empty vector if no path.
        
        return {}; 
    }
};

// ==========================================
// PART 3: TEST RUNNER & PARSER
// ==========================================

struct Scenario {
    string name;
    int width = 0, height = 0;
    vector<Point> walls;
    Point start = {0,0}, goal = {0,0};
    int min_cost = 0;
};

// Parses a file format where maps are drawn in ASCII
vector<Scenario> load_scenarios(const string& filename) {
    vector<Scenario> scenarios;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string line;
    Scenario current;
    bool in_grid = false;
    int grid_y = 0;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '/') continue; // Skip empty or comments

        if (line.rfind("Name:", 0) == 0) {
            if (current.width > 0) scenarios.push_back(current); // Push previous
            current = Scenario(); // Reset
            current.name = line.substr(6);
        }
        else if (line.rfind("Cost:", 0) == 0) {
            current.min_cost = stoi(line.substr(6));
        }
        else if (line == "GRID_START") {
            in_grid = true;
            grid_y = 0;
            current.walls.clear();
        }
        else if (line == "GRID_END") {
            in_grid = false;
            current.height = grid_y;
        }
        else if (in_grid) {
            if (current.width == 0) current.width = line.length();
            for (int x = 0; x < line.length(); ++x) {
                char c = line[x];
                if (c == '#') current.walls.push_back({x, grid_y});
                else if (c == 'S') current.start = {x, grid_y};
                else if (c == 'G') current.goal = {x, grid_y};
            }
            grid_y++;
        }
    }
    if (current.width > 0) scenarios.push_back(current); // Push last one
    return scenarios;
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "basic_tests.txt";
    cout << "Loading tests from: " << filename << endl;
    
    vector<Scenario> scenarios = load_scenarios(filename);
    Solution solver;
    int passed = 0;

    cout << "--- STARTING A* DOJO ---\n" << endl;

    for (const auto& s : scenarios) {
        cout << "Test: " << s.name << endl;
        Grid g(s.width, s.height, s.walls);
        
        vector<Point> path;
        try {
            path = solver.find_path(g, s.start, s.goal);
        } catch (...) {
            cout << "❌ CRASHED" << endl; continue;
        }

        g.draw(path, s.start, s.goal);

        if (s.min_cost == -1) {
            if (path.empty()) {
                cout << "✅ PASSED (No path exists)" << endl; passed++;
            } else {
                cout << "❌ FAILED (Found invalid path)" << endl;
            }
        } else {
            if (path.empty()) {
                cout << "❌ FAILED (No path found)" << endl;
            } else if (path.front() != s.start || path.back() != s.goal) {
                cout << "❌ FAILED (Wrong start/end)" << endl;
            } else {
                int cost = path.size() - 1;
                if (cost == s.min_cost) {
                    cout << "✅ PASSED (Optimal cost: " << cost << ")" << endl; passed++;
                } else {
                    cout << "⚠️ SUB-OPTIMAL (Cost: " << cost << ", Expected: " << s.min_cost << ")" << endl;
                }
            }
        }
        cout << "------------------------------" << endl;
    }

    cout << "\nSCORE: " << passed << "/" << scenarios.size() << endl;
    return 0;
}
