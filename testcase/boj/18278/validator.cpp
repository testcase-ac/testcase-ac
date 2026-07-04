#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "q");
    inf.readEoln();

    string colors = inf.readToken("[CZ]{1,100000}", "colors");
    ensuref((int)colors.size() == n, "colors length must be n: got %d, expected %d",
            (int)colors.size(), n);
    inf.readEoln();

    bool hasBlack = false;
    bool hasYellow = false;
    for (char color : colors) {
        hasBlack |= color == 'C';
        hasYellow |= color == 'Z';
    }
    ensuref(hasBlack, "there must be at least one contestant with a black shirt");
    ensuref(hasYellow, "there must be at least one contestant with a yellow shirt");

    vector<int> score(n, 0);
    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int d = inf.readInt(1, 300000, "d_i");
        inf.readEoln();

        score[x - 1] += d;
        ensuref(score[x - 1] <= 300000,
                "contestant %d score exceeds 300000 after update %d: %d",
                x, i, score[x - 1]);
    }

    inf.readEof();
}
