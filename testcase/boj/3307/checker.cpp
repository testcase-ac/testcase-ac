#include "testlib.h"

#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-3;

struct Output {
    vector<double> radius;
};

Output readOutput(InStream& stream, int n) {
    Output output;
    output.radius.reserve(n);

    for (int i = 0; i < n; ++i) {
        output.radius.push_back(stream.readDouble());
        if (i + 1 < n) {
            stream.readEoln();
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d radii", n);
    }

    return output;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    Output jury = readOutput(ans, n);
    Output participant = readOutput(ouf, n);

    for (int i = 0; i < n; ++i) {
        double error = fabs(jury.radius[i] - participant.radius[i]);
        if (error > EPS) {
            quitf(_wa,
                  "radius[%d] differs: expected %.10f, found %.10f, error %.10f",
                  i + 1,
                  jury.radius[i],
                  participant.radius[i],
                  error);
        }
    }

    quitf(_ok, "%d radii are within tolerance", n);
}
