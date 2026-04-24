#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of points
    int N = rnd.next(1, 10);
    // Grid size parameter L (ensure L >= N)
    int L = N + rnd.next(0, 5);
    // Number of categories k
    int k = rnd.next(1, min(N, 8));

    // Distribute N points among k sets P_i
    vector<int> sizes(k, 0);
    int rem = N;
    for (int i = 0; i < k; ++i) {
        if (i + 1 < k) {
            sizes[i] = rnd.next(0, rem);
            rem -= sizes[i];
        } else {
            sizes[i] = rem;
        }
    }

    // Build assignment of each point to a category index 1..k
    vector<int> idx;
    for (int i = 0; i < k; ++i) {
        for (int t = 0; t < sizes[i]; ++t)
            idx.push_back(i + 1);
    }
    shuffle(idx.begin(), idx.end());

    // Generate distinct x and y coordinates
    vector<int> allX(L+1), allY(L+1);
    for (int i = 0; i <= L; ++i) {
        allX[i] = i;
        allY[i] = i;
    }
    shuffle(allX.begin(), allX.end());
    shuffle(allY.begin(), allY.end());
    vector<int> xList(allX.begin(), allX.begin() + N);
    vector<int> yList(allY.begin(), allY.begin() + N);

    // Shuffle lists to decouple
    shuffle(xList.begin(), xList.end());
    shuffle(yList.begin(), yList.end());

    // Choose target counts c_i for each P_i
    vector<int> c(k);
    for (int i = 0; i < k; ++i) {
        if (sizes[i] > 0)
            c[i] = rnd.next(0, sizes[i]);
        else
            c[i] = 0;
    }

    // Output
    // Line1: L and k
    println(L, k);
    // Line2: c_1 ... c_k
    println(c);
    // Line3: N
    println(N);
    // Next N lines: x y i
    for (int j = 0; j < N; ++j) {
        println(xList[j], yList[j], idx[j]);
    }

    return 0;
}
