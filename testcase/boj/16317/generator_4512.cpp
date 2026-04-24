#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of dirty pushes
    int n = rnd.next(1, 10);
    // Choose mode: 0=uniform, 1=early cluster, 2=late cluster, 3=two clusters, 4=extreme ends
    int modeMax = (n == 1 ? 2 : 4);
    int mode = rnd.next(0, modeMax);

    vector<int> days;

    switch (mode) {
    case 1: {
        // Early cluster
        int base = rnd.next(1, 180);
        int width = rnd.next(n, min(20, 365));
        int lo = max(1, base - width);
        int hi = min(365, base + width);
        if (hi - lo + 1 < n) {
            lo = 1;
            hi = 365;
        }
        vector<int> pool;
        for (int d = lo; d <= hi; d++) pool.push_back(d);
        shuffle(pool.begin(), pool.end());
        days.assign(pool.begin(), pool.begin() + n);
        break;
    }
    case 2: {
        // Late cluster
        int base = rnd.next(186, 365);
        int width = rnd.next(n, min(20, 365));
        int lo = max(1, base - width);
        int hi = min(365, base + width);
        if (hi - lo + 1 < n) {
            lo = 1;
            hi = 365;
        }
        vector<int> pool;
        for (int d = lo; d <= hi; d++) pool.push_back(d);
        shuffle(pool.begin(), pool.end());
        days.assign(pool.begin(), pool.begin() + n);
        break;
    }
    case 3: {
        // Two clusters
        int k = rnd.next(1, n - 1);
        int k2 = n - k;
        // Cluster 1: early
        int base1 = rnd.next(1, 150);
        int width1 = rnd.next(k, min(20, 365));
        int lo1 = max(1, base1 - width1);
        int hi1 = min(365, base1 + width1);
        if (hi1 - lo1 + 1 < k) {
            lo1 = 1; hi1 = 365;
        }
        vector<int> pool1;
        for (int d = lo1; d <= hi1; d++) pool1.push_back(d);
        shuffle(pool1.begin(), pool1.end());
        days.insert(days.end(), pool1.begin(), pool1.begin() + k);
        // Cluster 2: late
        int base2 = rnd.next(216, 365);
        int width2 = rnd.next(k2, min(20, 365));
        int lo2 = max(1, base2 - width2);
        int hi2 = min(365, base2 + width2);
        if (hi2 - lo2 + 1 < k2) {
            lo2 = 1; hi2 = 365;
        }
        vector<int> pool2;
        for (int d = lo2; d <= hi2; d++) pool2.push_back(d);
        shuffle(pool2.begin(), pool2.end());
        days.insert(days.end(), pool2.begin(), pool2.begin() + k2);
        break;
    }
    case 4: {
        // Always include ends 1 and 365
        if (n >= 2) {
            days.push_back(1);
            days.push_back(365);
            int rem = n - 2;
            if (rem > 0) {
                vector<int> pool;
                for (int d = 2; d <= 364; d++) pool.push_back(d);
                shuffle(pool.begin(), pool.end());
                for (int i = 0; i < rem; i++)
                    days.push_back(pool[i]);
            }
            break;
        }
        // Fallback to uniform if n < 2
        [[fallthrough]];
    }
    default: {
        // Uniform random days from 1..365
        vector<int> pool(365);
        for (int i = 0; i < 365; i++) pool[i] = i + 1;
        shuffle(pool.begin(), pool.end());
        days.assign(pool.begin(), pool.begin() + n);
        break;
    }
    }

    sort(days.begin(), days.end());
    // Output
    println(n);
    println(days);

    return 0;
}
