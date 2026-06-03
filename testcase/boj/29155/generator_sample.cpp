#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int boundedTime(int value) {
    return max(1, min(300, value));
}

int makeTime(int difficulty, int index, int count, int mode) {
    if (mode == 0) {
        return rnd.next(1, 300);
    }
    if (mode == 1) {
        int base = rnd.next(1, 300);
        return boundedTime(base + rnd.next(-2, 2));
    }
    if (mode == 2) {
        return (index % 2 == 0) ? rnd.next(1, 8) : rnd.next(293, 300);
    }
    if (mode == 3) {
        int lo = rnd.next(1, 260);
        int hi = rnd.next(lo, 300);
        if (count == 1) {
            return rnd.next(lo, hi);
        }
        return lo + (hi - lo) * index / (count - 1);
    }

    int center = 35 + 45 * (difficulty - 1);
    return boundedTime(center + rnd.next(-20, 20));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 35);
    if (rnd.next(5) == 0) {
        n = rnd.next(36, 80);
    }

    vector<int> countByDifficulty(6, 1);
    for (int remaining = n - 5; remaining > 0; --remaining) {
        ++countByDifficulty[rnd.next(1, 5)];
    }

    vector<int> required(6);
    for (int difficulty = 1; difficulty <= 5; ++difficulty) {
        if (rnd.next(4) == 0) {
            required[difficulty] = countByDifficulty[difficulty];
        } else {
            required[difficulty] = rnd.next(1, countByDifficulty[difficulty]);
        }
    }

    vector<pair<int, int>> problems;
    for (int difficulty = 1; difficulty <= 5; ++difficulty) {
        int localMode = (rnd.next(3) == 0) ? rnd.next(0, 4) : mode;
        for (int i = 0; i < countByDifficulty[difficulty]; ++i) {
            problems.push_back(
                {difficulty, makeTime(difficulty, i, countByDifficulty[difficulty], localMode)});
        }
    }

    shuffle(problems.begin(), problems.end());

    println(n);
    println(vector<int>(required.begin() + 1, required.end()));
    for (const auto& problem : problems) {
        println(problem.first, problem.second);
    }

    return 0;
}
