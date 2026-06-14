#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

struct Problem {
    int beauty;
    int difficulty;
};

vector<Problem> shuffledAllDifficulties() {
    vector<Problem> problems;
    for (int difficulty = 1; difficulty <= 10; ++difficulty) {
        problems.push_back({rnd.next(1, 10), difficulty});
    }
    shuffle(problems.begin(), problems.end());
    return problems;
}

void addDuplicates(vector<Problem>& problems, int extraCount) {
    for (int i = 0; i < extraCount; ++i) {
        int difficulty = rnd.next(1, 10);
        problems.push_back({rnd.next(1, 10), difficulty});
    }
}

vector<Problem> makeCase(int mode) {
    vector<Problem> problems;

    if (mode == 0) {
        int n = rnd.next(1, 9);
        vector<int> difficulties;
        for (int difficulty = 1; difficulty <= 10; ++difficulty) {
            difficulties.push_back(difficulty);
        }
        shuffle(difficulties.begin(), difficulties.end());
        for (int i = 0; i < n; ++i) {
            problems.push_back({rnd.next(1, 10), difficulties[i]});
        }
    } else if (mode == 1) {
        problems = shuffledAllDifficulties();
    } else if (mode == 2) {
        problems = shuffledAllDifficulties();
        addDuplicates(problems, rnd.next(1, 12));
        shuffle(problems.begin(), problems.end());
    } else if (mode == 3) {
        int difficulty = rnd.next(1, 10);
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            problems.push_back({rnd.next(1, 10), difficulty});
        }
    } else {
        int n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            problems.push_back({rnd.next(1, 10), rnd.next(1, 10)});
        }
    }

    return problems;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        vector<Problem> problems = makeCase(mode);

        println(static_cast<int>(problems.size()));
        for (const Problem& problem : problems) {
            println(problem.beauty, problem.difficulty);
        }
    }

    return 0;
}
