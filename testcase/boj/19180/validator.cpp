#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string labels = "abcdefghijklmnopqrstuvwxyz0123456789";
    set<char> seen;

    for (int row = 0; row < 6; ++row) {
        string line = inf.readLine("[a-z0-9]{6}", "row");
        for (char ch : line) {
            ensuref(labels.find(ch) != string::npos,
                    "unexpected label '%c' in row %d", ch, row + 1);
            ensuref(seen.insert(ch).second,
                    "duplicate label '%c' in row %d", ch, row + 1);
        }
    }

    ensuref(int(seen.size()) == 36,
            "expected all 36 labels to appear exactly once, found %d",
            int(seen.size()));

    inf.readEof();
    return 0;
}
