#include "testlib.h"

#include <array>

using namespace std;

const double EPS = 1e-4;
const double MIN_VALUE = -1e100;
const double MAX_VALUE = 1e100;

array<double, 3> readCase(InStream& stream, int case_id) {
    array<double, 3> values;
    values[0] = stream.readDouble(MIN_VALUE, MAX_VALUE, format("landing position in case %d", case_id));
    values[1] = stream.readDouble(MIN_VALUE, MAX_VALUE, format("landing speed in case %d", case_id));
    values[2] = stream.readDouble(MIN_VALUE, MAX_VALUE, format("landing angle in case %d", case_id));
    return values;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int case_id = 1; case_id <= t; ++case_id) {
        array<double, 3> jury = readCase(ans, case_id);
        array<double, 3> participant = readCase(ouf, case_id);

        for (int field = 0; field < 3; ++field) {
            if (!doubleCompare(jury[field], participant[field], EPS)) {
                quitf(_wa,
                      "case %d field %d: expected %.10f, found %.10f, error %.10f",
                      case_id,
                      field + 1,
                      jury[field],
                      participant[field],
                      doubleDelta(jury[field], participant[field]));
            }
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d case(s) are within tolerance", t);
}
