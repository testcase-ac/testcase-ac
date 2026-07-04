#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Medal {
    int gold;
    int silver;
    int bronze;
};

static Medal medal(int gold, int silver, int bronze) {
    return Medal{gold, silver, bronze};
}

static int clampMedal(int value) {
    return max(0, min(10000, value));
}

static void printCase(int N, int L, const vector<Medal>& teams) {
    println(N, L);
    for (const Medal& team : teams) {
        println(team.gold, team.silver, team.bronze);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = 3;
    int L = 0;
    vector<Medal> teams;

    if (mode == 0) {
        N = rnd.next(3, 8);
        L = rnd.next(0, 12);
        int firstGoldAfter = rnd.next(L, L + 6);
        teams.push_back(medal(firstGoldAfter - L, rnd.next(0, 20), rnd.next(0, 20)));
        for (int i = 1; i < N; ++i) {
            teams.push_back(medal(firstGoldAfter, rnd.next(0, 20), rnd.next(0, 20)));
        }
    } else if (mode == 1) {
        N = rnd.next(3, 10);
        L = 0;
        int baseGold = rnd.next(0, 12);
        int baseSilver = rnd.next(0, 12);
        int baseBronze = rnd.next(0, 12);
        for (int i = 0; i < N; ++i) {
            teams.push_back(medal(
                clampMedal(baseGold + rnd.next(-2, 3)),
                clampMedal(baseSilver + rnd.next(-2, 3)),
                clampMedal(baseBronze + rnd.next(-2, 3))));
        }
    } else if (mode == 2) {
        N = rnd.next(3, 12);
        L = rnd.next(1, 20);
        int firstGoldAfter = rnd.next(1, 25);
        int firstSilver = rnd.next(0, 15);
        int firstBronze = rnd.next(0, 15);
        teams.push_back(medal(max(0, firstGoldAfter - L), firstSilver, firstBronze));
        for (int i = 1; i < N; ++i) {
            int gold = clampMedal(firstGoldAfter + rnd.next(-1, 1));
            int silver = clampMedal(firstSilver + rnd.next(-3, 4));
            int bronze = clampMedal(firstBronze + rnd.next(-3, 4));
            teams.push_back(medal(gold, silver, bronze));
        }
    } else if (mode == 3) {
        N = rnd.next(3, 15);
        L = rnd.next(1, 25);
        int targetGold = rnd.next(L, L + 12);
        int firstSilver = rnd.next(0, 8);
        int firstBronze = rnd.next(0, 8);
        teams.push_back(medal(targetGold - L, firstSilver, firstBronze));
        for (int i = 1; i < N; ++i) {
            int needSilver = rnd.next(0, L + 2);
            int needBronze = rnd.next(0, L + 2);
            teams.push_back(medal(
                targetGold,
                clampMedal(firstSilver - needSilver),
                clampMedal(firstBronze - needBronze)));
        }
    } else if (mode == 4) {
        N = rnd.next(3, 10);
        L = rnd.next(0, 15);
        for (int i = 0; i < N; ++i) {
            teams.push_back(medal(rnd.next(0, 25), rnd.next(0, 25), rnd.next(0, 25)));
        }
    } else {
        N = rnd.next(45, 50);
        L = rnd.next(9000, 10000);
        for (int i = 0; i < N; ++i) {
            teams.push_back(medal(rnd.next(0, 10000), rnd.next(0, 10000), rnd.next(0, 10000)));
        }
    }

    printCase(N, L, teams);
    return 0;
}
