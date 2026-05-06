#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 2000, "T");
    inf.readEoln();

    // Precompute all valid faces of the cube
    // Each face is a set of 4 indices
    vector< set<int> > faces;
    // Faces perpendicular to x-axis
    faces.push_back({0,1,2,3}); // x=0
    faces.push_back({4,5,6,7}); // x=1
    // Faces perpendicular to y-axis
    faces.push_back({0,1,4,5}); // y=0
    faces.push_back({2,3,6,7}); // y=1
    // Faces perpendicular to z-axis
    faces.push_back({0,2,4,6}); // z=0
    faces.push_back({1,3,5,7}); // z=1

    for (int tc = 0; tc < T; ++tc) {
        set<int> s;
        vector<int> vals(4);
        for (int i = 0; i < 4; ++i) {
            vals[i] = inf.readInt(0, 7, "vertex index");
            ensuref(0 <= vals[i] && vals[i] < 8, "vertex index %d out of range [0,7]", vals[i]);
            if (i < 3) inf.readSpace();
            s.insert(vals[i]);
        }
        inf.readEoln();

        ensuref((int)s.size() == 4, "Testcase %d: Indices are not all distinct: %d %d %d %d", tc+1, vals[0], vals[1], vals[2], vals[3]);
    }

    inf.readEof();
}
