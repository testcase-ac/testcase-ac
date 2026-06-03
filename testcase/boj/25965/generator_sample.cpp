#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Mission {
    int k;
    int d;
    int a;
};

int chooseAmount(int mode) {
    if (mode == 0) return rnd.next(1000, 12000);
    if (mode == 1) return rnd.next(1000, 50000000);
    return rnd.any(vector<int>{1000, 2000, 50000000});
}

Mission makeMission(int kills, int deaths, int assists, int mode) {
    Mission mission{chooseAmount(mode), chooseAmount(mode), chooseAmount(mode)};

    if (mode == 3) {
        int reward = rnd.next(1000, 20000);
        mission.k = reward;
        mission.a = rnd.next(1000, 20000);
        mission.d = rnd.next(30000, 50000000);
    } else if (mode == 4) {
        int penalty = rnd.next(1000, 20000);
        mission.d = penalty;
        mission.k = rnd.next(30000, 50000000);
        mission.a = rnd.next(30000, 50000000);
    } else if (mode == 5 && deaths > 0) {
        mission.k = chooseAmount(0);
        mission.a = chooseAmount(0);
        int positive = kills * mission.k + assists * mission.a;
        mission.d = max(1000, min(50000000, positive / deaths));
    }

    return mission;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(0, 5);
    int n = nMode == 0 ? 1 : (nMode == 1 ? rnd.next(2, 5) : rnd.next(6, 12));

    println(n);
    for (int game = 0; game < n; ++game) {
        int statMode = rnd.next(0, 4);
        int kills = rnd.next(0, 12);
        int deaths = rnd.next(0, 12);
        int assists = rnd.next(0, 12);

        if (statMode == 0) {
            kills = 0;
            assists = 0;
            deaths = rnd.next(1, 12);
        } else if (statMode == 1) {
            kills = rnd.next(8, 50);
            assists = rnd.next(8, 50);
            deaths = rnd.next(0, 3);
        } else if (statMode == 2) {
            kills = rnd.any(vector<int>{0, 50});
            deaths = rnd.any(vector<int>{0, 50});
            assists = rnd.any(vector<int>{0, 50});
        }

        int mMode = rnd.next(0, 4);
        int m = mMode == 0 ? 1 : (mMode == 1 ? rnd.next(2, 5) : rnd.next(6, 15));

        vector<Mission> missions;
        for (int i = 0; i < m; ++i) {
            missions.push_back(makeMission(kills, deaths, assists, rnd.next(0, 5)));
        }
        shuffle(missions.begin(), missions.end());

        println(m);
        for (const Mission& mission : missions) {
            println(mission.k, mission.d, mission.a);
        }
        println(kills, deaths, assists);
    }

    return 0;
}
