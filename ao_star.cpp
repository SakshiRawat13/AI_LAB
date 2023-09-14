#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int x;
  int y;
  int g_score;
  int f_score;
  Node* parent;
};

int monkey_banana_problem(int n, int m, int x, int y) {
  // Create a list of all possible nodes
  vector<Node> nodes;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      nodes.push_back(Node{i, j, 0, 0, nullptr});
    }
  }

  // Initialize the start and goal nodes
  Node start = nodes[x * n + y];
  Node goal = nodes[n - 1][n - 1];

  // Create the open and closed lists
  vector<Node*> open;
  vector<Node*> closed;

  // Add the start node to the open list
  open.push_back(&start);

  while (len(open) > 0) {
    // Get the node with the lowest f_score
    Node* node = open[0];
    for (int i = 1; i < len(open); i++) {
      if (open[i]->f_score < node->f_score) {
        node = open[i];
      }
    }

    // If the node is the goal node, then return the path
    if (node == &goal) {
      vector<Node*> path;
      while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
      }
      reverse(path.begin(), path.end());
      return path;
    }

    // Add the node to the closed list
    closed.push_back(node);

    // Get the neighbors of the node
    vector<Node*> neighbors = get_neighbors(node);

    // For each neighbor, calculate the g_score and f_score
    for (Node* neighbor : neighbors) {
      int g_score = node->g_score + neighbor->cost;
      int f_score = g_score + heuristic(neighbor);

      // If the neighbor is not in the open list or if the f_score is less than the f_score of the neighbor in the open list, then update the neighbor
      if (neighbor not in open or f_score < neighbor->f_score) {
        neighbor->g_score = g_score;
        neighbor->f_score = f_score;
        neighbor->parent = node;
        open.push_back(neighbor);
      }
    }
  }

  return {};
}

int main() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;

  vector<Node*> path = monkey_banana_problem(n, m, x, y);

  if (len(path) == 0) {
    cout << "No solution" << endl;
  } else {
    for (Node* node : path) {
      cout << node->x << " " << node->y << endl;
    }
  }

  return 0;
}
