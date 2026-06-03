#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static const vector<string> kTypes = {
    "ISTJ", "ISFJ", "INFJ", "INTJ",
    "ISTP", "ISFP", "INFP", "INTP",
    "ESTP", "ESFP", "ENFP", "ENTP",
    "ESTJ", "ESFJ", "ENFJ", "ENTJ",
};

static vector<string> makeCase(int n, int mode) {
    vector<string> people;
    people.reserve(n);

    if (mode == 0) {
        string type = rnd.any(kTypes);
        people.assign(n, type);
    } else if (mode == 1) {
        string a = rnd.any(kTypes);
        string b = rnd.any(kTypes);
        while (b == a) {
            b = rnd.any(kTypes);
        }
        for (int i = 0; i < n; ++i) {
            people.push_back(i % 3 == 0 ? a : b);
        }
    } else if (mode == 2) {
        vector<string> pool = kTypes;
        shuffle(pool.begin(), pool.end());
        int width = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            people.push_back(pool[rnd.next(width)]);
        }
    } else if (mode == 3) {
        vector<string> pool = kTypes;
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < n; ++i) {
            people.push_back(pool[i % pool.size()]);
        }
        shuffle(people.begin(), people.end());
    } else {
        for (int i = 0; i < n; ++i) {
            people.push_back(rnd.any(kTypes));
        }
    }

    return people;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    vector<vector<string>> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(5);
        int n;
        if (mode == 0) {
            n = rnd.next(3, 8);
        } else if (mode == 1) {
            n = rnd.next(3, 20);
        } else if (mode == 2) {
            n = rnd.next(6, 32);
        } else if (mode == 3) {
            n = rnd.next(33, 45);
        } else {
            n = rnd.next(3, 28);
        }
        cases.push_back(makeCase(n, mode));
    }

    println(t);
    for (const auto& people : cases) {
        println((int)people.size());
        println(people);
    }

    return 0;
}
