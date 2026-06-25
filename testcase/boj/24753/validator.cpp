#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(3, 1000, "S");
    inf.readSpace();
    int n = inf.readInt(1, s / 2, "N");
    inf.readEoln();

    vector<int> a;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a.push_back(inf.readInt(1, s, "a_i"));
    }
    inf.readEoln();
    inf.readEof();

    for (int i = 1; i < n; ++i) {
        ensuref(a[i - 1] < a[i],
                "occupied seats must be strictly increasing: a[%d]=%d, a[%d]=%d",
                i, a[i - 1], i + 1, a[i]);
        ensuref(a[i] - a[i - 1] > 1,
                "adjacent occupied seats at positions %d and %d: %d, %d",
                i, i + 1, a[i - 1], a[i]);
    }
    ensuref(a.front() != 1 || a.back() != s,
            "occupied seats 1 and S are adjacent in the circular table");
}
