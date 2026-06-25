#include "testlib.h"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static pair<string, string> makeOpenTrack(int n) {
    return {string(n, '.'), string(n, '.')};
}

static pair<string, string> makeSingleLaneTrack(int n, int lane) {
    string top(n, '#'), bottom(n, '#');
    string& row = lane == 0 ? top : bottom;
    fill(row.begin(), row.end(), '.');
    return {top, bottom};
}

static pair<string, string> makeAlternatingTrack(int n) {
    string top(n, '#'), bottom(n, '#');
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            top[i] = '.';
        } else {
            bottom[i] = '.';
        }
    }
    return {top, bottom};
}

static pair<string, string> makeRandomTrack(int n) {
    string top(n, '.'), bottom(n, '.');
    int obstaclePercent = rnd.next(15, 70);
    for (int i = 0; i < n; ++i) {
        top[i] = rnd.next(100) < obstaclePercent ? '#' : '.';
        bottom[i] = rnd.next(100) < obstaclePercent ? '#' : '.';
    }
    return {top, bottom};
}

static pair<string, string> makeBoundaryTrapTrack(int n) {
    string top(n, '.'), bottom(n, '.');
    if (rnd.next(2) == 0) {
        top[0] = '#';
    } else {
        bottom[0] = '#';
    }
    if (n > 1) {
        if (rnd.next(2) == 0) {
            top[n - 1] = '#';
        } else {
            bottom[n - 1] = '#';
        }
    }
    for (int i = 1; i + 1 < n; ++i) {
        if (rnd.next(100) < 35) {
            if (rnd.next(2) == 0) {
                top[i] = '#';
            } else {
                bottom[i] = '#';
            }
        }
    }
    return {top, bottom};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int m = rnd.next(1, 8);
    int k = rnd.next(1, 20);
    if (mode == 0) {
        m = 1;
        k = rnd.next(1, 12);
    } else if (mode == 1) {
        m = rnd.next(2, 4);
        k = rnd.next(8, 20);
    }

    vector<pair<string, string>> tracks;
    tracks.reserve(m);
    for (int i = 0; i < m; ++i) {
        int n = rnd.next(1, 12);
        if (mode == 2 && i == 0) {
            n = 1;
        } else if (mode == 3) {
            n = rnd.next(8, 18);
        }

        pair<string, string> track;
        int kind = rnd.next(6);
        if (mode == 4 && i == 0) {
            track = {string(n, '#'), string(n, '#')};
        } else if (kind == 0) {
            track = makeOpenTrack(n);
        } else if (kind == 1) {
            track = makeSingleLaneTrack(n, rnd.next(2));
        } else if (kind == 2) {
            track = makeAlternatingTrack(n);
        } else if (kind == 3) {
            track = makeBoundaryTrapTrack(n);
        } else {
            track = makeRandomTrack(n);
        }

        tracks.push_back(track);
    }

    vector<int> order(k);
    if (mode == 1) {
        for (int i = 0; i < k; ++i) {
            order[i] = i % m + 1;
        }
        if (rnd.next(2) == 0) {
            reverse(order.begin(), order.end());
        }
    } else if (mode == 5) {
        int a = rnd.next(1, m);
        int b = rnd.next(1, m);
        for (int i = 0; i < k; ++i) {
            order[i] = i % 3 == 0 ? b : a;
        }
    } else {
        for (int i = 0; i < k; ++i) {
            order[i] = rnd.next(1, m);
        }
    }

    println(m, k);
    println(order);
    for (const auto& [top, bottom] : tracks) {
        println(top);
        println(bottom);
    }

    return 0;
}
