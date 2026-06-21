#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using Person = pair<int, int>;

Person makePerson(int s, int h) {
    return {s, h};
}

Person randomPerson(int sLo, int sHi, int gapLo, int gapHi) {
    int s = rnd.next(sLo, sHi);
    int maxGap = min(gapHi, 10000 - s);
    int gap = rnd.next(gapLo, maxGap);
    return makePerson(s, s + gap);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Person> people;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(2, 8);
        people.push_back(makePerson(1, 2));
        people.push_back(makePerson(9999, 10000));
        while ((int)people.size() < n) {
            people.push_back(randomPerson(1, 9999, 1, 10000));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        int h = rnd.next(2, 10000);
        for (int i = 0; i < n; ++i) {
            int s = rnd.next(max(1, h - 20), h - 1);
            people.push_back(makePerson(s, h));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 14);
        int s = rnd.next(1, 9999);
        for (int i = 0; i < n; ++i) {
            int h = rnd.next(s + 1, min(10000, s + 30));
            people.push_back(makePerson(s, h));
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 20);
        int start = rnd.next(1, 10000 - n - 1);
        for (int i = 0; i < n; ++i) {
            int s = start + i;
            people.push_back(makePerson(s, s + rnd.next(1, 3)));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 18);
        int low = rnd.next(1, 200);
        int high = rnd.next(9800, 10000);
        for (int i = 0; i < n; ++i) {
            int s = min(9999, low + rnd.next(0, i * 3 + 10));
            int h = max(s + 1, high - rnd.next(0, i * 4 + 20));
            people.push_back(makePerson(s, h));
        }
    } else {
        int n = rnd.next(2, 30);
        int sLo = rnd.next(1, 8000);
        int sHi = rnd.next(sLo, 9999);
        for (int i = 0; i < n; ++i) {
            people.push_back(randomPerson(sLo, sHi, 1, 10000));
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(people.begin(), people.end());
    }

    println((int)people.size());
    for (const Person& person : people) {
        println(person.first, person.second);
    }

    return 0;
}
