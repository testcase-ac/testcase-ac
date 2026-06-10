#include "testlib.h"

#include <string>

using namespace std;

int readArrangement(int h, int w, const string& label) {
    int coins = 0;
    string pattern = "[.O]{" + to_string(w) + "}";
    for (int i = 0; i < h; ++i) {
        string row = inf.readToken(pattern, (label + "_row").c_str());
        inf.readEoln();
        for (char cell : row) {
            if (cell == 'O') {
                ++coins;
            }
        }
    }
    return coins;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h1 = inf.readInt(1, 10, "H_1");
    inf.readSpace();
    int w1 = inf.readInt(1, 10, "W_1");
    inf.readEoln();

    int coins1 = readArrangement(h1, w1, "current");

    int h2 = inf.readInt(1, 10, "H_2");
    inf.readSpace();
    int w2 = inf.readInt(1, 10, "W_2");
    inf.readEoln();

    int coins2 = readArrangement(h2, w2, "target");

    ensuref(coins1 == coins2,
            "the two arrangements must contain the same number of coins: %d != %d",
            coins1,
            coins2);
    // CHECK: The statement describes arrangements with coins, so reject empty shapes.
    ensuref(coins1 > 0, "arrangements must contain at least one coin");

    inf.readEof();
}
