#include "testlib.h"
using namespace std;

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int dim(int y, int m) {
    static int a[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeap(y)) return 29;
    return a[m];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sample a valid start date between 1900-01-01 and 2014-12-31
    int year = rnd.next(1900, 2014);
    int month = rnd.next(1, 12);
    int day = rnd.next(1, dim(year, month));

    // Hyper-parameter sampling for N to ensure variability
    int seg = rnd.next(0, 3);
    int N;
    if (seg == 0) {
        // very small
        N = rnd.next(1, 10);
    } else if (seg == 1) {
        // up to a year
        N = rnd.next(10, 365);
    } else if (seg == 2) {
        // multiple years
        N = rnd.next(365, 2000);
    } else {
        // up to maximum
        N = rnd.next(2000, 10000);
    }

    // Output in required format
    printf("%04d-%02d-%02d %d\n", year, month, day, N);
    return 0;
}
