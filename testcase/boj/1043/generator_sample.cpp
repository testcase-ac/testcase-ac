#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

vector<int> shuffledPeople(int n) {
    vector<int> people(n);
    iota(people.begin(), people.end(), 1);
    shuffle(people.begin(), people.end());
    return people;
}

vector<int> takeUnique(vector<int> people, int count) {
    shuffle(people.begin(), people.end());
    people.resize(count);
    sort(people.begin(), people.end());
    return people;
}

vector<int> randomPartyFromPool(const vector<int>& pool, int minSize, int maxSize) {
    int size = rnd.next(minSize, maxSize);
    return takeUnique(pool, size);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    vector<int> people = shuffledPeople(n);
    vector<int> truth;
    vector<vector<int>> parties;

    if (mode == 0) {
        truth.clear();
        for (int i = 0; i < m; ++i) {
            int maxSize = min(n, rnd.next(1, min(n, 5)));
            parties.push_back(randomPartyFromPool(people, 1, maxSize));
        }
    } else if (mode == 1) {
        int truthCount = rnd.next(1, n);
        truth = takeUnique(people, truthCount);
        int root = rnd.any(truth);
        for (int i = 0; i < m; ++i) {
            vector<int> party = {root};
            vector<int> candidates;
            for (int person : people) {
                if (person != root) candidates.push_back(person);
            }
            int extra = rnd.next(0, min<int>(4, candidates.size()));
            vector<int> picked = takeUnique(candidates, extra);
            party.insert(party.end(), picked.begin(), picked.end());
            sort(party.begin(), party.end());
            parties.push_back(party);
        }
    } else if (mode == 2) {
        int split = rnd.next(1, n);
        vector<int> left(people.begin(), people.begin() + split);
        vector<int> right(people.begin() + split, people.end());
        if (right.empty()) right.push_back(left.back());

        truth = {rnd.any(left)};
        for (int i = 0; i < m; ++i) {
            const vector<int>& pool = (i % 3 == 0 || right.empty()) ? left : right;
            int maxSize = min<int>(pool.size(), 5);
            parties.push_back(randomPartyFromPool(pool, 1, maxSize));
        }
    } else if (mode == 3) {
        int truthCount = rnd.next(1, min(n, 3));
        truth = takeUnique(people, truthCount);
        vector<int> order = shuffledPeople(n);
        for (int i = 0; i < m; ++i) {
            int a = order[i % n];
            int b = order[(i + 1) % n];
            vector<int> party = {a};
            if (b != a) party.push_back(b);
            if (n > 2 && rnd.next(2) == 1) {
                int c = order[(i + rnd.next(2, n - 1)) % n];
                if (find(party.begin(), party.end(), c) == party.end()) {
                    party.push_back(c);
                }
            }
            sort(party.begin(), party.end());
            parties.push_back(party);
        }
    } else {
        int truthCount = rnd.next(0, n);
        truth = takeUnique(people, truthCount);
        for (int i = 0; i < m; ++i) {
            int maxSize = min(n, rnd.next(1, min(n, 6)));
            parties.push_back(randomPartyFromPool(people, 1, maxSize));
        }
    }

    println(n, m);
    if (truth.empty()) {
        println(0);
    } else {
        println(static_cast<int>(truth.size()), truth);
    }
    for (const vector<int>& party : parties) {
        println(static_cast<int>(party.size()), party);
    }

    return 0;
}
