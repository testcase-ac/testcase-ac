#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Fixed 6-bit patterns for A-H
    vector<string> pat = {
        "000000", // A
        "001111", // B
        "010011", // C
        "011100", // D
        "100110", // E
        "101001", // F
        "110101", // G
        "111010"  // H
    };

    // Number of letters
    int n = rnd.next(1, 9);

    vector<string> segs;
    segs.reserve(n);

    for (int i = 0; i < n; i++) {
        int base = rnd.next(0, 7);
        int type = rnd.next(0, 2);
        string s = pat[base];

        if (type == 1) {
            // Introduce exactly one bit error
            int pos = rnd.next(0, 5);
            s[pos] = (s[pos] == '0' ? '1' : '0');
        } else if (type == 2) {
            // Create an ambiguous pattern: >=2 bits differ from every letter
            string t;
            while (true) {
                t.clear();
                for (int j = 0; j < 6; j++)
                    t.push_back(char('0' + rnd.next(0, 1)));
                bool ok = true;
                for (auto &p : pat) {
                    int d = 0;
                    for (int j = 0; j < 6; j++)
                        if (t[j] != p[j]) d++;
                    if (d < 2) { ok = false; break; }
                }
                if (ok) break;
            }
            s = t;
        }
        segs.push_back(s);
    }

    // Flatten segments to one bitstring
    string bits;
    for (auto &s : segs) bits += s;

    // Output
    println(n);
    println(bits);

    return 0;
}
