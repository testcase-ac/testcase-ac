#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int Lx = inf.readInt(1, 1000, "Lx");
    inf.readSpace();
    int Ly = inf.readInt(1, 1000, "Ly");
    inf.readSpace();
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    for (int i = 1; i <= N; ++i) {
        int lx = inf.readInt(1, Lx, "lx");
        inf.readSpace();
        int ly = inf.readInt(1, Ly, "ly");
        inf.readSpace();
        inf.readInt(1, 100000, "lz");
        inf.readSpace();
        int px = inf.readInt(0, Lx - lx, "px");
        inf.readSpace();
        int py = inf.readInt(0, Ly - ly, "py");
        inf.readEoln();

        ensuref(px + lx <= Lx,
                "box %d exceeds warehouse length: px=%d lx=%d Lx=%d",
                i, px, lx, Lx);
        ensuref(py + ly <= Ly,
                "box %d exceeds warehouse depth: py=%d ly=%d Ly=%d",
                i, py, ly, Ly);
    }

    inf.readEof();
    return 0;
}
