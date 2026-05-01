#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int scenario = rnd.next(0, 6);

    if (scenario == 0) {
        // Very small, hand-crafted interesting patterns
        vector<string> cand = {
            "M", "K",
            "MM", "MK", "KM", "KK",
            "MMK", "MKM", "MKK", "KMM",
            "MKKM", "KMKMK", "MMMK", "MKMM", "KKM"
        };
        s = rnd.any(cand);
    } else if (scenario == 1) {
        // Only M's
        int L = rnd.next(1, 30);
        s.assign(L, 'M');
    } else if (scenario == 2) {
        // Only K's
        int L = rnd.next(1, 30);
        s.assign(L, 'K');
    } else if (scenario == 3) {
        // Repeated pattern: M^a optionally followed by K
        int L = rnd.next(5, 50);
        while ((int)s.size() < L) {
            int rem = L - (int)s.size();
            int mlen = rnd.next(1, min(5, rem));
            s.append(mlen, 'M');
            rem = L - (int)s.size();
            if (rem > 0 && rnd.next(0, 1)) {
                s.push_back('K');
            }
        }
    } else if (scenario == 4) {
        // Completely random string of M and K
        int L = rnd.next(1, 80);
        s.reserve(L);
        for (int i = 0; i < L; ++i) {
            s.push_back(rnd.next(0, 1) == 0 ? 'M' : 'K');
        }
    } else if (scenario == 5) {
        // Alternating pattern
        int L = rnd.next(2, 60);
        char first = rnd.next(0, 1) == 0 ? 'M' : 'K';
        char second = (first == 'M' ? 'K' : 'M');
        s.reserve(L);
        for (int i = 0; i < L; ++i) {
            s.push_back((i % 2 == 0) ? first : second);
        }
    } else {
        // Mixed segments: M-run, M-run + K, or K-run
        int L = rnd.next(10, 80);
        while ((int)s.size() < L) {
            int rem = L - (int)s.size();
            int typeSeg = rnd.next(0, 2); // 0,1,2

            if (typeSeg == 0) {
                // M-run
                int lenM = rnd.next(1, min(4, rem));
                s.append(lenM, 'M');
            } else if (typeSeg == 1) {
                // M-run (possibly zero) + K
                if (rem == 1) {
                    s.push_back('K');
                } else {
                    int maxM = min(3, rem - 1);
                    int lenM = rnd.next(0, maxM);
                    if (lenM > 0) s.append(lenM, 'M');
                    s.push_back('K');
                }
            } else {
                // K-run
                int lenK = rnd.next(1, min(3, rem));
                s.append(lenK, 'K');
            }
        }
    }

    println(s);
    return 0;
}
