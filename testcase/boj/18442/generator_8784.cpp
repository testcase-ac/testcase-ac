#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pattern;
    if (argc >= 2) {
        pattern = atoi(argv[1]);
        if (pattern < 1 || pattern > 8) pattern = rnd.next(1, 8);
    } else {
        pattern = rnd.next(1, 8);
    }

    int V = 0, P = 0;
    long long L = 0;
    vector<long long> a;

    switch (pattern) {
        case 1: {
            // General random small/medium instance
            V = rnd.next(1, 20);
            P = rnd.next(1, V);
            L = rnd.next((long long)max(2, V + 1), 200LL);
            a.resize(V);
            for (int i = 0; i < V; ++i)
                a[i] = rnd.next(0LL, L - 1);
            sort(a.begin(), a.end());
            break;
        }
        case 2: {
            // P = 1, two far clusters to emphasize circle
            V = rnd.next(5, 20);
            P = 1;
            L = rnd.next(50LL, 1000000000LL);
            a.clear();
            int k = rnd.next(1, V - 1); // count in first cluster
            for (int i = 0; i < k; ++i) {
                long long hi = L / 10;
                if (hi < 0) hi = 0;
                if (hi > L - 1) hi = L - 1;
                a.push_back(rnd.next(0LL, hi));
            }
            for (int i = k; i < V; ++i) {
                long long lo = (L * 9) / 10;
                if (lo < 0) lo = 0;
                if (lo > L - 1) lo = L - 1;
                a.push_back(rnd.next(lo, L - 1));
            }
            sort(a.begin(), a.end());
            break;
        }
        case 3: {
            // P = V, trivial zero-answer case
            V = rnd.next(1, 20);
            P = V;
            L = rnd.next((long long)max(2, V + 1), 200LL);
            a.resize(V);
            for (int i = 0; i < V; ++i)
                a[i] = rnd.next(0LL, L - 1);
            sort(a.begin(), a.end());
            break;
        }
        case 4: {
            // Clustered with duplicates around a few centers
            V = rnd.next(5, 20);
            P = rnd.next(1, V);
            L = rnd.next(30LL, 500LL);
            vector<long long> centers;
            while ((int)centers.size() < 3) {
                long long c = rnd.next(0LL, L - 1);
                bool exists = false;
                for (long long x : centers) if (x == c) { exists = true; break; }
                if (!exists) centers.push_back(c);
            }
            a.clear();
            for (int i = 0; i < V; ++i) {
                long long c = rnd.any(centers);
                long long noise = rnd.next(-2, 2);
                long long pos = c + noise;
                if (pos < 0) pos = 0;
                if (pos >= L) pos = L - 1;
                a.push_back(pos);
            }
            sort(a.begin(), a.end());
            break;
        }
        case 5: {
            // Evenly spaced on line, but last nearly wraps to first
            V = rnd.next(4, 20);
            P = rnd.next(1, V);
            long long step = rnd.next(3, 20);
            a.resize(V);
            for (int i = 0; i < V; ++i)
                a[i] = step * 1LL * i;
            long long last = a.back();
            long long delta = rnd.next(1LL, step - 1);
            L = last + delta;
            // a already sorted
            break;
        }
        case 6: {
            // Several villages at 0, others split near 0 and near L-1
            V = rnd.next(2, 20);
            P = rnd.next(1, V);
            L = rnd.next(10LL, 500LL);
            a.clear();
            int kZeros = rnd.next(1, min(3, V));
            for (int i = 0; i < kZeros; ++i) a.push_back(0);
            for (int i = kZeros; i < V; ++i) {
                int side = rnd.next(0, 1);
                if (side == 0) {
                    long long lo = 1;
                    long long hi = max(1LL, L / 4);
                    if (hi > L - 1) hi = L - 1;
                    if (lo > hi) lo = hi;
                    a.push_back(rnd.next(lo, hi));
                } else {
                    long long lo = (L * 3) / 4;
                    if (lo < 1) lo = 1;
                    long long hi = L - 1;
                    if (lo > hi) lo = hi;
                    a.push_back(rnd.next(lo, hi));
                }
            }
            sort(a.begin(), a.end());
            break;
        }
        case 7: {
            // Fixed small tricky instance
            V = 6;
            P = 2;
            L = 20;
            a = {0, 1, 2, 10, 11, 19};
            sort(a.begin(), a.end());
            break;
        }
        case 8: {
            // Large L near 1e12 to test overflow and circle behavior
            V = rnd.next(10, 20);
            P = rnd.next(1, V);
            const long long MAXL = 1000000000000LL;
            L = MAXL - rnd.next(0LL, 100000000LL); // in [9e11, 1e12]
            a.clear();
            for (int i = 0; i < V; ++i) {
                long long pos;
                if (i < V / 3) {
                    pos = rnd.next(0LL, 1000000LL);
                } else if (i < 2 * V / 3) {
                    long long lo = L / 2;
                    long long hi = lo + 1000000LL;
                    if (hi > L - 1) hi = L - 1;
                    pos = rnd.next(lo, hi);
                } else {
                    long long lo = L - 1000000LL;
                    if (lo < 0) lo = 0;
                    pos = rnd.next(lo, L - 1);
                }
                a.push_back(pos);
            }
            sort(a.begin(), a.end());
            break;
        }
        default:
            break;
    }

    // Ensure constraints
    if (V == 0) {
        V = 1;
        P = 1;
        L = 10;
        a.assign(1, 0);
    }
    if (P < 1) P = 1;
    if (P > V) P = V;
    if ((int)a.size() != V) {
        a.resize(V, 0);
        sort(a.begin(), a.end());
    }

    println(V, P, L);
    for (int i = 0; i < V; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
