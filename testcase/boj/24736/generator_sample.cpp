#include "testlib.h"
#include <vector>
using namespace std;

struct Team {
    int touchdowns;
    int fieldGoals;
    int safeties;
    int pointsAfter;
    int conversions;
};

Team randomTeam(int touchdownLimit) {
    Team team;
    team.touchdowns = rnd.next(0, touchdownLimit);
    team.fieldGoals = rnd.next(0, 10);
    team.safeties = rnd.next(0, 10);
    team.pointsAfter = rnd.next(0, team.touchdowns);
    team.conversions = rnd.next(0, team.touchdowns - team.pointsAfter);
    return team;
}

Team anchoredTeam() {
    vector<int> anchors = {0, 1, 2, 9, 10};
    Team team;
    team.touchdowns = rnd.any(anchors);
    team.fieldGoals = rnd.any(anchors);
    team.safeties = rnd.any(anchors);

    int afterTouchdown = rnd.next(0, team.touchdowns);
    team.pointsAfter = rnd.next(0, afterTouchdown);
    team.conversions = afterTouchdown - team.pointsAfter;
    return team;
}

Team fullAfterTouchdownTeam() {
    Team team;
    team.touchdowns = rnd.next(1, 10);
    team.fieldGoals = rnd.next(0, 10);
    team.safeties = rnd.next(0, 10);
    team.pointsAfter = rnd.next(0, team.touchdowns);
    team.conversions = team.touchdowns - team.pointsAfter;
    return team;
}

void printTeam(const Team& team) {
    println(team.touchdowns, team.fieldGoals, team.safeties,
            team.pointsAfter, team.conversions);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Team visitor;
    Team home;

    if (mode == 0) {
        visitor = randomTeam(3);
        home = randomTeam(3);
    } else if (mode == 1) {
        visitor = randomTeam(10);
        home = randomTeam(10);
    } else if (mode == 2) {
        visitor = anchoredTeam();
        home = anchoredTeam();
    } else if (mode == 3) {
        visitor = fullAfterTouchdownTeam();
        home = fullAfterTouchdownTeam();
    } else if (mode == 4) {
        visitor = {0, rnd.next(0, 10), rnd.next(0, 10), 0, 0};
        home = fullAfterTouchdownTeam();
    } else {
        visitor = {10, rnd.next(0, 10), rnd.next(0, 10),
                   rnd.next(0, 10), 0};
        visitor.conversions = rnd.next(0, 10 - visitor.pointsAfter);
        home = anchoredTeam();
    }

    printTeam(visitor);
    printTeam(home);
    return 0;
}
