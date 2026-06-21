#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int star = 1; star <= n; ++star) {
        setTestCase(star);

        int e = inf.readInt(0, 10, "E");
        inf.readEoln();

        set<pair<int, int>> edges;
        for (int i = 1; i <= e; ++i) {
            int a = inf.readInt(1, 5, "a");
            inf.readSpace();
            int b = inf.readInt(1, 5, "b");
            inf.readEoln();

            ensuref(a != b, "star %d edge %d is a self-loop: %d %d", star, i, a, b);
            auto edge = minmax(a, b);
            ensuref(edges.insert(edge).second,
                    "star %d edge %d duplicates edge %d %d",
                    star,
                    i,
                    edge.first,
                    edge.second);
        }
    }

    inf.readEof();
    return 0;
}
