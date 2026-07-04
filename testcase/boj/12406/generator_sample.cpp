#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static vector<string> makeRoom(int h, int w) {
    vector<string> room(h, string(w, '.'));
    for (int r = 0; r < h; ++r) {
        room[r][0] = '#';
        room[r][w - 1] = '#';
    }
    for (int c = 0; c < w; ++c) {
        room[0][c] = '#';
        room[h - 1][c] = '#';
    }
    return room;
}

static void placePerson(vector<string>& room) {
    int h = (int)room.size();
    int w = (int)room[0].size();
    int r = rnd.next(1, h - 2);
    int c = rnd.next(1, w - 2);
    room[r][c] = 'X';
}

static vector<string> generateCase(int h, int w, int mode) {
    vector<string> room = makeRoom(h, w);

    if (mode == 1) {
        int mirrors = rnd.next(1, max(1, (h - 2) * (w - 2) / 4));
        for (int i = 0; i < mirrors; ++i) {
            int r = rnd.next(1, h - 2);
            int c = rnd.next(1, w - 2);
            room[r][c] = '#';
        }
    } else if (mode == 2) {
        for (int r = 1; r < h - 1; ++r) {
            for (int c = 1; c < w - 1; ++c) {
                if (rnd.next(100) < 45) {
                    room[r][c] = '#';
                }
            }
        }
    } else if (mode == 3) {
        int rowGap = rnd.next(2, 3);
        int colGap = rnd.next(2, 3);
        for (int r = 1; r < h - 1; ++r) {
            for (int c = 1; c < w - 1; ++c) {
                if (r % rowGap == 0 || c % colGap == 0) {
                    room[r][c] = '#';
                }
            }
        }
    } else if (mode == 4) {
        int parity = rnd.next(0, 1);
        for (int r = 1; r < h - 1; ++r) {
            for (int c = 1; c < w - 1; ++c) {
                if ((r + c) % 2 == parity) {
                    room[r][c] = '#';
                }
            }
        }
    }

    placePerson(room);
    return room;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode = rnd.next(0, 4);
        int h;
        int w;
        if (caseIndex == 0 && rnd.next(100) < 35) {
            h = 3;
            w = 3;
            mode = 0;
        } else {
            h = rnd.next(3, 12);
            w = rnd.next(3, 12);
        }

        int d;
        if (rnd.next(100) < 25) {
            d = rnd.next(1, 3);
        } else if (rnd.next(100) < 25) {
            d = rnd.next(30, 50);
        } else {
            d = rnd.next(4, 20);
        }

        vector<string> room = generateCase(h, w, mode);
        println(h, w, d);
        for (const string& row : room) {
            println(row);
        }
    }

    return 0;
}
