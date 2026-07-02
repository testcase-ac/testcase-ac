#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 13, "N");
    inf.readSpace();
    int k = inf.readInt(1, 20, "K");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    string diePattern = "[A-Z]{" + to_string(k) + "," + to_string(k) + "}";
    for (int i = 0; i < n; ++i) {
        string die = inf.readToken(diePattern, "die");
        inf.readEoln();

        vector<bool> seen(26, false);
        for (char ch : die) {
            int index = ch - 'A';
            ensuref(!seen[index],
                    "letter %c appears more than once on die %d",
                    ch,
                    i + 1);
            seen[index] = true;
        }
    }

    string wordPattern = "[A-Z]{" + to_string(n) + "," + to_string(n) + "}";
    for (int i = 0; i < m; ++i) {
        inf.readToken(wordPattern, "word");
        inf.readEoln();
    }

    inf.readEof();
}
