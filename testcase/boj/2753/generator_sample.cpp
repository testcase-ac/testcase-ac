#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int year;

    if (mode == 0) {
        vector<int> edgeYears = {1, 2, 3, 4, 99, 100, 101, 399, 400, 401, 3999, 4000};
        year = rnd.any(edgeYears);
    } else if (mode == 1) {
        year = 4 * rnd.next(1, 1000);
    } else if (mode == 2) {
        year = 100 * rnd.next(1, 40);
    } else if (mode == 3) {
        year = 400 * rnd.next(1, 10);
    } else if (mode == 4) {
        year = rnd.next(1, 4000);
        year -= year % 4;
        if (year < 1) year = 4;
    } else {
        year = rnd.next(1, 4000);
        while (year % 4 == 0) {
            year = rnd.next(1, 4000);
        }
    }

    println(year);
    return 0;
}
