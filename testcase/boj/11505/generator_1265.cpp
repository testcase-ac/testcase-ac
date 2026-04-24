#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    
    // Generate small parameters for easy human verification
    int N = rnd.next(1, 10);      // Number of elements
    int M = rnd.next(1, 10);      // Number of update operations
    int K = rnd.next(1, 10);      // Number of query operations
    
    // Print first line: N, M, K
    println(N, M, K);
    int MX = 1000;
    if(rnd.next() < 0.5) MX = 9;
    // Print the initial N numbers (each between 0 and 1,000,000)
    for (int i = 0; i < N; i++){
        println(rnd.next(0, MX));
    }
    
    // Prepare a vector to store the operations.
    // Each operation is represented as a triple: (a, b, c)
    vector<tuple<int,int,int>> ops;
    
    // M update operations: set the b-th number to c (a = 1)
    for (int i = 0; i < M; i++){
        int index = rnd.next(1, N);         // valid index between 1 and N
        int newVal = rnd.next(0, MX);    // new value between 0 and 1,000,000
        ops.push_back(make_tuple(1, index, newVal));
    }
    
    // K query operations: query the product from b to c (a = 2)
    for (int i = 0; i < K; i++){
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);             // ensure l <= r
        ops.push_back(make_tuple(2, l, r));
    }
    
    // Shuffle the operations to interleave updates and queries.
    shuffle(ops.begin(), ops.end());
    while(get<0>(ops.back()) == 1) {
      shuffle(ops.begin(), ops.end());
    }
    
    // Print each operation.
    for(auto &op : ops){
        int a, b, c;
        tie(a, b, c) = op;
        println(a, b, c);
    }
    
    return 0;
}
