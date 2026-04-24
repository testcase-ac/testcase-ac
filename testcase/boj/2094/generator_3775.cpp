#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of known years (at least 2 for queries diversity)
    int n = rnd.next(2, 10);

    // Generate a base year and increasing gaps
    int baseYear = rnd.next(-10, 10);
    int maxGap = rnd.next(1, 5);
    vector<int> years(n);
    years[0] = baseYear;
    for (int i = 1; i < n; i++) {
        years[i] = years[i-1] + rnd.next(1, maxGap);
    }

    // Generate rainfall data with a random trend: increasing, decreasing, or random
    vector<int> rain(n);
    int trend = rnd.next(-1, 1); // -1: decreasing, 0: random, 1: increasing
    if (trend > 0) {
        rain[0] = rnd.next(1, 1000);
        for (int i = 1; i < n; i++)
            rain[i] = rain[i-1] + rnd.next(0, 1000);
    } else if (trend < 0) {
        rain[0] = rnd.next(1, 10000);
        for (int i = 1; i < n; i++)
            rain[i] = max(1, rain[i-1] - rnd.next(0, 1000));
    } else {
        for (int i = 0; i < n; i++)
            rain[i] = rnd.next(1, 10000);
    }

    // Number of queries
    int m = rnd.next(1, 15);
    int ext = rnd.next(1, 5); // extension beyond known years

    // Output known data
    println(n);
    for (int i = 0; i < n; i++)
        println(years[i], rain[i]);

    // Build and output queries
    println(m);
    int y0 = years.front();
    int y1 = years.back();
    for (int i = 0; i < m; i++) {
        // Four types of queries for diversity
        int type = rnd.next(0, 3);
        int Y, X;
        if (type == 0) {
            // Both years inside known range
            Y = rnd.next(y0, y1 - 1);
            X = rnd.next(Y + 1, y1);
        } else if (type == 1) {
            // Y inside, X outside to the right
            Y = rnd.next(y0, y1 - 1);
            X = rnd.next(y1 + 1, y1 + ext);
        } else if (type == 2) {
            // Y outside to the left, X inside
            Y = rnd.next(y0 - ext, y0 - 1);
            X = rnd.next(y0 + 1, y1);
        } else {
            // Both outside: left and right
            Y = rnd.next(y0 - ext, y0 - 1);
            X = rnd.next(y1 + 1, y1 + ext);
        }
        println(Y, X);
    }

    return 0;
}
