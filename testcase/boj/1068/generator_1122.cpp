#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(4, 12);  // Generate a small N for easy verification
    vector<int> perm = rnd.perm(N, 0);  // Generate permutation of 0 to N-1
    vector<int> parent(N);
    parent[perm[0]] = -1;  // Root node

    int max_child = rnd.next(1, N-1); // define max_child for more variable type of tree
    vector<int> child_count(N, 0);
    for (int i = 1; i < N; ++i) {
        int p_index = rnd.next(0, i-1);  // Choose a parent from the previous nodes in permutation
        while(child_count[p_index] >= max_child) {
            p_index = rnd.next(0, i-1);
        }
        parent[perm[i]] = perm[p_index];
        child_count[p_index]++;
    }
    
    int del_node = rnd.next(0, N-1);  // Random node to delete
    
    // Output the test case
    println(N);
    for (int i = 0; i < N; ++i) {
        if (i > 0) cout << " ";
        cout << parent[i];
    }
    cout << endl;
    println(del_node);
    
    return 0;
}
