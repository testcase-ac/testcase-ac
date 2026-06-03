#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Person {
    int solved;
    int codeforces;
    int atcoder;
    int regionalRank;
};

int nearValue(int threshold, int low, int high) {
    int delta = rnd.next(-3, 3);
    return clamp(threshold + delta, low, high);
}

Person makePerson(int mode) {
    int solved = rnd.next(0, 100000);
    int codeforces = rnd.next(0, 4000);
    int atcoder = rnd.next(0, 4000);
    int regionalRank = rnd.next(0, 4) == 0 ? -1 : rnd.next(1, 200);

    if (mode == 0) {
        solved = nearValue(1000, 0, 100000);
        codeforces = rnd.next(0, 1599);
        atcoder = rnd.next(0, 1499);
        regionalRank = rnd.next(0, 1) == 0 ? -1 : rnd.next(31, 200);
    } else if (mode == 1) {
        solved = rnd.next(0, 999);
        codeforces = nearValue(1600, 0, 4000);
        atcoder = rnd.next(0, 1499);
        regionalRank = rnd.next(0, 1) == 0 ? -1 : rnd.next(31, 200);
    } else if (mode == 2) {
        solved = rnd.next(0, 999);
        codeforces = rnd.next(0, 1599);
        atcoder = nearValue(1500, 0, 4000);
        regionalRank = rnd.next(0, 1) == 0 ? -1 : rnd.next(31, 200);
    } else if (mode == 3) {
        solved = rnd.next(0, 999);
        codeforces = rnd.next(0, 1599);
        atcoder = rnd.next(0, 1499);
        regionalRank = rnd.next(1, 35);
    } else if (mode == 4) {
        solved = rnd.next(0, 999);
        codeforces = rnd.next(0, 1599);
        atcoder = rnd.next(0, 1499);
        regionalRank = rnd.next(0, 1) == 0 ? -1 : rnd.next(31, 200);
    } else {
        solved = rnd.next(0, 1) ? rnd.next(1000, 100000) : rnd.next(0, 999);
        codeforces = rnd.next(0, 1) ? rnd.next(1600, 4000) : rnd.next(0, 1599);
        atcoder = rnd.next(0, 1) ? rnd.next(1500, 4000) : rnd.next(0, 1499);
        regionalRank = rnd.next(0, 2) == 0 ? rnd.next(1, 30) : (rnd.next(0, 1) == 0 ? -1 : rnd.next(31, 200));
    }

    return {solved, codeforces, atcoder, regionalRank};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n = 1;
    if (sizeMode == 0) {
        n = rnd.next(1, 5);
    } else if (sizeMode == 1) {
        n = rnd.next(6, 20);
    } else if (sizeMode == 2) {
        n = rnd.next(21, 60);
    } else {
        n = rnd.next(61, 100);
    }

    vector<Person> people;
    people.reserve(n);
    for (int i = 0; i < n; ++i) {
        people.push_back(makePerson(rnd.next(0, 5)));
    }

    shuffle(people.begin(), people.end());

    println(n);
    for (const Person& person : people) {
        println(person.solved, person.codeforces, person.atcoder, person.regionalRank);
    }

    return 0;
}
