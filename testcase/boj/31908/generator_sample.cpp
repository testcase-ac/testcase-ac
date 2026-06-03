#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 0;
    vector<pair<string, string>> people;

    auto addPerson = [&](const string& ring) {
        string name = "p" + to_string((int)people.size() + 1);
        people.push_back({name, ring});
    };

    auto addRingGroup = [&](int ringIndex, int count) {
        string ring = "r" + to_string(ringIndex);
        for (int i = 0; i < count; ++i) {
            addPerson(ring);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            addPerson("-");
        }
    } else if (mode == 1) {
        n = rnd.next(2, 14);
        int ringIndex = 1;
        while ((int)people.size() < n) {
            int remaining = n - (int)people.size();
            int count = rnd.next(1, min(2, remaining));
            addRingGroup(ringIndex++, count);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        int ringIndex = 1;
        while ((int)people.size() < n) {
            int remaining = n - (int)people.size();
            int count = min(remaining, rnd.next(1, 4));
            addRingGroup(ringIndex++, count);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 25);
        int ringIndex = 1;
        while ((int)people.size() + 3 <= n && rnd.next(3)) {
            addRingGroup(ringIndex++, 3);
        }
        while ((int)people.size() < n) {
            int remaining = n - (int)people.size();
            int count = rnd.next(remaining == 1 ? 1 : 2, min(4, remaining));
            addRingGroup(ringIndex++, count);
        }
    } else {
        n = rnd.next(10, 30);
        int ringIndex = 1;
        while ((int)people.size() < n) {
            int remaining = n - (int)people.size();
            int choice = rnd.next(100);
            if (choice < 20) {
                addPerson("-");
            } else {
                int count = 1;
                if (choice >= 45 && remaining >= 2) count = 2;
                if (choice >= 75 && remaining >= 3) count = rnd.next(3, min(5, remaining));
                addRingGroup(ringIndex++, min(count, remaining));
            }
        }
    }

    shuffle(people.begin(), people.end());

    println((int)people.size());
    for (const auto& person : people) {
        println(person.first, person.second);
    }

    return 0;
}
