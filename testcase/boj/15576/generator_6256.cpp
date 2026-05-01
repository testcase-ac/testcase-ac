#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string genNumber(int maxLen, int skew) {
    // Generate length in [1..maxLen] with weighted distribution
    int len = rnd.wnext(maxLen, skew) + 1;
    string s;
    s.reserve(len);
    // First digit non-zero
    char first = char('1' + rnd.next(9)); // '1'..'9'
    s.push_back(first);
    // Remaining digits 0-9
    for (int i = 1; i < len; i++)
        s.push_back(char('0' + rnd.next(10)));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Maximum length of each number
    const int MAX_LEN = 30;
    // Possible skew parameters for wnext
    vector<int> skews = {-3, -1, 0, 1, 3};

    // Choose scenario to cover edge cases
    int scenario = rnd.next(0, 3);
    string A, B;

    if (scenario == 0) {
        // A = 0, B general
        A = "0";
        int skewB = rnd.any(skews);
        B = genNumber(MAX_LEN, skewB);
    } else if (scenario == 1) {
        // B = 0, A general
        B = "0";
        int skewA = rnd.any(skews);
        A = genNumber(MAX_LEN, skewA);
    } else if (scenario == 2) {
        // Both small single-digit (1-9)
        A = string(1, char('1' + rnd.next(9)));
        B = string(1, char('1' + rnd.next(9)));
    } else {
        // General both non-zero
        int skewA = rnd.any(skews);
        int skewB = rnd.any(skews);
        A = genNumber(MAX_LEN, skewA);
        B = genNumber(MAX_LEN, skewB);
    }

    // Output the two numbers
    println(A, B);
    return 0;
}
