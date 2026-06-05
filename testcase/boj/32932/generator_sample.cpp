#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> step(pair<int, int> p, char command) {
    if (command == 'U') ++p.second;
    if (command == 'D') --p.second;
    if (command == 'R') ++p.first;
    if (command == 'L') --p.first;
    return p;
}

void addObstacle(set<pair<int, int>>& obstacles, int x, int y) {
    if (x < -500 || x > 500 || y < -500 || y > 500) return;
    if (x == 0 && y == 0) return;
    obstacles.insert({x, y});
}

void addRandomObstacle(set<pair<int, int>>& obstacles, int spread) {
    for (int tries = 0; tries < 1000; ++tries) {
        int x = rnd.next(-spread, spread);
        int y = rnd.next(-spread, spread);
        if (x == 0 && y == 0) continue;
        if (obstacles.insert({x, y}).second) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string alphabet = "UDRL";
    int mode = rnd.next(0, 4);
    int k = rnd.next(1, 80);
    string commands;
    set<pair<int, int>> obstacles;

    if (mode == 0) {
        k = rnd.next(1, 120);
        for (int i = 0; i < k; ++i) commands += rnd.any(alphabet);
        int n = rnd.next(1, 35);
        int spread = rnd.next(2, 25);
        while ((int)obstacles.size() < n) addRandomObstacle(obstacles, spread);
    } else if (mode == 1) {
        pair<int, int> pos = {0, 0};
        for (int i = 0; i < k; ++i) {
            char command = rnd.any(alphabet);
            commands += command;
            pair<int, int> next = step(pos, command);
            if (rnd.next(0, 99) < 35) {
                addObstacle(obstacles, next.first, next.second);
            } else {
                pos = next;
            }
            if (rnd.next(0, 99) < 20) {
                addObstacle(obstacles, pos.first + rnd.next(-2, 2),
                            pos.second + rnd.next(-2, 2));
            }
        }
    } else if (mode == 2) {
        int width = rnd.next(1, 5);
        int height = rnd.next(1, 5);
        for (int x = -width; x <= width; ++x) {
            addObstacle(obstacles, x, -height);
            addObstacle(obstacles, x, height);
        }
        for (int y = -height; y <= height; ++y) {
            addObstacle(obstacles, -width, y);
            addObstacle(obstacles, width, y);
        }
        k = rnd.next(20, 120);
        for (int i = 0; i < k; ++i) commands += rnd.any(alphabet);
    } else if (mode == 3) {
        int runs = rnd.next(2, 8);
        for (int i = 0; i < runs; ++i) {
            char command = rnd.any(alphabet);
            int len = rnd.next(1, 18);
            commands += string(len, command);
        }
        k = commands.size();
        pair<int, int> pos = {0, 0};
        for (char command : commands) {
            pair<int, int> next = step(pos, command);
            if (rnd.next(0, 99) < 25) addObstacle(obstacles, next.first, next.second);
            if (!obstacles.count(next)) pos = next;
        }
    } else {
        k = rnd.next(10, 80);
        for (int i = 0; i < k; ++i) commands += rnd.any(alphabet);
        vector<pair<int, int>> corners = {
            {-500, -500}, {-500, 500}, {500, -500}, {500, 500},
            {-500, 0},    {500, 0},    {0, -500},   {0, 500},
        };
        shuffle(corners.begin(), corners.end());
        int take = rnd.next(1, (int)corners.size());
        for (int i = 0; i < take; ++i) addObstacle(obstacles, corners[i].first, corners[i].second);
    }

    int targetN = rnd.next(max(1, (int)obstacles.size()), min(80, max(1, (int)obstacles.size() + 25)));
    while ((int)obstacles.size() < targetN) addRandomObstacle(obstacles, rnd.next(3, 40));

    vector<pair<int, int>> obstacleList(obstacles.begin(), obstacles.end());
    shuffle(obstacleList.begin(), obstacleList.end());

    println((int)obstacleList.size(), k);
    for (auto obstacle : obstacleList) println(obstacle.first, obstacle.second);
    println(commands);

    return 0;
}
