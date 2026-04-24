#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    // Read goods values
    vector<int> goods = inf.readInts(n, 1, 1000000000, "goods");
    inf.readEoln();

    // Read price tags
    vector<int> prices = inf.readInts(n, 1, 1000000000, "prices");
    inf.readEoln();

    // Check that all goods are distinct
    {
        vector<int> tmp = goods;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < n; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate goods detected: %d at positions %d and %d",
                    tmp[i], i-1, i);
        }
    }

    // Check that all prices are distinct
    {
        vector<int> tmp = prices;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < n; i++) {
            ensuref(tmp[i] != tmp[i-1],
                    "Duplicate prices detected: %d at positions %d and %d",
                    tmp[i], i-1, i);
        }
    }

    inf.readEof();
    return 0;
}
