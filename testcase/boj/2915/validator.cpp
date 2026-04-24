#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the Roman numeral B: must consist only of characters I, V, X, L, C (uppercase)
    string B = inf.readToken("[IVXLC]+", "B");
    inf.readEoln();

    // Precompute all valid Roman numerals for numbers 1 through 99
    vector<string> romanOnes = {
        "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
    };
    vector<string> romanTens = {
        "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"
    };
    set<string> valid;
    for (int t = 0; t <= 9; t++) {
        for (int o = 0; o <= 9; o++) {
            int val = t * 10 + o;
            if (val >= 1 && val < 100) {
                valid.insert(romanTens[t] + romanOnes[o]);
            }
        }
    }

    // Check that B is one of the valid Roman numerals from 1 to 99
    ensuref(valid.count(B),
            "Invalid Roman numeral B='%s': must be a standard form representing 1..99", 
            B.c_str());

    inf.readEof();
    return 0;
}
