#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test sequences
    int T = rnd.next(5, 12);
    vector<char> faces = {'F','B','U','D','L','R'};

    for (int ti = 0; ti < T; ti++) {
        // Choose a pattern type for variability
        int type = rnd.next(0, 3);
        int L;
        // Different length distributions for each type
        if (type == 0) {
            // very short sequences
            L = rnd.next(1, 3);
        } else if (type == 1) {
            // moderate sequences
            L = rnd.next(4, 8);
        } else if (type == 2) {
            // long sequences
            L = rnd.next(20, 80);
        } else {
            // any length
            L = rnd.next(1, 80);
        }

        string s;
        if (type == 1) {
            // single-move repetition, e.g., "AAAAA" or "r r r"
            char mv = rnd.any(faces);
            bool lower = rnd.next(0, 1);
            if (lower) mv = char(tolower(mv));
            s = string(L, mv);
        } else if (type == 2) {
            // repeat a small pattern, e.g., "FRfrFRfr..."
            int p = rnd.next(2, 5);
            string pat;
            for (int i = 0; i < p; i++) {
                char mv = rnd.any(faces);
                if (rnd.next(0, 1)) mv = char(tolower(mv));
                pat.push_back(mv);
            }
            for (int i = 0; i < L; i++)
                s.push_back(pat[i % p]);
        } else {
            // fully random sequence
            for (int i = 0; i < L; i++) {
                char mv = rnd.any(faces);
                if (rnd.next(0, 1)) mv = char(tolower(mv));
                s.push_back(mv);
            }
        }
        // Output the generated move sequence
        printf("%s\n", s.c_str());
    }
    return 0;
}
