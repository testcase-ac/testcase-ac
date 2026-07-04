#include "testlib.h"

#include <cmath>
#include <string>
#include <vector>

using namespace std;

struct Vec3 {
    long double x;
    long double y;
    long double z;
};

static long double norm(const Vec3& v) {
    return sqrtl(v.x * v.x + v.y * v.y + v.z * v.z);
}

static Vec3 readVector(const string& prefix) {
    Vec3 v;
    v.x = inf.readDouble(-1000.0, 1000.0, (prefix + "_x").c_str());
    inf.readSpace();
    v.y = inf.readDouble(-1000.0, 1000.0, (prefix + "_y").c_str());
    inf.readSpace();
    v.z = inf.readDouble(-1000.0, 1000.0, (prefix + "_z").c_str());
    ensuref(norm(v) > 0.0L, "%s vector must be nonzero", prefix.c_str());
    return v;
}

static long double angleBetween(const Vec3& a, const Vec3& b) {
    long double cosine = (a.x * b.x + a.y * b.y + a.z * b.z) / (norm(a) * norm(b));
    if (cosine < -1.0L) {
        cosine = -1.0L;
    }
    if (cosine > 1.0L) {
        cosine = 1.0L;
    }
    return acosl(cosine);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long double pi = acosl(-1.0L);
    int datasets = 0;

    while (true) {
        int n = inf.readInt(0, 500, "n");
        inf.readEoln();
        if (n == 0) {
            break;
        }
        ++datasets;
        ensuref(datasets < 50, "number of datasets must be less than 50");

        vector<Vec3> stars(n);
        for (int i = 0; i < n; ++i) {
            stars[i] = readVector("s_" + to_string(i + 1));
            inf.readEoln();
        }

        int m = inf.readInt(1, 50, "m");
        inf.readEoln();

        vector<Vec3> telescopes(m);
        vector<long double> psi(m);
        for (int i = 0; i < m; ++i) {
            telescopes[i] = readVector("t_" + to_string(i + 1));
            inf.readSpace();
            psi[i] = inf.readDouble(0.0, static_cast<double>(pi / 2.0L), ("psi_" + to_string(i + 1)).c_str());
            inf.readEoln();
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                long double theta = angleBetween(stars[i], telescopes[j]);
                ensuref(fabsl(theta - psi[j]) > 0.00000001L,
                        "theta and psi too close for star %d and telescope %d", i + 1, j + 1);
            }
        }
    }

    ensuref(datasets >= 1, "input must contain at least one dataset");
    inf.readEof();
}
