#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of customers
    int N = rnd.next(1, 10);
    vector<int> tips(N);

    // Hyper-parameter: pick a pattern for diversity
    vector<string> types = {
        "random", "equal", "smallRange", "bigRange",
        "almostSmall", "asc", "desc", "sawtooth"
    };
    string type = rnd.any(types);

    if (type == "random") {
        for (int i = 0; i < N; i++)
            tips[i] = rnd.next(1, 20);
    }
    else if (type == "equal") {
        int v = rnd.next(1, 20);
        for (int i = 0; i < N; i++)
            tips[i] = v;
    }
    else if (type == "smallRange") {
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, 10);
        for (int i = 0; i < N; i++)
            tips[i] = rnd.next(lo, hi);
    }
    else if (type == "bigRange") {
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 100000);
        for (int i = 0; i < N; i++)
            tips[i] = rnd.next(lo, hi);
    }
    else if (type == "almostSmall") {
        if (N >= 2) {
            for (int i = 0; i < N-1; i++)
                tips[i] = rnd.next(1, 3);
            tips[N-1] = rnd.next(10, 100);
            shuffle(tips.begin(), tips.end());
        } else {
            tips[0] = rnd.next(1, 100);
        }
    }
    else if (type == "asc" || type == "desc") {
        for (int i = 0; i < N; i++)
            tips[i] = rnd.next(1, 100);
        sort(tips.begin(), tips.end());
        if (type == "desc")
            reverse(tips.begin(), tips.end());
    }
    else if (type == "sawtooth") {
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) tips[i] = rnd.next(1, 5);
            else tips[i] = rnd.next(10, 20);
        }
    }

    // Output in required format
    println(N);
    for (int x : tips)
        println(x);

    return 0;
}
