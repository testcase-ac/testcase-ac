#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int N = rnd.next(1, 10);
    println(N);

    // Predefined ranges for area and base
    pair<int,int> areaRanges[3] = {{0, 10}, {10, 100}, {100, 1000}};
    pair<int,int> baseRanges[3] = {{0, 10}, {10, 100}, {100, 1000}};

    for (int i = 0; i < N; i++) {
        // Pick a random range type for area and base
        auto ar = areaRanges[rnd.next(0, 2)];
        auto br = baseRanges[rnd.next(0, 2)];

        // Generate area = intPart + fracPart/100
        int aInt = rnd.next(ar.first, ar.second);
        int aFrac = rnd.next(0, 99);
        double area = aInt + aFrac / 100.0;

        // Generate base, ensure it's > 0 by making fracPart >= 1 if intPart == 0
        int bInt = rnd.next(br.first, br.second);
        int bFrac = rnd.next(1, 99);
        double base = bInt + bFrac / 100.0;

        // Print with two decimal places
        printf("%.2f %.2f\n", area, base);
    }

    return 0;
}
