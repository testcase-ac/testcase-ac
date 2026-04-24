#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // maximum base length
        int maxL = rnd.next(1, 10);
        vector<string> w(3);
        // generate three distinct sorted base words
        while (true) {
            for (int i = 0; i < 3; i++) {
                int L = rnd.next(1, maxL);
                string s;
                s.reserve(L);
                for (int j = 0; j < L; j++) {
                    s.push_back(char('a' + rnd.next(0, 25)));
                }
                w[i] = s;
            }
            vector<string> ord = w;
            sort(ord.begin(), ord.end());
            if (ord[0] != ord[1] && ord[1] != ord[2]) {
                w = ord;
                break;
            }
        }
        // probability of a question mark
        double p = rnd.next(0.0, 1.0);
        // introduce '?' randomly
        for (int i = 0; i < 3; i++) {
            string &s = w[i];
            for (int j = 0; j < (int)s.size(); j++) {
                if (rnd.next() < p) {
                    s[j] = '?';
                }
            }
            println(s);
        }
    }
    return 0;
}
