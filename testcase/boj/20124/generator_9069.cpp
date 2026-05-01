#include "testlib.h"
using namespace std;

struct Person {
    string name;
    long long score;
};

string makeName(int id) {
    id++; // make it 1-based
    string s;
    while (id > 0) {
        int rem = (id - 1) % 26;
        s.push_back('a' + rem);
        id = (id - 1) / 26;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 5); // 6 types: 0..5
    vector<Person> people;

    // Decide if we want very large scores sometimes
    auto genMaxScore = [&]() -> long long {
        bool big = (rnd.next(0, 9) == 0); // 10% chance of big scores
        if (big) {
            // in [1e9-50, 1e9]
            return rnd.next(1000000000 - 50, 1000000000);
        } else {
            return rnd.next(2, 1000); // at least 2 to allow smaller scores
        }
    };

    if (type == 0) {
        // Very small N, unique maximum
        int sub = rnd.next(0, 2);
        int N;
        if (sub == 0) N = 1;
        else N = rnd.next(2, 5);

        long long base = rnd.next(1, 10);
        long long step = rnd.next(1, 5);

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = makeName(i);
            p.score = base + 1LL * i * step; // strictly increasing
            people.push_back(p);
        }
    } else if (type == 1) {
        // All equal scores
        int N = rnd.next(2, 10);
        long long commonScore = genMaxScore();

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = makeName(i);
            p.score = commonScore;
            people.push_back(p);
        }
        shuffle(people.begin(), people.end());
    } else if (type == 2) {
        // Tricky lexicographical names, tie among some, others smaller
        vector<string> trickyNames = {
            "a", "aa", "aaa", "b", "ab", "aba",
            "zzz", "zz", "za", "az", "aaaz", "aaz"
        };
        shuffle(trickyNames.begin(), trickyNames.end());
        int maxN = min((int)trickyNames.size(), 10);
        int N = rnd.next(3, maxN);

        long long maxScore = genMaxScore();

        // Pick indices for max scorers (at least 2, at most N-1)
        int k = rnd.next(2, min(4, N - 1));
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());

        vector<bool> isMax(N, false);
        for (int i = 0; i < k; i++) isMax[idx[i]] = true;

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = trickyNames[i];
            if (isMax[i]) {
                p.score = maxScore;
            } else {
                // strictly smaller than maxScore
                p.score = rnd.next(1LL, maxScore - 1);
            }
            people.push_back(p);
        }
        shuffle(people.begin(), people.end());
    } else if (type == 3) {
        // Medium N, sequential names, several tie-max, others smaller
        int N = rnd.next(10, 20);
        long long maxScore = genMaxScore();

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = makeName(i);
            p.score = rnd.next(1LL, maxScore - 1);
            people.push_back(p);
        }

        int k = rnd.next(2, min(5, N));
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < k; i++) {
            people[idx[i]].score = maxScore;
        }
        shuffle(people.begin(), people.end());
    } else if (type == 4) {
        // Names that are very close lexicographically
        vector<string> nearNames = {
            "a", "aa", "ab", "ac", "b", "ba", "bb",
            "z", "za", "zb", "zz"
        };
        int maxN = (int)nearNames.size();
        int N = rnd.next(4, maxN);

        long long maxScore = genMaxScore();

        // Choose N names
        shuffle(nearNames.begin(), nearNames.end());
        nearNames.resize(N);

        // Choose max scorers (at least 2, at most N-1)
        int k = rnd.next(2, min(5, N - 1));
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        vector<bool> isMax(N, false);
        for (int i = 0; i < k; i++) isMax[idx[i]] = true;

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = nearNames[i];
            if (isMax[i]) {
                p.score = maxScore;
            } else {
                p.score = rnd.next(1LL, maxScore - 1);
            }
            people.push_back(p);
        }
        shuffle(people.begin(), people.end());
    } else { // type == 5
        // General random case: sometimes unique max, sometimes tie
        bool makeTie = (rnd.next(0, 1) == 1);
        int N = rnd.next(5, 20);
        long long maxScore = genMaxScore();

        for (int i = 0; i < N; i++) {
            Person p;
            p.name = makeName(i);
            p.score = rnd.next(1LL, maxScore - 1);
            people.push_back(p);
        }

        if (makeTie) {
            int k = rnd.next(2, min(5, N));
            vector<int> idx(N);
            for (int i = 0; i < N; i++) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < k; i++) {
                people[idx[i]].score = maxScore;
            }
        } else {
            // Single max: choose one index to be unique max
            int pos = rnd.next(0, N - 1);
            people[pos].score = maxScore;
        }
        shuffle(people.begin(), people.end());
    }

    int N = (int)people.size();
    println(N);
    for (const auto &p : people) {
        println(p.name, p.score);
    }

    return 0;
}
