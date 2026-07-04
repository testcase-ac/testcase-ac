#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

namespace {

string probability(int millionths) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%d.%06d", millionths / 1000000, millionths % 1000000);
    return string(buf);
}

vector<string> makeCase(int mode) {
    int n = rnd.next(1, 12);
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(1, 8);
        values.assign(n, 500000);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) values.push_back(rnd.any(vector<int>{0, 1, 999999, 1000000}));
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(4) == 0) {
                values.push_back(500000);
            } else {
                values.push_back(rnd.next(0, 1000000));
            }
        }
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 6);
        for (int i = 0; i < n / 2; ++i) {
            int x = rnd.next(0, 1000000);
            values.push_back(x);
            values.push_back(1000000 - x);
        }
        shuffle(values.begin(), values.end());
    } else {
        n = rnd.next(8, 18);
        int lo = rnd.next(0, 400000);
        int hi = rnd.next(600000, 1000000);
        for (int i = 0; i < n; ++i) values.push_back(rnd.next(lo, hi));
    }

    vector<string> out;
    for (int value : values) out.push_back(probability(value));
    return out;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        printf("\n");

        vector<string> probabilities = makeCase((tc + rnd.next(5)) % 5);
        println(static_cast<int>(probabilities.size()));
        for (int i = 0; i < static_cast<int>(probabilities.size()); ++i) {
            if (i > 0) printf(" ");
            printf("%s", probabilities[i].c_str());
        }
        printf("\n");
    }

    return 0;
}
