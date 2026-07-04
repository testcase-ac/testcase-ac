#include "testlib.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Vec3 {
    int x;
    int y;
    int z;
};

static long double norm(const Vec3& v) {
    return sqrtl(1.0L * v.x * v.x + 1.0L * v.y * v.y + 1.0L * v.z * v.z);
}

static long double angleBetween(const Vec3& a, const Vec3& b) {
    long double cosine = (1.0L * a.x * b.x + 1.0L * a.y * b.y + 1.0L * a.z * b.z) / (norm(a) * norm(b));
    if (cosine < -1.0L) {
        cosine = -1.0L;
    }
    if (cosine > 1.0L) {
        cosine = 1.0L;
    }
    return acosl(cosine);
}

static Vec3 randomVector(int limit) {
    while (true) {
        Vec3 v{rnd.next(-limit, limit), rnd.next(-limit, limit), rnd.next(-limit, limit)};
        if (v.x != 0 || v.y != 0 || v.z != 0) {
            return v;
        }
    }
}

static Vec3 axisVector() {
    int axis = rnd.next(0, 2);
    int sign = rnd.next(0, 1) == 0 ? -1 : 1;
    Vec3 v{0, 0, 0};
    if (axis == 0) {
        v.x = sign;
    } else if (axis == 1) {
        v.y = sign;
    } else {
        v.z = sign;
    }
    return v;
}

static vector<Vec3> makeVectors(int count, int mode) {
    vector<Vec3> values;
    Vec3 base = randomVector(4);
    for (int i = 0; i < count; ++i) {
        if (mode == 0) {
            values.push_back(axisVector());
        } else if (mode == 1) {
            Vec3 v{base.x + rnd.next(-2, 2), base.y + rnd.next(-2, 2), base.z + rnd.next(-2, 2)};
            if (v.x == 0 && v.y == 0 && v.z == 0) {
                v.x = base.x == 0 ? 1 : base.x;
            }
            values.push_back(v);
        } else {
            values.push_back(randomVector(rnd.next(3, 12)));
        }
    }
    return values;
}

static long double chooseRadius(const vector<Vec3>& stars, const Vec3& telescope) {
    const long double pi = acosl(-1.0L);
    vector<long double> candidates = {
        0.0L,
        0.0001L,
        0.12L,
        0.35L,
        0.70L,
        1.05L,
        pi / 2.0L - 0.0001L,
        pi / 2.0L - 0.00001L
    };
    shuffle(candidates.begin(), candidates.end());

    for (long double psi : candidates) {
        bool ok = true;
        for (const Vec3& star : stars) {
            if (fabsl(angleBetween(star, telescope) - psi) <= 0.000001L) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return psi;
        }
    }

    return 0.54321L;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 4);
    cout << fixed << setprecision(10);

    for (int tc = 0; tc < datasets; ++tc) {
        int mode = rnd.next(0, 2);
        int n = rnd.next(1, mode == 2 ? 12 : 8);
        int m = rnd.next(1, mode == 2 ? 7 : 5);
        vector<Vec3> stars = makeVectors(n, mode);
        vector<Vec3> telescopes = makeVectors(m, (mode + rnd.next(0, 2)) % 3);

        cout << n << '\n';
        for (const Vec3& star : stars) {
            cout << star.x << ' ' << star.y << ' ' << star.z << '\n';
        }

        cout << m << '\n';
        for (const Vec3& telescope : telescopes) {
            cout << telescope.x << ' ' << telescope.y << ' ' << telescope.z << ' '
                 << static_cast<double>(chooseRadius(stars, telescope)) << '\n';
        }
    }

    cout << 0 << '\n';
    return 0;
}
