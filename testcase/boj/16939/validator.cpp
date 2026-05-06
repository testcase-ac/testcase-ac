#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The cube has 24 stickers, colors are 1..6, each appears exactly 4 times.
    vector<int> colors = inf.readInts(24, 1, 6, "color");
    inf.readEoln();

    // Check each color appears exactly 4 times
    vector<int> cnt(7, 0);
    for (int i = 0; i < 24; i++) {
        cnt[colors[i]]++;
    }
    for (int c = 1; c <= 6; c++) {
        ensuref(cnt[c] == 4,
                "Color %d appears %d times, but it must appear exactly 4 times",
                c, cnt[c]);
    }

    inf.readEof();
    return 0;
}
