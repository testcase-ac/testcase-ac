#include "testlib.h"
using namespace std;

struct CaseData {
    int w, h;
    vector<string> g;
};

CaseData makeRandomMixed() {
    CaseData c;
    c.w = rnd.next(1, 9);
    c.h = rnd.next(1, 9);
    c.g.assign(c.h, string(c.w, '.'));
    vector<pair<int,int>> empties;

    for (int i = 0; i < c.h; ++i) {
        for (int j = 0; j < c.w; ++j) {
            double x = rnd.next(); // [0,1)
            char ch;
            if (x < 0.20) ch = '#';
            else if (x < 0.35) ch = '*';
            else ch = '.';
            c.g[i][j] = ch;
            if (ch == '.') empties.push_back({i, j});
        }
    }

    if (empties.empty()) {
        int ri = rnd.next(0, c.h - 1);
        int rj = rnd.next(0, c.w - 1);
        c.g[ri][rj] = '.';
        empties.push_back({ri, rj});
    }

    pair<int,int> s = rnd.any(empties);
    c.g[s.first][s.second] = '@';

    return c;
}

CaseData makeBoxImpossible() {
    CaseData c;
    c.w = rnd.next(3, 9);
    c.h = rnd.next(3, 9);
    c.g.assign(c.h, string(c.w, '#'));

    vector<pair<int,int>> interior;
    for (int i = 1; i < c.h - 1; ++i) {
        for (int j = 1; j < c.w - 1; ++j) {
            if (rnd.next(0, 1) == 0) {
                c.g[i][j] = '.';
                interior.push_back({i, j});
            }
        }
    }

    if (interior.empty()) {
        int ri = c.h / 2;
        int rj = c.w / 2;
        c.g[ri][rj] = '.';
        interior.push_back({ri, rj});
    }

    pair<int,int> s = rnd.any(interior);
    c.g[s.first][s.second] = '@';

    // Place some fires inside, but not on '@'
    vector<pair<int,int>> fireCand;
    for (auto &p : interior) {
        if (!(p.first == s.first && p.second == s.second) && c.g[p.first][p.second] == '.')
            fireCand.push_back(p);
    }
    if (!fireCand.empty()) {
        int maxF = (int)fireCand.size();
        int k = rnd.next(0, max(0, min(maxF, (c.w * c.h) / 4)));
        shuffle(fireCand.begin(), fireCand.end());
        for (int i = 0; i < k; ++i) {
            c.g[fireCand[i].first][fireCand[i].second] = '*';
        }
    }

    return c;
}

CaseData makeImmediateEscape() {
    CaseData c;
    c.w = rnd.next(1, 9);
    c.h = rnd.next(1, 9);
    c.g.assign(c.h, string(c.w, '.'));

    vector<pair<int,int>> boundary;
    for (int i = 0; i < c.h; ++i) {
        for (int j = 0; j < c.w; ++j) {
            if (i == 0 || i == c.h - 1 || j == 0 || j == c.w - 1)
                boundary.push_back({i, j});
        }
    }

    pair<int,int> s = rnd.any(boundary);
    c.g[s.first][s.second] = '@';

    // Add walls and fires, but keep '@'
    for (int i = 0; i < c.h; ++i) {
        for (int j = 0; j < c.w; ++j) {
            if (i == s.first && j == s.second) continue;
            double x = rnd.next();
            if (x < 0.20) c.g[i][j] = '#';
            else if (x < 0.40) c.g[i][j] = '*';
            else c.g[i][j] = '.';
        }
    }

    return c;
}

CaseData makeCorridor() {
    CaseData c;
    bool horizontal = (rnd.next(0, 1) == 0);
    int n = rnd.next(2, 9);

    if (horizontal) {
        c.h = 1;
        c.w = n;
    } else {
        c.h = n;
        c.w = 1;
    }

    c.g.assign(c.h, string(c.w, '.'));

    int sPos = rnd.next(0, n - 1);
    int fPos;
    do {
        fPos = rnd.next(0, n - 1);
    } while (fPos == sPos);

    for (int idx = 0; idx < n; ++idx) {
        char ch;
        if (idx == sPos) ch = '@';
        else if (idx == fPos) ch = '*';
        else {
            double x = rnd.next();
            if (x < 0.15) ch = '#';
            else if (x < 0.35) ch = '*';
            else ch = '.';
        }

        if (horizontal)
            c.g[0][idx] = ch;
        else
            c.g[idx][0] = ch;
    }

    return c;
}

CaseData makeNoFire() {
    CaseData c;
    c.w = rnd.next(1, 9);
    c.h = rnd.next(1, 9);
    c.g.assign(c.h, string(c.w, '.'));

    vector<pair<int,int>> empties;
    for (int i = 0; i < c.h; ++i) {
        for (int j = 0; j < c.w; ++j) {
            double x = rnd.next();
            if (x < 0.25) c.g[i][j] = '#';
            else c.g[i][j] = '.';
            if (c.g[i][j] == '.') empties.push_back({i, j});
        }
    }

    if (empties.empty()) {
        int ri = rnd.next(0, c.h - 1);
        int rj = rnd.next(0, c.w - 1);
        c.g[ri][rj] = '.';
        empties.push_back({ri, rj});
    }

    pair<int,int> s = rnd.any(empties);
    c.g[s.first][s.second] = '@';

    return c;
}

CaseData makeDenseFire() {
    CaseData c;
    c.w = rnd.next(1, 9);
    c.h = rnd.next(1, 9);
    c.g.assign(c.h, string(c.w, '.'));

    vector<pair<int,int>> empties;
    for (int i = 0; i < c.h; ++i) {
        for (int j = 0; j < c.w; ++j) {
            double x = rnd.next();
            if (x < 0.10) c.g[i][j] = '#';
            else if (x < 0.80) c.g[i][j] = '*';
            else c.g[i][j] = '.';
            if (c.g[i][j] == '.') empties.push_back({i, j});
        }
    }

    if (empties.empty()) {
        int ri = rnd.next(0, c.h - 1);
        int rj = rnd.next(0, c.w - 1);
        c.g[ri][rj] = '.';
        empties.push_back({ri, rj});
    }

    pair<int,int> s = rnd.any(empties);
    c.g[s.first][s.second] = '@';

    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        CaseData c;
        if (T >= 2 && tc == 0) {
            c = makeBoxImpossible();
        } else if (T >= 2 && tc == 1) {
            c = makeImmediateEscape();
        } else {
            int typ = rnd.next(0, 5);
            if (typ == 0) c = makeRandomMixed();
            else if (typ == 1) c = makeCorridor();
            else if (typ == 2) c = makeNoFire();
            else if (typ == 3) c = makeDenseFire();
            else if (typ == 4) c = makeBoxImpossible();
            else c = makeImmediateEscape();
        }

        println(c.w, c.h);
        for (int i = 0; i < c.h; ++i) {
            println(c.g[i]);
        }
    }

    return 0;
}
