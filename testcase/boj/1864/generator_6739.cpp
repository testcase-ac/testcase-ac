#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of octopus numbers
    int T = rnd.next(1, 10);
    vector<string> lines;
    // All symbols including negative slash
    vector<char> sym = {'-', '\\', '(', '@', '?', '>', '&', '%', '/'};
    // Non-negative symbols (0 to 7)
    vector<char> posSym = {'-', '\\', '(', '@', '?', '>', '&', '%'};
    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 4);
        string s;
        if (type == 0) {
            // All zeros
            int len = rnd.next(1, 8);
            s = string(len, '-');
        } else if (type == 1) {
            // All negative ones
            int len = rnd.next(1, 8);
            s = string(len, '/');
        } else if (type == 2) {
            // Fully random
            int len = rnd.next(1, 8);
            for (int j = 0; j < len; j++)
                s.push_back(rnd.any(sym));
        } else if (type == 3) {
            // Leading negative, then positives
            int len = rnd.next(2, 8);
            s.push_back('/');
            for (int j = 1; j < len; j++)
                s.push_back(rnd.any(posSym));
        } else {
            // Alternating negative and non-negative
            int len = rnd.next(1, 8);
            for (int j = 0; j < len; j++) {
                if (j % 2 == 0)
                    s.push_back('/');
                else
                    s.push_back(rnd.any(posSym));
            }
        }
        lines.push_back(s);
    }
    // Shuffle order to increase variability
    shuffle(lines.begin(), lines.end());
    for (auto &ln : lines)
        println(ln);
    // Terminator
    println("#");
    return 0;
}
