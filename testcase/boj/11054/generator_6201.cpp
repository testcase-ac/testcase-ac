#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 4);
    vector<int> a;
    int N;
    if (type == 0) {
        // Fully random sequence
        N = rnd.next(1, 20);
        for (int i = 0; i < N; ++i)
            a.push_back(rnd.next(1, 100));
    } else if (type == 1) {
        // Strict bitonic sequence
        N = rnd.next(3, 20);
        int p = rnd.next(1, N - 1);
        int maxVal = 100;
        vector<int> pool(maxVal);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        vector<int> ups(pool.begin(), pool.begin() + p);
        vector<int> downs(pool.begin() + p, pool.begin() + N);
        sort(ups.begin(), ups.end());
        sort(downs.begin(), downs.end(), greater<int>());
        a = ups;
        a.insert(a.end(), downs.begin(), downs.end());
    } else if (type == 2) {
        // Strictly increasing distinct
        N = rnd.next(1, 20);
        int maxVal = 100;
        vector<int> pool(maxVal);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        a.assign(pool.begin(), pool.begin() + N);
        sort(a.begin(), a.end());
    } else if (type == 3) {
        // Strictly decreasing distinct
        N = rnd.next(1, 20);
        int maxVal = 100;
        vector<int> pool(maxVal);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        a.assign(pool.begin(), pool.begin() + N);
        sort(a.begin(), a.end(), greater<int>());
    } else {
        // Random with duplicates (small range)
        N = rnd.next(1, 20);
        for (int i = 0; i < N; ++i)
            a.push_back(rnd.next(1, 5));
    }

    println(N);
    println(a);
    return 0;
}
