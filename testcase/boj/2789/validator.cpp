#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single word: uppercase letters, length between 3 and 100.
    string s = inf.readToken("[A-Z]{3,100}", "s");
    inf.readEoln();

    // After removing all letters in "CAMBRIDGE", the result must be non-empty.
    const string forbidden = "CAMBRIDGE";
    // Use a lookup set for O(1) checks.
    bool is_forb[256] = {};
    for (char c : forbidden) {
        is_forb[(unsigned char)c] = true;
    }
    int remain = 0;
    for (char c : s) {
        if (!is_forb[(unsigned char)c]) {
            remain++;
        }
    }
    ensuref(remain > 0,
            "After removing letters in CAMBRIDGE from \"%s\", the result is empty", 
            s.c_str());

    inf.readEof();
    return 0;
}
