#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: alphabet size
    int alpha_k = rnd.next(3, 26);
    // Target string length
    int L = rnd.next(1, 10);
    // Generate target string
    string t;
    for (int i = 0; i < L; i++) {
        t += char('A' + rnd.next(0, alpha_k - 1));
    }
    // Number of rings
    int N = rnd.next(1, 10);
    // Probability a ring contains the target
    double p_match = rnd.next(0.0, 1.0);

    vector<string> rings;
    for (int i = 0; i < N; i++) {
        bool want = rnd.next() < p_match;
        string s;
        if (want) {
            // generate a ring that contains t (circularly)
            s = string(10, '?');
            // fill with random chars
            for (int j = 0; j < 10; j++)
                s[j] = char('A' + rnd.next(0, alpha_k - 1));
            // insert t at random circular position
            int pos = rnd.next(0, 9);
            for (int j = 0; j < L; j++)
                s[(pos + j) % 10] = t[j];
        } else {
            // generate a ring that does NOT contain t (circularly)
            while (true) {
                s.clear();
                for (int j = 0; j < 10; j++)
                    s += char('A' + rnd.next(0, alpha_k - 1));
                string dbl = s + s;
                if (dbl.find(t) == string::npos) break;
            }
        }
        rings.push_back(s);
    }
    // randomize order
    shuffle(rings.begin(), rings.end());

    // Output
    printf("%s\n", t.c_str());
    println(N);
    for (auto &s : rings)
        printf("%s\n", s.c_str());

    return 0;
}
