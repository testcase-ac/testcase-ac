#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> biases = {-1, 0, 1};
    vector<long long> maxvals = {100, 1000, 1000000, 1999999999LL};

    int Tbias = rnd.any(biases);
    int T = rnd.wnext(5, Tbias) + 1;
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int pbias = rnd.any(biases);
        int p = rnd.wnext(10, pbias) + 1;

        long long maxPrice = rnd.any(maxvals);
        set<long long> used;
        vector<long long> prices;
        while ((int)prices.size() < p) {
            long long x = rnd.next(1LL, maxPrice);
            if (!used.count(x)) {
                used.insert(x);
                prices.push_back(x);
            }
        }

        int alph = rnd.next(3, 26);
        vector<string> names;
        for (int i = 0; i < p; i++) {
            int lbias = rnd.any(biases);
            int len = rnd.wnext(10, lbias) + 1;
            string s;
            for (int j = 0; j < len; j++) {
                char c = char('a' + rnd.next(0, alph - 1));
                s.push_back(c);
            }
            names.push_back(s);
        }

        vector<int> ids(p);
        iota(ids.begin(), ids.end(), 0);
        shuffle(ids.begin(), ids.end());

        println(p);
        for (int idx : ids) {
            println(prices[idx], names[idx]);
        }
    }
    return 0;
}
