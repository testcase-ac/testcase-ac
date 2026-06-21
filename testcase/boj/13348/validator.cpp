#include "testlib.h"

#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even, got %d", n);

    int k = inf.readInt(0, 1000, "K");
    inf.readEoln();

    vector<string> pictureAt(n + 1);
    vector<bool> faceUp(n + 1, false);
    map<string, set<int>> positionsByPicture;
    int faceUpCount = 0;

    for (int i = 1; i <= k; ++i) {
        int c1 = inf.readInt(1, n, "C_1");
        inf.readSpace();
        int c2 = inf.readInt(1, n, "C_2");
        inf.readSpace();
        string p1 = inf.readToken("[a-z]{1,20}", "P_1");
        inf.readSpace();
        string p2 = inf.readToken("[a-z]{1,20}", "P_2");
        inf.readEoln();

        ensuref(c1 != c2, "turn %d chooses the same card twice: %d", i, c1);
        ensuref(!faceUp[c1], "turn %d chooses already face-up card %d", i, c1);
        ensuref(!faceUp[c2], "turn %d chooses already face-up card %d", i, c2);

        if (!pictureAt[c1].empty()) {
            ensuref(pictureAt[c1] == p1,
                    "turn %d gives card %d picture %s, previously %s",
                    i, c1, p1.c_str(), pictureAt[c1].c_str());
        } else {
            pictureAt[c1] = p1;
            positionsByPicture[p1].insert(c1);
        }

        if (!pictureAt[c2].empty()) {
            ensuref(pictureAt[c2] == p2,
                    "turn %d gives card %d picture %s, previously %s",
                    i, c2, p2.c_str(), pictureAt[c2].c_str());
        } else {
            pictureAt[c2] = p2;
            positionsByPicture[p2].insert(c2);
        }

        ensuref(positionsByPicture[p1].size() <= 2,
                "turn %d makes picture %s appear on more than two positions",
                i, p1.c_str());
        ensuref(positionsByPicture[p2].size() <= 2,
                "turn %d makes picture %s appear on more than two positions",
                i, p2.c_str());

        if (p1 == p2) {
            faceUp[c1] = true;
            faceUp[c2] = true;
            faceUpCount += 2;
        }
    }

    ensuref(n - faceUpCount >= 2, "fewer than two cards remain face-down");
    inf.readEof();
}
