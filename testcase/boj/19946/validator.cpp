#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string token = inf.readToken("[0-9]{1,20}", "N");
    inf.readEoln();
    inf.readEof();

    ensuref(token == "0" || token[0] != '0', "N has leading zero: %s", token.c_str());

    const unsigned __int128 upper = (((unsigned __int128)1) << 64) - 1;
    unsigned __int128 n = 0;
    for (char c : token) {
        n = n * 10 + (c - '0');
        ensuref(n <= upper, "N exceeds 2^64 - 1: %s", token.c_str());
    }

    ensuref(n >= 2, "N must be at least 2");

    bool possible = false;
    for (int k = 1; k <= 64; ++k) {
        unsigned __int128 value = (((unsigned __int128)1) << 64) -
                                  (((unsigned __int128)1) << (64 - k));
        if (n == value) {
            possible = true;
            break;
        }
    }
    ensuref(possible, "N is not obtainable from exactly one mistake");
}
