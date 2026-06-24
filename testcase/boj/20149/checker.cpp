#include "testlib.h"

using namespace std;

const double EPS = 1e-9;

struct Answer {
    int intersects;
    bool hasPoint;
    double x;
    double y;
};

Answer readAnswer(InStream& stream) {
    Answer answer{};
    answer.intersects = stream.readInt(0, 1, "intersection flag");

    if (stream.seekEof()) {
        answer.hasPoint = false;
        return answer;
    }

    answer.hasPoint = true;
    answer.x = stream.readDouble(-1e18, 1e18, "intersection x");
    answer.y = stream.readDouble(-1e18, 1e18, "intersection y");
    if (!stream.seekEof()) {
        stream.readEof();
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.intersects == 0 && jury.hasPoint) {
        quitf(_fail, "jury printed an intersection point while answer is 0");
    }
    if (participant.intersects != jury.intersects) {
        quitf(_wa, "expected intersection flag %d, found %d",
              jury.intersects, participant.intersects);
    }

    if (!jury.hasPoint) {
        if (participant.hasPoint) {
            quitf(_wa, "participant printed an unexpected intersection point");
        }
        quitf(_ok, "intersection flag %d", participant.intersects);
    }

    if (jury.intersects == 0) {
        quitf(_fail, "jury printed an intersection point while answer is 0");
    }
    if (!participant.hasPoint) {
        quitf(_wa, "participant did not print the required intersection point");
    }
    if (!doubleCompare(jury.x, participant.x, EPS) ||
        !doubleCompare(jury.y, participant.y, EPS)) {
        quitf(_wa,
              "expected point (%.17g, %.17g), found (%.17g, %.17g)",
              jury.x, jury.y, participant.x, participant.y);
    }

    quitf(_ok, "intersection point is within tolerance");
}
