#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // length of X: from 1 to 6 digits
    int L = rnd.next(1, 6);
    // mode for diversity
    int mode = rnd.next(0, 3);
    vector<int> d(L);
    if (mode == 0) {
        // random digits, ensuring no leading zero
        for (int i = 0; i < L; i++) {
            if (i == 0) d[i] = rnd.next(1, 9);
            else d[i] = rnd.next(0, 9);
        }
    } else if (mode == 1) {
        // no next permutation: digits sorted descending
        // generate random then sort descending
        for (int i = 0; i < L; i++) {
            if (i == 0) d[i] = rnd.next(1, 9);
            else d[i] = rnd.next(0, 9);
        }
        sort(d.begin(), d.end(), greater<int>());
        // ensure first is not zero (shouldn't happen but safe)
        if (d[0] == 0) {
            for (int i = 1; i < L; i++) {
                if (d[i] != 0) {
                    swap(d[0], d[i]);
                    break;
                }
            }
        }
    } else if (mode == 2) {
        // guaranteed next exists: ascending with at least two distinct
        if (L == 1) {
            d[0] = rnd.next(1, 9);
        } else {
            do {
                for (int i = 0; i < L; i++)
                    d[i] = rnd.next(1, 9);
                sort(d.begin(), d.end());
            } while (d.front() == d.back());
        }
    } else {
        // mode 3: random but force next_permutation exists if possible
        if (L == 1) {
            d[0] = rnd.next(1, 9);
        } else {
            while (true) {
                for (int i = 0; i < L; i++) {
                    if (i == 0) d[i] = rnd.next(1, 9);
                    else d[i] = rnd.next(0, 9);
                }
                auto cp = d;
                if (next_permutation(cp.begin(), cp.end())) break;
            }
        }
    }
    // build number string
    string s;
    s.reserve(L);
    for (int x : d) s.push_back(char('0' + x));
    // output
    println(s);
    return 0;
}
