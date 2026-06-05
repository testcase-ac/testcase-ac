#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25000, "N");
    inf.readEoln();

    set<int> endpoints;
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 2000000000, "A");
        inf.readSpace();
        int b = inf.readInt(1, 2000000000, "B");
        inf.readEoln();

        ensuref(a < b, "interval %d has A >= B: %d >= %d", i + 1, a, b);
        ensuref(endpoints.insert(a).second, "endpoint %d is reused at interval %d", a, i + 1);
        ensuref(endpoints.insert(b).second, "endpoint %d is reused at interval %d", b, i + 1);
    }

    inf.readEof();
}
