#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 26, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string t = inf.readToken("[A-Z]{1,26}", "t");
        inf.readEoln();

        ensuref(static_cast<int>(t.size()) == k,
                "string %d has length %d, expected %d",
                i + 1,
                static_cast<int>(t.size()),
                k);

        vector<bool> seen(k, false);
        for (char c : t) {
            ensuref('A' <= c && c < 'A' + k,
                    "string %d contains letter %c outside first %d uppercase letters",
                    i + 1,
                    c,
                    k);
            int letter = c - 'A';
            ensuref(!seen[letter],
                    "string %d contains duplicate letter %c",
                    i + 1,
                    c);
            seen[letter] = true;
        }
    }

    inf.readEof();
}
