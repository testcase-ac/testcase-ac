#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string make_partition_string(int total, int min_parts, int max_parts) {
    // partition total into parts between 1 and 26, with part count in [min_parts,max_parts]
    int max_p = min(max_parts, total); 
    int min_p = min_parts;
    if (min_p > max_p) min_p = max_p;
    int parts = rnd.next(min_p, max_p);
    vector<int> vals(parts);
    int rem = total, slots = parts;
    for (int i = 0; i < parts; i++) {
        if (slots == 1) {
            vals[i] = rem;
        } else {
            int lo = max(1, rem - 26 * (slots - 1));
            int hi = min(26, rem - (slots - 1));
            vals[i] = rnd.next(lo, hi);
        }
        rem -= vals[i];
        slots--;
    }
    // build string and randomly inject spaces
    string s;
    for (int i = 0; i < parts; i++) {
        s += char('A' + vals[i] - 1);
        if (i + 1 < parts && rnd.next() < 0.2) {
            s += ' ';
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of items
    int N = rnd.next(1, 10);

    vector<string> items;
    for (int i = 0; i < N; i++) {
        double mode = rnd.next();
        if (mode < 0.2) {
            // PERFECT LIFE case sum == 100
            items.push_back(make_partition_string(100, 4, 10));
        } else if (mode < 0.4) {
            // small life sum < 20
            int target = rnd.next(1, 19);
            items.push_back(make_partition_string(target, 1, 5));
        } else {
            // random string up to 30 chars
            int L = rnd.next(1, 30);
            string s;
            bool hasLetter = false;
            for (int j = 0; j < L; j++) {
                if (rnd.next() < 0.2) {
                    s += ' ';
                } else {
                    hasLetter = true;
                    s += char('A' + rnd.next(0, 25));
                }
            }
            if (!hasLetter) {
                // ensure at least one letter
                int pos = rnd.next(0, L - 1);
                s[pos] = char('A' + rnd.next(0, 25));
            }
            items.push_back(s);
        }
    }

    // output
    println(N);
    for (auto &s : items) {
        println(s);
    }
    return 0;
}
