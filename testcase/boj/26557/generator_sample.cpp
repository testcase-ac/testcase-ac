#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Pos {
    int z;
    int y;
    int x;
};

vector<vector<string>> makeMaze(int f, int r, int c, char fill) {
    return vector<vector<string>>(f, vector<string>(r, string(c, fill)));
}

void placeEndpoints(vector<vector<string>>& maze, Pos s, Pos e) {
    maze[s.z][s.y][s.x] = 'S';
    maze[e.z][e.y][e.x] = 'E';
}

void carveManhattanPath(vector<vector<string>>& maze, Pos cur, Pos target) {
    maze[cur.z][cur.y][cur.x] = '.';
    while (cur.z != target.z) {
        cur.z += (cur.z < target.z ? 1 : -1);
        maze[cur.z][cur.y][cur.x] = '.';
    }
    while (cur.y != target.y) {
        cur.y += (cur.y < target.y ? 1 : -1);
        maze[cur.z][cur.y][cur.x] = '.';
    }
    while (cur.x != target.x) {
        cur.x += (cur.x < target.x ? 1 : -1);
        maze[cur.z][cur.y][cur.x] = '.';
    }
}

vector<vector<string>> randomMaze(int f, int r, int c, int mode) {
    vector<vector<string>> maze;
    Pos s{rnd.next(f), rnd.next(r), rnd.next(c)};
    Pos e{s.z, s.y, s.x};
    while (e.z == s.z && e.y == s.y && e.x == s.x) {
        e = Pos{rnd.next(f), rnd.next(r), rnd.next(c)};
    }

    if (mode == 0) {
        maze = makeMaze(f, r, c, '#');
        carveManhattanPath(maze, s, e);
        int extraOpen = rnd.next(0, f * r * c / 3);
        for (int i = 0; i < extraOpen; ++i) {
            maze[rnd.next(f)][rnd.next(r)][rnd.next(c)] = '.';
        }
    } else if (mode == 1) {
        maze = makeMaze(f, r, c, '.');
        int wallPercent = rnd.next(20, 75);
        for (int z = 0; z < f; ++z) {
            for (int y = 0; y < r; ++y) {
                for (int x = 0; x < c; ++x) {
                    if (rnd.next(100) < wallPercent) {
                        maze[z][y][x] = '#';
                    }
                }
            }
        }
    } else if (mode == 2) {
        maze = makeMaze(f, r, c, '#');
        int corridorRow = rnd.next(r);
        int corridorCol = rnd.next(c);
        for (int z = 0; z < f; ++z) {
            for (int x = 0; x < c; ++x) {
                maze[z][corridorRow][x] = '.';
            }
            for (int y = 0; y < r; ++y) {
                maze[z][y][corridorCol] = '.';
            }
        }
        s = Pos{0, corridorRow, rnd.next(c)};
        e = Pos{f - 1, rnd.next(r), corridorCol};
    } else {
        maze = makeMaze(f, r, c, '#');
        for (int z = 0; z < f; ++z) {
            for (int y = 0; y < r; ++y) {
                for (int x = 0; x < c; ++x) {
                    if ((z + y + x + rnd.next(2)) % 3 == 0) {
                        maze[z][y][x] = '.';
                    }
                }
            }
        }
    }

    placeEndpoints(maze, s, e);
    return maze;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(3, 8);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(4);
        int f = rnd.next(1, 4);
        int r = rnd.next(1, 5);
        int c = rnd.next(2, 8);

        if (mode == 0 && rnd.next(2) == 0) {
            f = 1;
            r = 1;
            c = rnd.next(2, 15);
        }
        if (mode == 2) {
            f = rnd.next(2, 4);
            r = rnd.next(2, 5);
            c = rnd.next(2, 5);
        }

        println(f, r, c);
        vector<vector<string>> maze = randomMaze(f, r, c, mode);
        for (int z = 0; z < f; ++z) {
            for (int y = 0; y < r; ++y) {
                println(maze[z][y]);
            }
        }
    }

    return 0;
}
