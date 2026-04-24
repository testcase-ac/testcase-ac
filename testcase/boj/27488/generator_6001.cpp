#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int t = rnd.next(1, 10);
    vector<long long> ns;
    for (int i = 0; i < t; i++) {
        if (i == 0) {
            // always include the smallest edge
            ns.push_back(1);
        } else if (i == 1 && t > 1) {
            // include the largest edge
            ns.push_back(1000000000LL);
        } else {
            double p = rnd.next();
            if (p < 0.2) {
                // pick from some canonical small values
                vector<long long> small = {2, 9, 10, 11, 19, 20, 99};
                ns.push_back(rnd.any(small));
            } else if (p < 0.4) {
                // small random
                ns.push_back(rnd.next(1LL, 100LL));
            } else if (p < 0.6) {
                // medium random
                ns.push_back(rnd.next(101LL, 1000000LL));
            } else if (p < 0.8) {
                // large-ish random
                ns.push_back(rnd.next(1000001LL, 100000000LL));
            } else {
                // repeating-digit numbers like 7777 or 555555
                int d = rnd.next(1, 9);
                int len = rnd.next(1, 9);
                string s(len, char('0' + d));
                long long v = stoll(s);
                if (v > 1000000000LL) v = 999999999LL;
                ns.push_back(v);
            }
        }
    }
    // shuffle test cases for order variability
    shuffle(ns.begin(), ns.end());
    println(t);
    for (auto x : ns) println(x);
    return 0;
}
