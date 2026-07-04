#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string probabilityToken(long long millionths) {
    if (millionths == 1000000) {
        return rnd.next(0, 1) == 0 ? "1" : "1.0";
    }
    if (millionths == 500000 && rnd.next(0, 1) == 0) {
        return "0.5";
    }

    string fraction = to_string(millionths);
    while (fraction.size() < 6) {
        fraction = "0" + fraction;
    }
    while (!fraction.empty() && fraction.back() == '0') {
        fraction.pop_back();
    }
    return "0." + fraction;
}

long long randomProbability(int mode) {
    if (mode == 0) {
        return rnd.any(vector<long long>{500000, 1000000});
    }
    if (mode == 1) {
        return rnd.any(vector<long long>{500000, 500001, 999999, 1000000});
    }
    if (mode == 2) {
        return rnd.next(500000, 600000);
    }
    if (mode == 3) {
        return rnd.next(900000, 1000000);
    }
    if (mode == 4) {
        return rnd.next(500000, 1000000);
    }

    vector<long long> values = {500000, 500001, 625000, 750000, 875000, 900000, 999999, 1000000};
    return rnd.any(values);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 8);
    } else if (mode <= 5) {
        n = rnd.next(9, 40);
    } else if (mode == 6) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.any(vector<int>{4995, 4999, 5000});
    }

    int k = rnd.next(1, n);
    if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = n;
    } else if (mode == 3) {
        k = (n + 1) / 2;
    } else if (mode == 7) {
        k = rnd.any(vector<int>{1, n / 2, n});
    }

    vector<string> probabilities;
    for (int i = 0; i < n; ++i) {
        long long value = randomProbability(mode);
        if (mode == 5 && i % 3 == 0) {
            value = rnd.any(vector<long long>{500000, 1000000});
        }
        probabilities.push_back(probabilityToken(value));
    }

    println(n, k);
    println(probabilities);
    return 0;
}
