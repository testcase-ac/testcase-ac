#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 2000, "K");
    inf.readSpace();
    inf.readInt(1, 1000000000, "Q");
    inf.readEoln();

    vector<int> count(n + 1);
    for (int i = 0; i < n; ++i) {
        vector<int> colors = inf.readInts(k, 1, n, "color");
        inf.readEoln();
        for (int color : colors) ++count[color];
    }

    for (int color = 1; color <= n; ++color)
        ensuref(count[color] == k, "color %d occurs %d times, expected %d",
                color, count[color], k);

    inf.readEof();
}
