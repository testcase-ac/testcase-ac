#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Length of the string
    int N = rnd.next(1, 15);
    // Weights for each character type
    int pL = rnd.next(1, 10); // lowercase
    int pU = rnd.next(1, 10); // uppercase
    int pD = rnd.next(1, 10); // digit
    int pS = rnd.next(0, 10); // space (allow zero to drop spaces)
    int sum = pL + pU + pD + pS;

    string s;
    s.reserve(N);
    // Build the string
    for (int i = 0; i < N; i++) {
        int w = rnd.next(1, sum);
        char c;
        if (w <= pL) {
            c = char('a' + rnd.next(0, 25));
        } else if (w <= pL + pU) {
            c = char('A' + rnd.next(0, 25));
        } else if (w <= pL + pU + pD) {
            c = char('0' + rnd.next(0, 9));
        } else {
            c = ' ';
        }
        s.push_back(c);
    }
    // Ensure there's at least one non-space character
    bool has_non_space = false;
    for (char c : s) {
        if (c != ' ') { has_non_space = true; break; }
    }
    if (!has_non_space) {
        int pos = rnd.next(0, N - 1);
        int t = rnd.next(0, 2);
        char c;
        if (t == 0) c = char('a' + rnd.next(0, 25));
        else if (t == 1) c = char('A' + rnd.next(0, 25));
        else c = char('0' + rnd.next(0, 9));
        s[pos] = c;
    }

    // Output the test case
    println(s);
    return 0;
}
