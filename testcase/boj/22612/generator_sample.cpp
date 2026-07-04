#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct RoomPair {
    int w;
    int h;
    vector<string> left;
    vector<string> right;
};

pair<int, int> randomCell(int h, int w) {
    return {rnd.next(0, h - 1), rnd.next(0, w - 1)};
}

pair<int, int> distinctCell(int h, int w, pair<int, int> blocked) {
    pair<int, int> p;
    do {
        p = randomCell(h, w);
    } while (p == blocked);
    return p;
}

void placeMarkers(RoomPair& room, pair<int, int> len, pair<int, int> leftGoal,
                  pair<int, int> rin, pair<int, int> rightGoal) {
    room.left[len.first][len.second] = 'L';
    room.left[leftGoal.first][leftGoal.second] = '%';
    room.right[rin.first][rin.second] = 'R';
    room.right[rightGoal.first][rightGoal.second] = '%';
}

RoomPair makeRandomRooms(int w, int h, int wallPercent) {
    RoomPair room{w, h, vector<string>(h, string(w, '.')),
                  vector<string>(h, string(w, '.'))};

    auto len = randomCell(h, w);
    auto leftGoal = distinctCell(h, w, len);
    auto rin = randomCell(h, w);
    auto rightGoal = distinctCell(h, w, rin);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pair<int, int> here = {i, j};
            if (here != len && here != leftGoal && rnd.next(0, 99) < wallPercent) {
                room.left[i][j] = '#';
            }
            if (here != rin && here != rightGoal && rnd.next(0, 99) < wallPercent) {
                room.right[i][j] = '#';
            }
        }
    }

    placeMarkers(room, len, leftGoal, rin, rightGoal);
    return room;
}

RoomPair makeCorridor() {
    bool horizontal = rnd.next(0, 1) == 0;
    int len = rnd.next(2, 12);
    int w = horizontal ? len : 1;
    int h = horizontal ? 1 : len;
    RoomPair room{w, h, vector<string>(h, string(w, '.')),
                  vector<string>(h, string(w, '.'))};

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {h - 1, w - 1};
    if (rnd.next(0, 1)) {
        swap(start, goal);
    }

    pair<int, int> rin = {start.first, w - 1 - start.second};
    pair<int, int> rightGoal = {goal.first, w - 1 - goal.second};
    if (rin == rightGoal) {
        rightGoal = distinctCell(h, w, rin);
    }

    placeMarkers(room, start, goal, rin, rightGoal);
    return room;
}

RoomPair makeMirroredObstacles() {
    int w = rnd.next(3, 12);
    int h = rnd.next(3, 8);
    RoomPair room{w, h, vector<string>(h, string(w, '.')),
                  vector<string>(h, string(w, '.'))};

    auto len = randomCell(h, w);
    auto leftGoal = distinctCell(h, w, len);
    pair<int, int> rin = {len.first, w - 1 - len.second};
    pair<int, int> rightGoal = {leftGoal.first, w - 1 - leftGoal.second};
    if (rin == rightGoal) {
        rightGoal = distinctCell(h, w, rin);
    }

    int wallPercent = rnd.next(10, 35);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pair<int, int> leftHere = {i, j};
            pair<int, int> rightHere = {i, w - 1 - j};
            if (leftHere == len || leftHere == leftGoal || rightHere == rin ||
                rightHere == rightGoal) {
                continue;
            }
            if (rnd.next(0, 99) < wallPercent) {
                room.left[i][j] = '#';
                room.right[i][w - 1 - j] = '#';
            }
        }
    }

    placeMarkers(room, len, leftGoal, rin, rightGoal);
    return room;
}

RoomPair makeGatePattern() {
    int w = rnd.next(5, 12);
    int h = rnd.next(4, 8);
    RoomPair room{w, h, vector<string>(h, string(w, '.')),
                  vector<string>(h, string(w, '.'))};

    int wallRow = rnd.next(1, h - 2);
    int leftGate = rnd.next(0, w - 1);
    int rightGate = rnd.next(0, w - 1);
    for (int j = 0; j < w; ++j) {
        if (j != leftGate) {
            room.left[wallRow][j] = '#';
        }
        if (j != rightGate) {
            room.right[wallRow][j] = '#';
        }
    }

    pair<int, int> len = {rnd.next(0, wallRow - 1), rnd.next(0, w - 1)};
    pair<int, int> leftGoal = {rnd.next(wallRow + 1, h - 1), rnd.next(0, w - 1)};
    pair<int, int> rin = {rnd.next(0, wallRow - 1), rnd.next(0, w - 1)};
    pair<int, int> rightGoal = {rnd.next(wallRow + 1, h - 1), rnd.next(0, w - 1)};

    placeMarkers(room, len, leftGoal, rin, rightGoal);
    return room;
}

RoomPair makeCase() {
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return makeCorridor();
    }
    if (mode == 1) {
        return makeRandomRooms(rnd.next(2, 8), rnd.next(2, 8), rnd.next(0, 18));
    }
    if (mode == 2) {
        return makeRandomRooms(rnd.next(4, 12), rnd.next(3, 9), rnd.next(25, 48));
    }
    if (mode == 3) {
        return makeMirroredObstacles();
    }
    return makeGatePattern();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 7);
    for (int tc = 0; tc < cases; ++tc) {
        RoomPair room = makeCase();
        println(room.w, room.h);
        for (int i = 0; i < room.h; ++i) {
            println(room.left[i], room.right[i]);
        }
    }
    println(0, 0);
    return 0;
}
