#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> a(5);
    set<int> seen;
    for (int i = 0; i < 5; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a[i] = inf.readInt(1, 100, "a_i");
        ensuref(seen.insert(a[i]).second,
                "numbers must be distinct, duplicate value %d at position %d",
                a[i], i + 1);
    }
    inf.readEoln();
    inf.readEof();

    return 0;
}
