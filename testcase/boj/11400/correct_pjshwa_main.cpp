// A C++ program to find strongly connected components in a given 
// directed graph using Tarjan's algorithm (single DFS) 
#include <bits/stdc++.h> 
#define NIL -1 
using namespace std; 
  
// A class that represents an directed graph 
class Graph { 
    int V;    // No. of vertices 
    list<int> *adj;    // A dynamic array of adjacency lists 
    vector<pair<int, int> > *bridges;
  
    // A Recursive DFS based function used by SCC() 
    void SCCUtil(int u, int disc[], int low[], int parent[]); 
public: 
    Graph(int V);   // Constructor 
    void addEdge(int v, int w);   // function to add an edge to graph 
    void SCC();    // prints strongly connected components 
}; 
  
Graph::Graph(int V) { 
    this->V = V; 
    adj = new list<int>[V]; 
    bridges = new vector<pair<int, int> >; 
} 
  
void Graph::addEdge(int v, int w) { 
    adj[v].push_back(w); 
} 
  
// A recursive function that finds and prints strongly connected 
// components using DFS traversal 
// u --> The vertex to be visited next 
// disc[] --> Stores discovery times of visited vertices 
// low[] -- >> earliest visited vertex (the vertex with minimum 
//             discovery time) that can be reached from subtree 
//             rooted with current vertex 
void Graph::SCCUtil(int u, int disc[], int low[], int parent[]) { 
  // A static variable is used for simplicity, we can avoid use 
  // of static variable by passing a pointer. 
  static int time = 0; 

  // Initialize discovery time and low value 
  disc[u] = low[u] = ++time; 

  // Go through all vertices adjacent to this 
  list<int>::iterator i; 
  for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
      int v = *i;  // v is current adjacent of 'u' 

      // If v is not visited yet, then recur for it 
      if (disc[v] == NIL) 
      { 
          parent[v] = u; 
          SCCUtil(v, disc, low, parent); 

          // Check if the subtree rooted with 'v' has a 
          // connection to one of the ancestors of 'u' 
          // Case 1 (per above discussion on Disc and Low value) 
          low[u] = min(low[u], low[v]); 

          if (low[v] > disc[u]) {
            if (u < v) bridges->push_back({u, v});
            else bridges->push_back({v, u});
          }
      } 

      // Update low value of 'u' only of 'v' is still in stack 
      // (i.e. it's a back edge, not cross edge). 
      // Case 2 (per above discussion on Disc and Low value) 
      else if (v != parent[u]) low[u] = min(low[u], disc[v]); 
  } 
} 
  
// The function to do DFS traversal. It uses SCCUtil() 
void Graph::SCC() 
{ 
  int *disc = new int[V]; 
  int *low = new int[V]; 
  int *parent = new int[V]; 

  // Initialize disc and low, and parent arrays 
  for (int i = 0; i < V; i++) 
  { 
      disc[i] = NIL; 
      low[i] = NIL; 
      parent[i] = NIL; 
  } 

  // Call the recursive helper function to find strongly 
  // connected components in DFS tree with vertex 'i' 
  for (int i = 0; i < V; i++) 
      if (disc[i] == NIL) 
          SCCUtil(i, disc, low, parent); 

  int aa, bb;
  sort(bridges->begin(), bridges->end());
  cout << bridges->size() << '\n';
  for(auto it = bridges->begin(); it != bridges->end(); it++){
    tie(aa, bb) = *it;
    cout << aa + 1 << ' ' << bb + 1 << '\n';
  }
} 
  
// Driver program to test above function 
int main() 
{ 
  int v, e, a, b;
  cin >> v >> e;
  Graph g1(v);

  while (e--) {
    cin >> a >> b;
    g1.addEdge(a - 1, b - 1); 
    g1.addEdge(b - 1, a - 1); 
  }

  g1.SCC();
} 
