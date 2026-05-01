#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of serials: small to moderate for manual verification
    int N = rnd.next(1, 15);

    set<string> used;
    vector<string> serials;

    while ((int)serials.size() < N) {
        // Choose length: mostly small, occasionally medium or long
        int L;
        int p = rnd.next(0, 3);
        if (p == 0)       L = rnd.next(20, 50);
        else if (p == 1)  L = rnd.next(6, 20);
        else              L = rnd.next(1, 5);

        // Decide how many digits to include to cover edge cases
        int k;
        int t = rnd.next(0, 3);
        if (t == 0)             k = 0;                 // pure letters
        else if (t == 1)        k = L;                 // pure digits
        else if (t == 2)        k = rnd.next(1, min(3, L));          // few digits
        else                    k = rnd.next(max(0, L-3), L-1);    // many digits but mixed

        // pick k distinct positions for digits
        vector<int> pos(L);
        for (int i = 0; i < L; i++) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        set<int> digitPos(pos.begin(), pos.begin() + k);

        // build the serial
        string s;
        s.reserve(L);
        for (int i = 0; i < L; i++) {
            if (digitPos.count(i)) {
                char d = char('0' + rnd.next(0, 9));
                s.push_back(d);
            } else {
                char c = char('A' + rnd.next(0, 25));
                s.push_back(c);
            }
        }

        if (!used.count(s)) {
            used.insert(s);
            serials.push_back(s);
        }
    }

    // Shuffle the list so order is random
    shuffle(serials.begin(), serials.end());

    // Output
    println(N);
    for (auto &s : serials) println(s);

    return 0;
}
