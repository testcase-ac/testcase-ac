#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lines
    int N = rnd.next(1, 10);
    vector<string> lines;
    for (int i = 0; i < N; i++) {
        // Line length hyper-parameter: skewed between 0 and 20
        int maxLen = 20;
        int t = rnd.next(-2, 2);
        int L = rnd.wnext(maxLen + 1, t);

        // Category weights: lowercase, uppercase, digit, space
        vector<int> w(4);
        int sum = 0;
        for (int c = 0; c < 4; c++) {
            w[c] = rnd.next(0, 5);
            sum += w[c];
        }
        if (sum == 0) {
            // ensure at least one category
            int c = rnd.next(0, 3);
            w[c] = 1;
            sum = 1;
        }

        // Build the string
        string s;
        s.reserve(L);
        for (int j = 0; j < L; j++) {
            int pick = rnd.next(1, sum);
            int cum = 0, cat = 0;
            for (; cat < 4; cat++) {
                cum += w[cat];
                if (pick <= cum) break;
            }
            char ch;
            if (cat == 0) {
                ch = char(rnd.next('a', 'z'));
            } else if (cat == 1) {
                ch = char(rnd.next('A', 'Z'));
            } else if (cat == 2) {
                ch = char(rnd.next('0', '9'));
            } else {
                ch = ' ';
            }
            s.push_back(ch);
        }
        lines.push_back(s);
    }

    // Output generated lines
    for (auto &s : lines) {
        println(s);
    }

    return 0;
}
