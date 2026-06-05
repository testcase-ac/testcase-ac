#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int k;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 8);
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        m = rnd.next(1, 12);
        k = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
        m = rnd.next(8, 25);
        k = rnd.next(1, n);
    } else if (mode == 3) {
        n = 10;
        m = rnd.next(12, 35);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(6, 30);
        k = n;
    } else {
        n = rnd.next(3, 10);
        m = rnd.next(15, 45);
        k = rnd.next(1, n);
    }

    vector<int> skills(2 * n);
    iota(skills.begin(), skills.end(), 1);
    shuffle(skills.begin(), skills.end());

    vector<int> favored(skills.begin(), skills.begin() + n);
    vector<int> other(skills.begin() + n, skills.end());
    vector<vector<int>> quests;

    auto randomQuest = [&](const vector<int>& pool, bool allowDuplicate) {
        vector<int> quest;
        if (allowDuplicate) {
            for (int i = 0; i < k; ++i) {
                quest.push_back(rnd.any(pool));
            }
        } else {
            vector<int> local = pool;
            shuffle(local.begin(), local.end());
            for (int i = 0; i < k; ++i) {
                quest.push_back(local[i]);
            }
        }
        if (rnd.next(0, 1)) {
            shuffle(quest.begin(), quest.end());
        }
        return quest;
    };

    auto mixedQuest = [&]() {
        vector<int> quest;
        int fromFavored = rnd.next(0, k);
        vector<int> left = favored;
        vector<int> right = other;
        shuffle(left.begin(), left.end());
        shuffle(right.begin(), right.end());
        for (int i = 0; i < fromFavored; ++i) {
            quest.push_back(left[i % (int)left.size()]);
        }
        for (int i = fromFavored; i < k; ++i) {
            quest.push_back(right[(i - fromFavored) % (int)right.size()]);
        }
        shuffle(quest.begin(), quest.end());
        return quest;
    };

    for (int i = 0; i < m; ++i) {
        int pattern = rnd.next(0, 99);
        bool duplicateMode = (mode == 5 && pattern < 35) || pattern < 8;

        if (pattern < 35) {
            quests.push_back(randomQuest(favored, duplicateMode));
        } else if (pattern < 55) {
            quests.push_back(randomQuest(other, duplicateMode));
        } else if (pattern < 85) {
            quests.push_back(mixedQuest());
        } else {
            quests.push_back(randomQuest(skills, duplicateMode));
        }
    }

    if (m >= 2 && k == n) {
        quests[0] = favored;
        quests[1] = other;
        shuffle(quests[0].begin(), quests[0].end());
        shuffle(quests[1].begin(), quests[1].end());
    }

    println(n, m, k);
    for (const auto& quest : quests) {
        println(quest);
    }

    return 0;
}
