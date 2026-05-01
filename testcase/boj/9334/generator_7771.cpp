#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(5, 10);
    println(T);
    for (int ti = 0; ti < T; ++ti) {
        int id = rnd.next(0, 5);
        int n;
        vector<int> f;
        while (true) {
            if (id == 0) {
                // constant sequence: f[n] = k
                n = rnd.next(8, 12);
                int k = rnd.next(-10, 10);
                if (k == 0) k = 1;
                f.assign(n, k);
            } else if (id == 1) {
                // alternating: f[n] = (-1) * f[n-1]
                n = rnd.next(8, 12);
                int k = rnd.next(-10, 10);
                if (k == 0) k = -1;
                f.resize(n);
                for (int i = 0; i < n; ++i)
                    f[i] = ((i % 2) ? -k : k);
            } else if (id == 2) {
                // powers of base 2 or -2
                n = rnd.next(8, 10);
                int b = rnd.any(vector<int>{2, -2});
                f.resize(n);
                f[0] = 1;
                for (int i = 1; i < n; ++i)
                    f[i] = f[i-1] * b;
            } else if (id == 3) {
                // arithmetic progression via recurrence f[n]=2f[n-1]-f[n-2]
                n = rnd.next(8, 12);
                int f1 = rnd.next(-10, 10); if (f1 == 0) f1 = 1;
                int c = rnd.next(-10, 10); if (c == 0) c = 1;
                int f2 = f1 + c;
                if (f2 == 0) { continue; }
                f.resize(n);
                f[0] = f1; f[1] = f2;
                for (int i = 2; i < n; ++i)
                    f[i] = 2*f[i-1] - f[i-2];
            } else if (id == 4) {
                // fibonacci-like
                n = rnd.next(8, 12);
                int f1 = rnd.next(-5, 5); if (f1 == 0) f1 = 1;
                int f2 = rnd.next(-5, 5); if (f2 == 0) f2 = -1;
                f.resize(n);
                f[0] = f1; f[1] = f2;
                for (int i = 2; i < n; ++i)
                    f[i] = f[i-1] + f[i-2];
            } else {
                // generic random recurrence
                n = rnd.next(8, 12);
                int d = rnd.next(1, 3);
                vector<int> a(d);
                for (int i = 0; i < d; ++i)
                    a[i] = rnd.next(-2, 2);
                if (a[d-1] == 0)
                    a[d-1] = rnd.any(vector<int>{-2, -1, 1, 2});
                int sumabs = 0;
                for (int x : a) sumabs += abs(x);
                if (sumabs < 1 || sumabs > 3) continue;
                f.assign(n, 0);
                for (int i = 0; i < d; ++i) {
                    int v = rnd.next(-5, 5);
                    if (v == 0) v = 1;
                    f[i] = v;
                }
                bool ok = true;
                for (int i = d; i < n; ++i) {
                    long long s = 0;
                    for (int j = 0; j < d; ++j)
                        s += (long long)a[j] * f[i-j-1];
                    if (abs(s) > 1000) { ok = false; break; }
                    f[i] = (int)s;
                }
                if (!ok) continue;
            }
            // verify bounds
            bool valid = true;
            for (int x : f)
                if (abs(x) > 1000) { valid = false; break; }
            if (!valid) continue;
            // ensure first d terms non-zero
            int d_check = 1;
            if (id == 3 || id == 4) d_check = 2;
            if (id == 5) {
                // need to recompute d for generic
                // but generic ensures first d non-zero already
            }
            for (int i = 0; i < min((int)f.size(), d_check); ++i)
                if (f[i] == 0) valid = false;
            if (!valid) continue;
            break;
        }
        vector<int> out;
        out.push_back((int)f.size());
        for (int v : f) out.push_back(v);
        println(out);
    }
    return 0;
}
