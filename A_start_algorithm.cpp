#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
struct Node {
    Point point;
    Node* parent;
    int g;  // Cost from start node to this node
    int h;  // Heuristic (estimated cost from this node to goal)
    Node(Point _point, Node* _parent, int _g, int _h)
        : point(_point), parent(_parent), g(_g), h(_h) {}
    
    // Define a comparison operator for priority queue
    bool operator>(const Node& other) const {
        return (g + h) > (other.g + other.h);
    }
};

// A* algorithm implementation
vector<Point> astar(vector<vector<int>>& grid, Point start, Point goal) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Define possible moves (up, down, left, right, and diagonals)
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    
    // Create a priority queue for open nodes
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    
    // Create a 2D array to track the cost of reaching each cell
    vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));
    
    // Initialize the start node and add it to the open set
    Node startNode(start, nullptr, 0, abs(start.x - goal.x) + abs(start.y - goal.y));
    openSet.push(startNode);
    cost[start.x][start.y] = 0;
    
    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        
        // Check if we have reached the goal
        if (current.point.x == goal.x && current.point.y == goal.y) {
            // Reconstruct the path from goal to start
            vector<Point> path;
            while (current.parent != nullptr) {
                path.push_back(current.point);
                current = *current.parent;
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        
        // Explore the neighbors
        for (int i = 0; i < 8; i++) {
            int newX = current.point.x + dx[i];
            int newY = current.point.y + dy[i];
            
            // Check if the neighbor is within bounds and is a valid move
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == 0) {
                int newG = current.g + 1;  // Assuming uniform cost for all moves
                
                // If this path is better than the previous one, update the cost and add to open set
                if (newG < cost[newX][newY]) {
                    cost[newX][newY] = newG;
                    int newH = abs(newX - goal.x) + abs(newY - goal.y);
                    Node neighbor(Point(newX, newY), &current, newG, newH);
                    openSet.push(neighbor);
                }
            }
        }
    }
    
    // If the open set is empty and the goal is not reached, return an empty path
    return vector<Point>();
}

int main() {
    
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    
    Point start(0, 0);
    Point goal(4, 4);
    
    vector<Point> path = astar(grid, start, goal);
    
    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (const Point& point : path) {
            cout << "(" << point.x << ", " << point.y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }
    
    return 0;
}
