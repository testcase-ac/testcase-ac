#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Team {
    int k;
    int da;
    int db;
};

static Team makeTeam(int remainingCapacity, int mode) {
    int k = rnd.next(0, remainingCapacity);
    int da = rnd.next(0, 40);
    int db = rnd.next(0, 40);

    if (mode == 0) {
        db = da;
    } else if (mode == 1) {
        da = rnd.next(0, 8);
        db = rnd.next(30, 1000);
    } else if (mode == 2) {
        da = rnd.next(30, 1000);
        db = rnd.next(0, 8);
    } else if (mode == 3) {
        da = rnd.any(vector<int>{0, 1, 999, 1000});
        db = rnd.any(vector<int>{0, 1, 999, 1000});
    }

    return {k, da, db};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 8);
    for (int tc = 0; tc < cases; ++tc) {
        int n = rnd.next(1, 12);
        int totalCapacity = rnd.next(0, 60);
        int a = rnd.next(0, totalCapacity);
        int b = totalCapacity - a;
        if (rnd.next(4) == 0) {
            a = rnd.next(0, 10000);
            b = rnd.next(0, 10000);
            totalCapacity = min(a + b, 120);
        }

        vector<Team> teams;
        int remainingCapacity = totalCapacity;
        for (int i = 0; i < n; ++i) {
            int mode = (tc + i + rnd.next(5)) % 5;
            Team team = makeTeam(remainingCapacity, mode);
            teams.push_back(team);
            remainingCapacity -= team.k;
        }

        if (totalCapacity > 0 && rnd.next(2) == 0) {
            int add = rnd.next(0, remainingCapacity);
            teams[rnd.next(n)].k += add;
            remainingCapacity -= add;
        }
        shuffle(teams.begin(), teams.end());

        println(n, a, b);
        for (const Team& team : teams) {
            println(team.k, team.da, team.db);
        }
    }

    println(0, 0, 0);
    return 0;
}
