#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

vector<Point> allCells(int lx, int ly) {
    vector<Point> cells;
    for (int x = -lx; x <= lx; ++x) {
        for (int y = -ly; y <= ly; ++y) {
            cells.push_back({x, y});
        }
    }
    return cells;
}

Point randomCell(int lx, int ly) {
    return {rnd.next(-lx, lx), rnd.next(-ly, ly)};
}

void addFurniture(set<Point>& furniture, Point p, Point start, Point goal, int lx, int ly) {
    if (p == start || p == goal) return;
    if (p.first < -lx || p.first > lx || p.second < -ly || p.second > ly) return;
    furniture.insert(p);
}

int furnitureCapacity(int lx, int ly) {
    return (2 * lx + 1) * (2 * ly + 1) - 2;
}

void fillRandomFurniture(set<Point>& furniture, int target, Point start, Point goal, int lx, int ly) {
    target = min(target, furnitureCapacity(lx, ly));
    vector<Point> cells = allCells(lx, ly);
    shuffle(cells.begin(), cells.end());

    for (Point p : cells) {
        if ((int)furniture.size() >= target) break;
        addFurniture(furniture, p, start, goal, lx, ly);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int lx = rnd.next(1, 8);
    int ly = rnd.next(1, 8);
    if (mode == 5) {
        lx = rnd.next(15, 100);
        ly = rnd.next(15, 100);
    }

    Point start = randomCell(lx, ly);
    Point goal = randomCell(lx, ly);
    while (goal == start) {
        goal = randomCell(lx, ly);
    }

    set<Point> furniture;

    if (mode == 0) {
        int count = rnd.next(0, min(10, furnitureCapacity(lx, ly)));
        fillRandomFurniture(furniture, count, start, goal, lx, ly);
    } else if (mode == 1) {
        int cx = rnd.next(-lx, lx);
        int cy = rnd.next(-ly, ly);
        int radius = rnd.next(1, 3);
        for (int x = cx - radius; x <= cx + radius; ++x) {
            for (int y = cy - radius; y <= cy + radius; ++y) {
                if (rnd.next(0, 99) < 55) {
                    addFurniture(furniture, {x, y}, start, goal, lx, ly);
                }
            }
        }
    } else if (mode == 2) {
        int target = rnd.next(1, min(9, furnitureCapacity(lx, ly)));
        int wallX = rnd.next(-lx, lx);
        for (int y = -ly; y <= ly; ++y) {
            if (rnd.next(0, 99) < 75) {
                addFurniture(furniture, {wallX, y}, start, goal, lx, ly);
            }
        }
        fillRandomFurniture(furniture, target, start, goal, lx, ly);
    } else if (mode == 3) {
        int target = rnd.next(1, min(9, furnitureCapacity(lx, ly)));
        int wallY = rnd.next(-ly, ly);
        for (int x = -lx; x <= lx; ++x) {
            if (rnd.next(0, 99) < 75) {
                addFurniture(furniture, {x, wallY}, start, goal, lx, ly);
            }
        }
        fillRandomFurniture(furniture, target, start, goal, lx, ly);
    } else if (mode == 4) {
        vector<Point> cells = allCells(lx, ly);
        shuffle(cells.begin(), cells.end());
        int limit = min(1000, furnitureCapacity(lx, ly));
        int count = rnd.next(max(0, limit / 3), limit);
        for (Point p : cells) {
            if ((int)furniture.size() == count) break;
            addFurniture(furniture, p, start, goal, lx, ly);
        }
    } else {
        start = rnd.any(vector<Point>{{-lx, -ly}, {-lx, ly}, {lx, -ly}, {lx, ly}});
        goal = rnd.any(vector<Point>{{-lx, -ly}, {-lx, ly}, {lx, -ly}, {lx, ly}});
        while (goal == start) {
            goal = rnd.any(vector<Point>{{-lx, -ly}, {-lx, ly}, {lx, -ly}, {lx, ly}});
        }
        int count = rnd.next(0, min(40, furnitureCapacity(lx, ly)));
        fillRandomFurniture(furniture, count, start, goal, lx, ly);
    }

    println(start.first, start.second, goal.first, goal.second);
    println((int)furniture.size());
    for (Point p : furniture) {
        println(p.first, p.second);
    }
    println(lx, ly);

    return 0;
}
