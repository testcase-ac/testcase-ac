#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int s = rnd.next(1, 8);
    int n = rnd.next(1, 24);
    vector<pair<int, string>> people;
    people.reserve(n);

    if (mode == 0) {
        s = rnd.next(1, 3);
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, max(1, n / 2));
            string t = rnd.next(0, 1) ? "y" : "n";
            people.push_back({d, t});
        }
    } else if (mode == 1) {
        s = rnd.next(1, 5);
        n = rnd.next(5, 18);
        int yCount = rnd.next(n / 2, n);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, n + 3);
            string t = i < yCount ? "y" : "n";
            people.push_back({d, t});
        }
    } else if (mode == 2) {
        s = rnd.next(2, 8);
        n = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(n, 1000000000);
            string t = rnd.next(0, 3) == 0 ? "y" : "n";
            people.push_back({d, t});
        }
    } else if (mode == 3) {
        s = rnd.next(1, 6);
        n = rnd.next(6, 24);
        int pivot = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(max(1, pivot - 2), min(1000000000, pivot + 2));
            string t = rnd.next(0, 2) == 0 ? "y" : "n";
            people.push_back({d, t});
        }
    } else if (mode == 4) {
        s = rnd.next(1, 8);
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, n + 5);
            string t = i % rnd.next(2, 4) == 0 ? "y" : "n";
            people.push_back({d, t});
        }
    } else {
        s = rnd.next(1, 8);
        n = rnd.next(1, 24);
        int low = rnd.next(1, n);
        int high = rnd.next(low, min(1000000000, n * 3));
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(low, high);
            string t = rnd.next(0, 1) ? "y" : "n";
            people.push_back({d, t});
        }
    }

    shuffle(people.begin(), people.end());

    println(s, n);
    for (const auto& person : people) {
        println(person.first, person.second);
    }

    return 0;
}
