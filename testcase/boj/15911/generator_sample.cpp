#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

namespace {

string fixedProbability(int millionths) {
    if (rnd.next(0, 4) == 0) {
        if (millionths == 0) return "0";
        if (millionths == 1000000) return "1";
    }

    string s = to_string(millionths);
    while (s.size() < 7) s = "0" + s;
    return s.substr(0, 1) + "." + s.substr(1, 6);
}

string randomProbability(int mode) {
    if (mode == 0) {
        return fixedProbability(rnd.any(vector<int>{0, 1, 499999, 500000,
                                                   500001, 999999, 1000000}));
    }
    if (mode == 1) {
        return fixedProbability(rnd.next(495000, 505000));
    }
    if (mode == 2) {
        return fixedProbability(rnd.next(0, 1000000));
    }

    int numerator = rnd.next(0, 10);
    return fixedProbability(numerator * 100000);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 0;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(0, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(0, 12);
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        m = rnd.next(10, 40);
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        m = rnd.next(20, 80);
    } else {
        n = rnd.next(20, 60);
        m = rnd.next(0, 120);
    }

    vector<string> initial;
    for (int i = 0; i < n; ++i) {
        int probabilityMode = mode;
        if (mode == 3 && rnd.next(0, 2) != 0) probabilityMode = 0;
        if (mode == 4) probabilityMode = rnd.next(0, 3);
        initial.push_back(randomProbability(probabilityMode));
    }

    println(n, m);
    println(initial);

    int stickyCoin = rnd.next(1, n);
    for (int i = 0; i < m; ++i) {
        int coin = rnd.next(1, n);
        if (mode == 3 && rnd.next(0, 3) != 0) coin = stickyCoin;
        if (mode == 0 && rnd.next(0, 1) == 0) coin = 1;

        int probabilityMode = mode;
        if (mode == 4) probabilityMode = rnd.next(0, 3);
        println(coin, randomProbability(probabilityMode));
    }

    return 0;
}
