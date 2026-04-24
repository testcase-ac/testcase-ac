#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of points
    int N = rnd.next(1, 10);

    // decide clustering or uniform distribution for coordinates
    double pCluster = rnd.next(0.0, 1.0);
    int maxRange = (rnd.next() < 0.5 ? rnd.next(10, 100) : rnd.next(500, 1000));
    vector<int> a;
    if (pCluster < 0.5 || N <= 2) {
        // uniform unique
        set<int> S;
        while ((int)S.size() < N) {
            S.insert(rnd.next(0, maxRange));
        }
        a.assign(S.begin(), S.end());
    } else {
        // cluster into k groups
        int k = rnd.next(2, min(N, 3));
        vector<int> sizes(k, N / k);
        for (int i = 0; i < N % k; i++) sizes[i]++;
        int d = max(1, maxRange / 20);
        for (int i = 0; i < k; i++) {
            int center = rnd.next(0, maxRange);
            for (int j = 0; j < sizes[i]; j++) {
                int v = center + rnd.next(-d, d);
                if (v < 0) v = 0;
                if (v > maxRange) v = maxRange;
                a.push_back(v);
            }
        }
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        set<int> S(a.begin(), a.end());
        while ((int)S.size() < N) {
            S.insert(rnd.next(0, maxRange));
        }
        a.assign(S.begin(), S.end());
    }
    sort(a.begin(), a.end());

    // generate widths with varying max width
    vector<int> widthChoices = {10, 100, 1000};
    int hiW = rnd.any(widthChoices);
    vector<int> w(N);
    for (int i = 0; i < N; i++) {
        w[i] = rnd.next(1, hiW);
    }

    // output
    println(N);
    for (int x : a) println(x);
    for (int x : w) println(x);

    return 0;
}
