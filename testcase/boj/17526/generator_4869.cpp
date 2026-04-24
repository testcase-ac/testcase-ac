#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of planets
    int n = rnd.next(3, 10);

    // Hyper-parameters for diversity
    vector<int> distCaps = {10, 100, 1000};
    int maxDist = rnd.any(distCaps);

    vector<int> paceCaps = {5, 10, 100, 100000};
    int maxPace = rnd.any(paceCaps);

    vector<int> prepCaps = {0, 50, 200, 1000, 1000000000};
    int maxPrep = rnd.any(prepCaps);

    // Distances between adjacent planets: size n-1
    vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++) {
        d[i] = rnd.next(1, maxDist);
    }
    // Occasionally make distances monotonic to test edge behaviors
    if (rnd.next(0, 1)) {
        if (rnd.next(0, 1))
            sort(d.begin(), d.end());
        else
            sort(d.begin(), d.end(), greater<int>());
    }

    // Preparation time and pace for planets 1..n-1
    vector<long long> p(n);
    vector<int> s(n);
    for (int i = 1; i < n; i++) {
        p[i] = rnd.next(0, maxPrep);
        s[i] = rnd.next(1, maxPace);
    }
    // Force some extreme cases at start
    if (rnd.next(0, 1)) p[1] = 0;
    if (rnd.next(0, 1)) p[1] = maxPrep;
    if (rnd.next(0, 1)) s[1] = 1;
    if (rnd.next(0, 1)) s[1] = maxPace;

    // Output
    println(n);
    println(d);
    for (int i = 1; i < n; i++) {
        println(p[i], s[i]);
    }
    return 0;
}
