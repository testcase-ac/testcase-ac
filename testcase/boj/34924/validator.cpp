#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{4,100000}", "S");
    inf.readEoln();

    ensuref(static_cast<int>(s.size()) == n, "S length must be N: got %d, expected %d",
            static_cast<int>(s.size()), n);

    for (char c : string("PAUL")) {
        int count = 0;
        for (char x : s) {
            if (x == c) {
                ++count;
            }
        }
        ensuref(count == 1, "%c must appear exactly once: got %d", c, count);
    }

    inf.readEof();
}
