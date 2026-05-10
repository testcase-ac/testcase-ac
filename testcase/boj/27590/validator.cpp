#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: d_s, y_s
    int d_s = inf.readInt(0, 49, "d_s");
    inf.readSpace();
    int y_s = inf.readInt(d_s + 1, 50, "y_s"); // y_s > d_s
    inf.readEoln();

    // Second line: d_m, y_m
    int d_m = inf.readInt(0, 49, "d_m");
    inf.readSpace();
    int y_m = inf.readInt(d_m + 1, 50, "y_m"); // y_m > d_m
    inf.readEoln();

    // Global property: There is NOT an eclipse happening right now.
    // That is, there is no integer k >= 0 such that:
    // (d_s - k) mod y_s == 0 and (d_m - k) mod y_m == 0 for k == 0
    // i.e., d_s % y_s == 0 and d_m % y_m == 0 is NOT allowed.
    ensuref(!(d_s % y_s == 0 && d_m % y_m == 0),
        "There is an eclipse happening right now (k=0): d_s mod y_s == 0 and d_m mod y_m == 0");

    // Global property: There will be an eclipse within the next 5000 years.
    // That is, there exists k in [1,5000] such that:
    // (d_s - k) mod y_s == 0 and (d_m - k) mod y_m == 0
    bool found = false;
    for (int k = 1; k <= 5000; ++k) {
        if ((d_s - k) % y_s == 0 && (d_m - k) % y_m == 0) {
            found = true;
            break;
        }
    }
    ensuref(found, "No eclipse found within the next 5000 years for (d_s=%d, y_s=%d, d_m=%d, y_m=%d)", d_s, y_s, d_m, y_m);

    inf.readEof();
}
