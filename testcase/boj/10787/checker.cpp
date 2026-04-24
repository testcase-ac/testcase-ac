#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-6;
double PI = acos(-1.0);

int n, s;
vector<double> r, x, y, z;

// Read and validate an answer (jury or contestant), compute slice cheese volumes.
vector<double> readAns(InStream &st) {
    // read thicknesses
    vector<double> t(s);
    double sum_t = 0;
    for (int i = 0; i < s; i++) {
        t[i] = st.readDouble();
        if (t[i] < 0)
            st.quitf(_wa, "thickness[%d] = %f is negative", i+1, t[i]);
        sum_t += t[i];
    }
    // check total thickness = 100 mm
    double tol = EPS * max(100.0, sum_t);
    if (fabs(sum_t - 100.0) > tol)
        st.quitf(_wa, "sum of thicknesses = %f, expected 100.0", sum_t);

    // compute the cheese volume in each slice
    vector<double> vols(s, 0.0);
    double z0 = 0.0;
    for (int i = 0; i < s; i++) {
        double z1 = z0;
        double z2 = z0 + t[i];
        // volume of block slice
        double blockVol = 100.0 * 100.0 * (z2 - z1);
        // subtract hole volumes
        double holeVol = 0.0;
        for (int j = 0; j < n; j++) {
            double lo = max(z1, z[j] - r[j]);
            double hi = min(z2, z[j] + r[j]);
            if (hi > lo) {
                // integral of circle area: V = π [ r^2 * (hi-lo) - ((hi-c)^3 - (lo-c)^3)/3 ]
                double a = hi - z[j];
                double b = lo - z[j];
                double seg = PI * ( r[j]*r[j] * (hi - lo)
                    - (a*a*a - b*b*b) / 3.0 );
                holeVol += seg;
            }
        }
        vols[i] = blockVol - holeVol;
        z0 = z2;
    }
    return vols;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    n = inf.readInt();
    s = inf.readInt();
    r.resize(n);
    x.resize(n);
    y.resize(n);
    z.resize(n);
    for (int i = 0; i < n; i++) {
        // input in micrometers, convert to mm
        double ri = inf.readInt();
        double xi = inf.readInt();
        double yi = inf.readInt();
        double zi = inf.readInt();
        r[i] = ri / 1000.0;
        x[i] = xi / 1000.0;
        y[i] = yi / 1000.0;
        z[i] = zi / 1000.0;
    }

    // read jury and participant answers
    vector<double> jvol = readAns(ans);
    vector<double> pvol = readAns(ouf);

    // compare volumes slice by slice
    for (int i = 0; i < s; i++) {
        if (!doubleCompare(jvol[i], pvol[i], EPS)) {
            quitf(_wa,
                  "slice %d volume differs: expected %.9f, found %.9f",
                  i+1, jvol[i], pvol[i]);
        }
    }
    quitf(_ok, "correct");
    return 0;
}
