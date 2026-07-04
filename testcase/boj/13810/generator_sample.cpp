#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Futon {
    long long x;
    long long y;
    char dir;
};

bool addFuton(vector<Futon>& futons, set<pair<long long, long long>>& occupied,
              long long x, long long y, char dir) {
    pair<long long, long long> a = {x, y};
    pair<long long, long long> b = dir == 'x' ? make_pair(x + 1, y) : make_pair(x, y + 1);
    if (occupied.count(a) || occupied.count(b)) {
        return false;
    }

    occupied.insert(a);
    occupied.insert(b);
    futons.push_back({x, y, dir});
    return true;
}

vector<Futon> denseGridDataset() {
    vector<Futon> futons;
    set<pair<long long, long long>> occupied;

    int width = rnd.next(3, 8);
    int height = rnd.next(3, 8);
    vector<pair<int, int>> cells;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cells.push_back({x, y});
        }
    }
    shuffle(cells.begin(), cells.end());

    int target = rnd.next(3, min(16, width * height / 2));
    for (auto [x, y] : cells) {
        vector<char> dirs;
        if (x + 1 < width) dirs.push_back('x');
        if (y + 1 < height) dirs.push_back('y');
        shuffle(dirs.begin(), dirs.end());

        for (char dir : dirs) {
            if (addFuton(futons, occupied, x, y, dir)) {
                break;
            }
        }
        if ((int)futons.size() >= target) {
            break;
        }
    }

    return futons;
}

vector<Futon> sparseDataset() {
    vector<Futon> futons;
    set<pair<long long, long long>> occupied;

    int n = rnd.next(1, 12);
    long long baseX = rnd.next(0LL, 30LL);
    long long baseY = rnd.next(0LL, 30LL);
    for (int i = 0; i < n; ++i) {
        for (int attempt = 0; attempt < 100; ++attempt) {
            long long x = baseX + rnd.next(0LL, 40LL);
            long long y = baseY + rnd.next(0LL, 40LL);
            char dir = rnd.next(0, 1) == 0 ? 'x' : 'y';
            if (addFuton(futons, occupied, x, y, dir)) {
                break;
            }
        }
    }

    return futons;
}

vector<Futon> boundaryDataset() {
    vector<Futon> futons;
    set<pair<long long, long long>> occupied;
    constexpr long long kMaxCoord = 1000000000LL;

    long long anchor = rnd.next(kMaxCoord - 20, kMaxCoord);
    addFuton(futons, occupied, anchor, anchor, 'x');
    addFuton(futons, occupied, anchor - 3, anchor, 'y');
    addFuton(futons, occupied, 0, anchor, 'y');
    addFuton(futons, occupied, anchor, 0, 'x');

    int extra = rnd.next(0, 4);
    for (int i = 0; i < extra; ++i) {
        long long x = rnd.next(0LL, 15LL);
        long long y = kMaxCoord - rnd.next(0LL, 15LL);
        char dir = rnd.next(0, 1) == 0 ? 'x' : 'y';
        addFuton(futons, occupied, x, y, dir);
    }

    return futons;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(3, 6);
    for (int tc = 0; tc < datasets; ++tc) {
        vector<Futon> futons;
        int mode = tc == 0 ? 0 : rnd.next(0, 2);
        if (mode == 0) {
            futons = denseGridDataset();
        } else if (mode == 1) {
            futons = sparseDataset();
        } else {
            futons = boundaryDataset();
        }

        println((int)futons.size());
        shuffle(futons.begin(), futons.end());
        for (const Futon& futon : futons) {
            println(futon.x, futon.y, string(1, futon.dir));
        }
    }
    println(0);

    return 0;
}
