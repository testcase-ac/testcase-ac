#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static void readTeam(const string& prefix) {
    int touchdowns = inf.readInt(0, 10, (prefix + "_T").c_str());
    inf.readSpace();
    int fieldGoals = inf.readInt(0, 10, (prefix + "_F").c_str());
    inf.readSpace();
    int safeties = inf.readInt(0, 10, (prefix + "_S").c_str());
    inf.readSpace();
    int pointsAfter = inf.readInt(0, 10, (prefix + "_P").c_str());
    inf.readSpace();
    int conversions = inf.readInt(0, 10, (prefix + "_C").c_str());
    inf.readEoln();

    ensuref(pointsAfter + conversions <= touchdowns,
            "%s has P + C = %d greater than T = %d",
            prefix.c_str(), pointsAfter + conversions, touchdowns);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readTeam("visitor");
    readTeam("home");

    inf.readEof();
}
