#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int caseNo = 0;
    // Read test cases until sentinel 0 0 0 0 0 0
    while (true) {
        // Read six integers with broad ranges to allow sentinel
        int w = inf.readInt(0, 1000, "w");
        inf.readSpace();
        int h = inf.readInt(0, 1000, "h");
        inf.readSpace();
        int x = inf.readInt(0, 1000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y");
        inf.readSpace();
        int s = inf.readInt(0, 99, "s");
        inf.readSpace();
        int r = inf.readInt(0, 359, "r");
        inf.readEoln();

        // Check for sentinel line
        if (w == 0 && h == 0 && x == 0 && y == 0 && s == 0 && r == 0) {
            break;
        }

        // Count and limit number of cases
        caseNo++;
        ensuref(caseNo <= MAX_CASES,
                "Number of test cases exceeds maximum of %d (at least %d)", 
                MAX_CASES, caseNo);

        // Validate basic constraints for a real test case
        ensuref(w > 0, "w must be > 0 in case %d; found %d", caseNo, w);
        ensuref(h > 0, "h must be > 0 in case %d; found %d", caseNo, h);
        ensuref(s > 0, "s (scale) must be > 0 in case %d; found %d", caseNo, s);
        ensuref(x <= w, "x must satisfy 0 <= x <= w in case %d; found x=%d, w=%d",
                caseNo, x, w);
        ensuref(y <= h, "y must satisfy 0 <= y <= h in case %d; found y=%d, h=%d",
                caseNo, y, h);

        // Validate the smaller (rotated) map lies entirely within the larger
        // Smaller map dimensions
        double sw = (double)w * s / 100.0;
        double sh = (double)h * s / 100.0;
        // Rotation angle in radians
        const double PI = acos(-1.0);
        double theta = r * PI / 180.0;
        double c = cos(theta);
        double sn = sin(theta);
        // The four corners of the smaller map before rotation
        vector<pair<double,double>> rel = {
            {0.0, 0.0},
            {sw,  0.0},
            {0.0,  sh},
            {sw,  sh}
        };
        // Check each corner after rotation + translation is within [0, w] x [0, h]
        for (int i = 0; i < 4; i++) {
            double dx = rel[i].first;
            double dy = rel[i].second;
            double X = x + dx * c - dy * sn;
            double Y = y + dx * sn + dy * c;
            // Allow tiny numerical slack
            const double EPS = 1e-8;
            ensuref(X >= -EPS && X <= w + EPS && Y >= -EPS && Y <= h + EPS,
                    "Smaller map goes out of bounds in case %d; corner %d at (%.9f, %.9f) not in [0,0]-[%d,%d]",
                    caseNo, i, X, Y, w, h);
        }
    }

    inf.readEof();
    return 0;
}
