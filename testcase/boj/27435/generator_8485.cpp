#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXN = 1000000000000000000LL;
    vector<long long> qs;

    int scenario = rnd.next(0, 4);

    if (scenario == 0) {
        // Basic & sample-like: many small values, include example Ns
        qs.push_back(1);
        qs.push_back(2);
        qs.push_back(3);
        qs.push_back(4);
        qs.push_back(5);
        qs.push_back(6);
        qs.push_back(7);
        qs.push_back(8);
        qs.push_back(9);
        qs.push_back(10);

        // Explicit sample-related and small mediums
        qs.push_back(6);   // duplicate on purpose
        qs.push_back(12);
        qs.push_back(100);

        // A few random small/medium values
        int extraSmall = rnd.next(2, 5);
        for (int i = 0; i < extraSmall; i++) {
            qs.push_back(rnd.next(1LL, 200LL));
        }

        if (qs.size() < 20) {
            qs.push_back(500);
            qs.push_back(1000);
        }

        // Truncate to keep T small if needed
        if ((int)qs.size() > 20) qs.resize(20);
        shuffle(qs.begin(), qs.end());
    } else if (scenario == 1) {
        // Mixed: small, medium, and up to 1e9
        int T = rnd.next(15, 22);
        for (int i = 0; i < T; i++) {
            int type = rnd.next(0, 2);
            long long n;
            if (type == 0) {
                // small
                n = rnd.next(1LL, 1000LL);
            } else if (type == 1) {
                // medium
                n = rnd.next(1001LL, 1000000LL);
            } else {
                // larger, but not extreme
                n = rnd.next(1000001LL, 1000000000LL);
            }
            qs.push_back(n);
        }
        // Ensure some tiny edge cases present
        qs[0] = 1;
        if (qs.size() > 1) qs[1] = 2;
        if (qs.size() > 2) qs[2] = 3;
        shuffle(qs.begin(), qs.end());
    } else if (scenario == 2) {
        // Include very large values up to 1e18 and a broad range
        qs.push_back(1);
        qs.push_back(2);
        qs.push_back(3);
        qs.push_back(4);
        qs.push_back(5);
        qs.push_back(6);
        qs.push_back(10);
        qs.push_back(100);
        qs.push_back(1000);
        qs.push_back(1000000LL);
        qs.push_back(1000000000LL);
        qs.push_back(1000000000000LL);
        qs.push_back(1000000000000000LL); // 1e15
        qs.push_back(MAXN / 2);
        qs.push_back(MAXN - 5);
        qs.push_back(MAXN);

        int baseT = (int)qs.size();
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; i++) {
            long long n = rnd.next(100000000000000000LL, MAXN);
            qs.push_back(n);
        }

        shuffle(qs.begin(), qs.end());
    } else if (scenario == 3) {
        // Clustered around a few centers + many duplicates
        int T = rnd.next(12, 20);
        long long c1 = rnd.next(10LL, 1000LL);
        long long c2 = rnd.next(100000000LL, 1000000000LL);
        long long c3 = rnd.next(100000000000000000LL, MAXN);

        for (int i = 0; i < T; i++) {
            int cluster = rnd.next(0, 2);
            long long base = (cluster == 0 ? c1 : (cluster == 1 ? c2 : c3));
            long long offset = rnd.next(-5, 5);
            long long n = base + offset;
            if (n < 1) n = 1;
            if (n > MAXN) n = MAXN;
            qs.push_back(n);
        }

        // Introduce some exact duplicates explicitly
        if (!qs.empty()) qs.push_back(qs[0]);
        if (qs.size() > 2) qs.push_back(qs[2]);

        // Keep within limit
        if ((int)qs.size() > 22) qs.resize(22);
        shuffle(qs.begin(), qs.end());
    } else { // scenario == 4
        // Random across full range, bias towards small ones
        int T = rnd.next(5, 15);
        for (int i = 0; i < T; i++) {
            int bucket = rnd.next(0, 9); // 0-9
            long long n;
            if (bucket <= 4) {
                // 50%: very small
                n = rnd.next(1LL, 100LL);
            } else if (bucket <= 6) {
                // 20%: small/medium
                n = rnd.next(101LL, 100000LL);
            } else if (bucket <= 7) {
                // 20%: medium/large
                n = rnd.next(100001LL, 1000000000LL);
            } else {
                // 20%: very large
                n = rnd.next(1000000000000000LL, MAXN);
            }
            qs.push_back(n);
        }
        // Ensure at least one max and one tiny
        qs.push_back(1);
        qs.push_back(MAXN);
        shuffle(qs.begin(), qs.end());
    }

    // Final safety: ensure bounds and size constraints
    for (long long &x : qs) {
        if (x < 1) x = 1;
        if (x > MAXN) x = MAXN;
    }
    if ((int)qs.size() > 25) qs.resize(25);

    int Tfinal = (int)qs.size();
    if (Tfinal == 0) {
        qs.push_back(1);
        Tfinal = 1;
    }

    println(Tfinal);
    for (int i = 0; i < Tfinal; i++) {
        println(qs[i]);
    }

    return 0;
}
