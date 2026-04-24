#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size hyper-parameter
    int N = rnd.next(1, 10);

    // Range hyper-parameters
    int loB = rnd.next(-10, 10);
    int hiB = rnd.next(-10, 10);
    if (loB > hiB) swap(loB, hiB);

    // Weight parameter for uneven distribution
    int tParam = rnd.next(-2, 2);

    // Decide whether to generate all distinct or allow duplicates
    bool forceDistinct = rnd.next() < 0.5;

    vector<int> a;
    a.reserve(N);

    if (forceDistinct) {
        // Build the pool of possible values
        vector<int> pool;
        for (int x = loB; x <= hiB; ++x)
            pool.push_back(x);
        shuffle(pool.begin(), pool.end());

        int take = min(N, (int)pool.size());
        // Take as many distinct as possible
        for (int i = 0; i < take; ++i)
            a.push_back(pool[i]);
        // If pool was too small, fill the rest with random repeats
        for (int i = take; i < N; ++i)
            a.push_back(pool[rnd.next(0, take - 1)]);
    } else {
        // Possibly many duplicates, using weighted random
        for (int i = 0; i < N; ++i) {
            int v = rnd.wnext(hiB - loB + 1, tParam) + loB;
            a.push_back(v);
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
