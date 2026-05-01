#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Box {
    int x, y, w;
};

int genWeight(int scenario) {
    if (scenario == 3) return 1; // all ones
    int t = rnd.next(0, 3);
    if (t == 0) return 1;
    if (t == 1) return rnd.next(2, 10);
    if (t == 2) return rnd.next(11, 100);
    return rnd.next(100000, 200000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4); // 0: random, 1: line, 2: path-heavy, 3: w=1, 4: rectangle path

    int B; // coordinate bound
    int Q;
    if (scenario == 4) {
        B = rnd.next(4, 20);
        Q = rnd.next(4, 20);
    } else {
        B = rnd.next(5, 25);
        Q = rnd.next(1, 20);
    }

    int maxN = min(20, B * B);
    int N = rnd.next(1, maxN);

    vector<pair<int,int>> moves;
    moves.reserve(Q);

    int curx = 1, cury = 1;
    int rectR = 0, rectU = 0;

    auto genRandomStep = [&](int &x, int &y) {
        int maxStep[4];
        maxStep[0] = B - x;    // right
        maxStep[1] = B - y;    // up
        maxStep[2] = x - 1;    // left
        maxStep[3] = y - 1;    // down

        vector<int> dirs;
        for (int d = 0; d < 4; d++)
            if (maxStep[d] >= 1) dirs.push_back(d);

        vector<int> cand;
        for (int d : dirs) {
            int weight = 1;
            if (scenario == 1 && (d == 0 || d == 2)) weight += 2; // horizontal bias
            if (scenario == 2 && (d == 1 || d == 3)) weight += 2; // vertical bias
            for (int i = 0; i < weight; i++) cand.push_back(d);
        }

        int dir = cand[rnd.next(0, (int)cand.size() - 1)];
        int maxS = maxStep[dir];
        int step;
        bool preferLong = (scenario == 2);
        if (preferLong) {
            step = rnd.wnext(maxS, +2) + 1;
        } else {
            step = rnd.wnext(maxS, -2) + 1;
        }
        if (step < 1) step = 1;
        if (step > maxS) step = maxS;

        moves.push_back({dir, step});
        if (dir == 0) x += step;
        else if (dir == 1) y += step;
        else if (dir == 2) x -= step;
        else y -= step;
    };

    if (scenario == 4) {
        rectR = rnd.next(1, B - 1);
        rectU = rnd.next(1, B - 1);

        // Rectangle loop returning to (1,1)
        moves.push_back({0, rectR});
        moves.push_back({1, rectU});
        moves.push_back({2, rectR});
        moves.push_back({3, rectU});
        curx = 1; cury = 1;

        for (int i = 4; i < Q; i++) {
            genRandomStep(curx, cury);
        }
    } else {
        for (int i = 0; i < Q; i++) {
            genRandomStep(curx, cury);
        }
    }

    // Simulate path to record distinct visited cells (excluding start (1,1))
    set<pair<int,int>> pathSet;
    vector<pair<int,int>> pathCells;
    pathCells.reserve(500);

    curx = 1; cury = 1;
    for (auto mv : moves) {
        int d = mv.first, v = mv.second;
        for (int s = 0; s < v; s++) {
            if (d == 0) curx++;
            else if (d == 1) cury++;
            else if (d == 2) curx--;
            else cury--;
            pair<int,int> p = {curx, cury};
            if (pathSet.insert(p).second) pathCells.push_back(p);
        }
    }

    // Prepare all grid cells
    vector<pair<int,int>> allCells;
    allCells.reserve(B * B);
    for (int x = 1; x <= B; x++)
        for (int y = 1; y <= B; y++)
            allCells.push_back({x, y});

    // Decide special cells for boxes
    vector<pair<int,int>> special;
    set<pair<int,int>> specialSet;

    auto addSpecial = [&](int x, int y) {
        pair<int,int> p = {x, y};
        if ((int)special.size() >= N) return;
        if (specialSet.insert(p).second) special.push_back(p);
    };

    if (scenario == 1) {
        // Many boxes on one row or one column
        bool horizontal = rnd.next(0, 1);
        if (horizontal) {
            int y0 = rnd.next(1, B);
            vector<pair<int,int>> line;
            for (int x = 1; x <= B; x++) line.push_back({x, y0});
            shuffle(line.begin(), line.end());
            int cellsOnLine = B;
            int kLine = min(cellsOnLine, max(1, N * 2 / 3));
            for (int i = 0; i < kLine; i++) addSpecial(line[i].first, line[i].second);
        } else {
            int x0 = rnd.next(1, B);
            vector<pair<int,int>> line;
            for (int y = 1; y <= B; y++) line.push_back({x0, y});
            shuffle(line.begin(), line.end());
            int cellsOnLine = B;
            int kLine = min(cellsOnLine, max(1, N * 2 / 3));
            for (int i = 0; i < kLine; i++) addSpecial(line[i].first, line[i].second);
        }
    } else if (scenario == 2) {
        // Boxes mostly on the path
        if (!pathCells.empty()) {
            vector<pair<int,int>> tmp = pathCells;
            shuffle(tmp.begin(), tmp.end());
            int d = (int)tmp.size();
            int kOnPath = min(d, max(1, N - rnd.next(0, N / 2)));
            for (int i = 0; i < kOnPath; i++) addSpecial(tmp[i].first, tmp[i].second);
        }
    } else if (scenario == 4) {
        // Put boxes at rectangle corners
        int x2 = 1 + rectR;
        int y2 = 1 + rectU;
        addSpecial(1, 1);
        addSpecial(x2, 1);
        addSpecial(x2, y2);
        addSpecial(1, y2);
    } else {
        // scenario 0 or 3: maybe start cell and some path cells
        if (rnd.next(0, 3) == 0) addSpecial(1, 1);
        if (!pathCells.empty() && (int)special.size() < N) {
            vector<pair<int,int>> tmp = pathCells;
            shuffle(tmp.begin(), tmp.end());
            int k = min((int)tmp.size(), rnd.next(1, min(N - (int)special.size(), 3)));
            for (int i = 0; i < k; i++) addSpecial(tmp[i].first, tmp[i].second);
        }
    }

    // Fill remaining boxes randomly from remaining cells
    shuffle(allCells.begin(), allCells.end());
    set<pair<int,int>> boxPos;
    vector<Box> boxes;
    boxes.reserve(N);

    for (auto p : special) {
        if ((int)boxes.size() >= N) break;
        if (boxPos.insert(p).second) {
            boxes.push_back({p.first, p.second, genWeight(scenario)});
        }
    }

    for (auto p : allCells) {
        if ((int)boxes.size() >= N) break;
        if (boxPos.insert(p).second) {
            boxes.push_back({p.first, p.second, genWeight(scenario)});
        }
    }

    // Output
    println(N, Q);
    for (const auto &b : boxes) {
        println(b.x, b.y, b.w);
    }
    for (auto mv : moves) {
        println(mv.first, mv.second);
    }

    return 0;
}
