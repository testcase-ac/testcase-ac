/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of houses
    int N = rnd.next(2, 10);
    // Number of routers
    int C = rnd.next(2, N);

    // Generate unique coordinates in [0,100]
    const int MAX_COORD = 100;
    vector<int> pool;
    for (int i = 0; i <= MAX_COORD; i++)
        pool.push_back(i);
    shuffle(pool.begin(), pool.end());
    vector<int> xs(pool.begin(), pool.begin() + N);

    // Output
    println(N, C);
    for (int x : xs)
        println(x);
    return 0;
}
