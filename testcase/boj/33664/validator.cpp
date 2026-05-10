#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read B, N, M
    long long B = inf.readLong(0LL, 1000000000000000000LL, "B");
    inf.readSpace();
    int N = inf.readInt(1, 2800, "N");
    inf.readSpace();
    int M = inf.readInt(1, 280, "M");
    // M must also satisfy M <= N
    ensuref(M <= N, "M (%d) must be <= N (%d)", M, N);
    inf.readEoln();

    // Read N items: name and price
    set<string> itemNames;
    __int128 sumPrices = 0;
    for (int i = 0; i < N; i++) {
        // item name: only letters, length 1..15
        string name = inf.readToken("[A-Za-z]{1,15}", "item_name");
        inf.readSpace();
        long long p = inf.readLong(0LL, 1000000000000000000LL, "price");
        inf.readEoln();

        // name must be unique
        auto res = itemNames.insert(name);
        ensuref(res.second, "Duplicate item name at index %d: %s", i, name.c_str());

        // accumulate sum
        sumPrices += p;
    }
    // sum of prices must not exceed 2e18
    const __int128 LIMIT = ( (__int128)2000000000000000000LL );
    ensuref(sumPrices <= LIMIT,
            "Sum of all item prices exceeds 2e18: %lld",
            (long long)sumPrices);

    // Read M purchase names
    set<string> bought;
    for (int i = 0; i < M; i++) {
        string jname = inf.readToken("[A-Za-z]{1,15}", "buy_name");
        inf.readEoln();
        // must refer to an existing item
        ensuref(itemNames.count(jname),
                "Purchase name at index %d not found in item list: %s", i, jname.c_str());
        // must be unique among purchases
        auto res2 = bought.insert(jname);
        ensuref(res2.second,
                "Duplicate purchase name at index %d: %s", i, jname.c_str());
    }

    inf.readEof();
    return 0;
}
