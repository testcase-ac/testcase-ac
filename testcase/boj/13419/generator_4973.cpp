#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    println(T);
    for (int i = 0; i < T; i++) {
        // Decide length n (1 to 10), bias toward small but sometimes full 10
        int n;
        if (rnd.next(0, 3) == 0) {
            n = 10;
        } else {
            n = rnd.wnext(10, -1) + 1;  // range [1,10], bias small
        }
        n = min(n, 10);

        // Three pattern types
        int type = rnd.next(0, 2);
        string s;
        if (type == 0) {
            // contiguous increasing
            int start = rnd.next(0, 26 - n);
            for (int j = 0; j < n; j++) {
                s.push_back(char('A' + start + j));
            }
        } else if (type == 1) {
            // contiguous decreasing
            int start = rnd.next(n - 1, 25);
            for (int j = 0; j < n; j++) {
                s.push_back(char('A' + start - j));
            }
        } else {
            // random subset shuffled
            vector<char> alpha(26);
            for (int j = 0; j < 26; j++) alpha[j] = char('A' + j);
            shuffle(alpha.begin(), alpha.end());
            vector<char> sel(alpha.begin(), alpha.begin() + n);
            shuffle(sel.begin(), sel.end());
            for (char c : sel) s.push_back(c);
        }

        // Output the string
        printf("%s\n", s.c_str());
    }
    return 0;
}
