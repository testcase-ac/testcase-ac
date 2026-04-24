#include "testlib.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    // Register the program as a test generator
    registerGen(argc, argv, 1);
    
    // Number of nodes
    int n = rnd.wnext(6, 0) + 3;

    // Output the number of nodes
    cout << n << "\n";
    
    // Prepare a list of nodes
    vector<int> nodes;
    
    // Initially, add the first node (this can be the root)
    nodes.push_back(1);
    vector<pair<int, int>> edges;
    // Generate random edges by attaching each new node to a previously added node
    for (int i = 2; i <= n; i++) {
        // Randomly choose an existing node from the current tree (nodes vector)
        int parent = nodes[rnd.wnext(nodes.size(), 0)];
        
        // Add the current node to the nodes list
        nodes.push_back(i);
        
        // Print the edge between the chosen parent and the current node
        edges.push_back({i, parent});
        if(rnd.next(0, 1)) {
          swap(edges.back().first, edges.back().second);
        }
    }
    shuffle(edges.begin(), edges.end());
  for(auto [a, b]: edges)
      cout << a << ' ' << b << '\n';
    
    return 0;
}
