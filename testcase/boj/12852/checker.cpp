#include "testlib.h"
#include <vector>
using namespace std;

int n;

struct Answer {
    int operations;
};

bool validStep(int from, int to) {
    if (from - 1 == to) return true;
    if (from % 2 == 0 && from / 2 == to) return true;
    if (from % 3 == 0 && from / 3 == to) return true;
    return false;
}

Answer readAnswer(InStream& stream) {
    int operations = stream.readInt(0, 1000000, "operation count");
    vector<int> path(operations + 1);

    for (int i = 0; i <= operations; ++i) {
        path[i] = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after path");
    }

    if (path.front() != n) {
        stream.quitf(_wa, "path starts at %d instead of %d", path.front(), n);
    }
    if (path.back() != 1) {
        stream.quitf(_wa, "path ends at %d instead of 1", path.back());
    }
    for (int i = 0; i < operations; ++i) {
        if (!validStep(path[i], path[i + 1])) {
            stream.quitf(_wa,
                         "invalid operation from path[%d]=%d to path[%d]=%d",
                         i + 1, path[i], i + 2, path[i + 1]);
        }
    }

    return {operations};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer part = readAnswer(ouf);

    if (part.operations < jury.operations) {
        quitf(_fail,
              "participant found shorter valid path: jury=%d participant=%d",
              jury.operations, part.operations);
    }
    if (part.operations > jury.operations) {
        quitf(_wa,
              "path is not optimal: jury=%d participant=%d",
              jury.operations, part.operations);
    }

    quitf(_ok, "valid optimal path with %d operations", part.operations);
}
