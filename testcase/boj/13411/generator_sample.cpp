#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Robot {
    int x;
    int y;
    int v;
};

static void addRobot(vector<Robot>& robots, set<pair<int, int>>& used, int x, int y,
                     int v) {
    if (used.insert({x, y}).second) {
        robots.push_back({x, y, v});
    }
}

static int randomSign() {
    return rnd.next(0, 1) == 0 ? -1 : 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Robot> robots;
    set<pair<int, int>> used;
    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);

    if (mode == 0) {
        addRobot(robots, used, 0, 0, rnd.next(1, 1000));
        while ((int)robots.size() < n) {
            int d = rnd.next(1, 60);
            int axis = rnd.next(0, 3);
            int x = axis < 2 ? randomSign() * d : 0;
            int y = axis >= 2 ? randomSign() * d : 0;
            addRobot(robots, used, x, y, rnd.next(1, 1000));
        }
    } else if (mode == 1) {
        while ((int)robots.size() < n) {
            int v = rnd.next(1, 20);
            int k = rnd.next(1, 25);
            int x = randomSign() * v * k;
            int y = rnd.next(0, 1) == 0 ? 0 : randomSign() * v * k;
            addRobot(robots, used, x, y, v);
        }
    } else if (mode == 2) {
        while ((int)robots.size() < n) {
            int x = rnd.next(-10000, 10000);
            int y = rnd.next(-10000, 10000);
            int v = rnd.next(950, 1000);
            addRobot(robots, used, x, y, v);
        }
    } else if (mode == 3) {
        while ((int)robots.size() < n) {
            int x = rnd.next(-30, 30);
            int y = rnd.next(-30, 30);
            int v = rnd.next(1, 8);
            addRobot(robots, used, x, y, v);
        }
    } else {
        vector<tuple<int, int, int>> candidates = {
            {3, 4, 5},     {-3, 4, 5},    {5, 12, 13},   {-5, -12, 13},
            {8, 15, 17},   {7, 24, 25},   {-20, 21, 29}, {0, 40, 10},
            {40, 0, 10},   {-60, 80, 20}, {99, 0, 9},    {0, -99, 9},
            {120, 160, 40}};
        shuffle(candidates.begin(), candidates.end());
        for (auto [x, y, v] : candidates) {
            if ((int)robots.size() == n) break;
            addRobot(robots, used, x, y, v);
        }
        while ((int)robots.size() < n) {
            int x = rnd.next(-100, 100);
            int y = rnd.next(-100, 100);
            int v = rnd.next(1, 50);
            addRobot(robots, used, x, y, v);
        }
    }

    shuffle(robots.begin(), robots.end());

    println((int)robots.size());
    for (const Robot& robot : robots) {
        println(robot.x, robot.y, robot.v);
    }

    return 0;
}
