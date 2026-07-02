#include "testlib.h"
#include <algorithm>
#include <cstdio>
#include <set>
#include <string>
#include <vector>
using namespace std;

string massToken(int value) {
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "0.%05d", value);
    return string(buffer);
}

vector<int> takeUnique(set<int>& used, int low, int high, int count) {
    vector<int> values;
    for (int attempts = 0; values.size() < static_cast<size_t>(count) && attempts < 10000; ++attempts) {
        int value = rnd.next(low, high);
        if (used.insert(value).second) {
            values.push_back(value);
        }
    }
    for (int value = low; values.size() < static_cast<size_t>(count) && value <= high; ++value) {
        if (used.insert(value).second) {
            values.push_back(value);
        }
    }
    return values;
}

void printMasses(const vector<int>& values) {
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%s", massToken(values[i]).c_str());
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n = rnd.next(1, 12);
        set<int> used;
        vector<int> naomi;
        vector<int> ken;

        if (mode == 0) {
            naomi = takeUnique(used, 1, 99999, n);
            ken = takeUnique(used, 1, 99999, n);
        } else if (mode == 1) {
            naomi = takeUnique(used, 50000, 99999, n);
            ken = takeUnique(used, 1, 49999, n);
        } else if (mode == 2) {
            naomi = takeUnique(used, 1, 49999, n);
            ken = takeUnique(used, 50000, 99999, n);
        } else if (mode == 3) {
            int start = rnd.next(1, 99999 - 2 * n);
            for (int i = 0; i < n; ++i) {
                naomi.push_back(start + 2 * i);
                ken.push_back(start + 2 * i + 1);
            }
        } else {
            int center = rnd.next(50, 99950);
            naomi = takeUnique(used, max(1, center - 40), min(99999, center + 40), n);
            ken = takeUnique(used, max(1, center - 40), min(99999, center + 40), n);
        }

        shuffle(naomi.begin(), naomi.end());
        shuffle(ken.begin(), ken.end());

        println(n);
        printMasses(naomi);
        printMasses(ken);
    }

    return 0;
}
