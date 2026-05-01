#include "testlib.h"
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Vec {
    double x, y, z;
    Vec operator + (const Vec& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec operator - (const Vec& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vec operator * (double s) const { return {x*s, y*s, z*s}; }
};

double dot(const Vec& a, const Vec& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec cross(const Vec& a, const Vec& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

double norm(const Vec& a) {
    return sqrt(dot(a,a));
}

Vec normalize(const Vec& a) {
    double n = norm(a);
    return {a.x/n, a.y/n, a.z/n};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const double EPS = 1e-6;
    const double PI = acos(-1.0);

    // number of darts
    int n = rnd.next(1, 10);

    // Choose two perpendicular axes for the ellipse from coordinate axes
    int axisH = rnd.next(0, 2);
    int offset = rnd.next(1, 2);
    int axisV = (axisH + offset) % 3;

    double lenH = rnd.next(1.0, 5.0) * (rnd.next(0,1) ? 1.0 : -1.0);
    double lenV = rnd.next(1.0, 5.0) * (rnd.next(0,1) ? 1.0 : -1.0);

    Vec h = {0, 0, 0}, v = {0, 0, 0};
    if (axisH == 0) h.x = lenH;
    if (axisH == 1) h.y = lenH;
    if (axisH == 2) h.z = lenH;
    if (axisV == 0) v.x = lenV;
    if (axisV == 1) v.y = lenV;
    if (axisV == 2) v.z = lenV;

    // Plane normal
    Vec nrm = cross(h, v);

    // Probability of hit
    double hitProb = rnd.next(0.2, 0.8);

    // Output board
    println(n);
    println(h.x, h.y, h.z);
    println(v.x, v.y, v.z);

    for (int i = 0; i < n; i++) {
        if (rnd.next() < hitProb) {
            // Hit case: intersection at X inside ellipse, t >= 0
            double theta = rnd.next(0.0, 2*PI);
            double r = sqrt(rnd.next());
            double s = r * cos(theta), t = r * sin(theta);
            Vec X = h * s + v * t;
            double u = (rnd.next() < 0.2 ? 0.0 : rnd.next(0.1, 10.0));
            // random direction
            Vec d0;
            do {
                d0.x = rnd.next(-1.0, 1.0);
                d0.y = rnd.next(-1.0, 1.0);
                d0.z = rnd.next(-1.0, 1.0);
            } while (norm(d0) < EPS);
            Vec d = normalize(d0);
            Vec p = X - d * u;
            println(p.x, p.y, p.z, d.x, d.y, d.z);
        } else {
            int missType = rnd.next(0, 2);
            if (missType == 0) {
                // Miss: intersection exists but outside ellipse
                double theta = rnd.next(0.0, 2*PI);
                double rr = rnd.next(1.2, 2.0);
                double s = rr * cos(theta), t = rr * sin(theta);
                Vec X = h * s + v * t;
                double u = rnd.next(0.1, 10.0);
                Vec d0;
                do {
                    d0.x = rnd.next(-1.0, 1.0);
                    d0.y = rnd.next(-1.0, 1.0);
                    d0.z = rnd.next(-1.0, 1.0);
                } while (norm(d0) < EPS);
                Vec d = normalize(d0);
                Vec p = X - d * u;
                println(p.x, p.y, p.z, d.x, d.y, d.z);
            } else if (missType == 1) {
                // Miss: ray parallel to plane, no intersection
                Vec d0;
                do {
                    double a = rnd.next(-1.0, 1.0);
                    double b = rnd.next(-1.0, 1.0);
                    d0 = h * a + v * b;
                } while (norm(d0) < EPS);
                Vec d = normalize(d0);
                Vec p;
                do {
                    p.x = rnd.next(-100.0, 100.0);
                    p.y = rnd.next(-100.0, 100.0);
                    p.z = rnd.next(-100.0, 100.0);
                } while (fabs(dot(p, nrm)) < EPS);
                println(p.x, p.y, p.z, d.x, d.y, d.z);
            } else {
                // Miss: intersection behind start point (t < 0)
                double theta = rnd.next(0.0, 2*PI);
                double r = sqrt(rnd.next());
                double s = r * cos(theta), t = r * sin(theta);
                Vec X = h * s + v * t;
                double u = -rnd.next(0.1, 10.0);
                Vec d0;
                do {
                    d0.x = rnd.next(-1.0, 1.0);
                    d0.y = rnd.next(-1.0, 1.0);
                    d0.z = rnd.next(-1.0, 1.0);
                } while (norm(d0) < EPS);
                Vec d = normalize(d0);
                Vec p = X - d * u;
                println(p.x, p.y, p.z, d.x, d.y, d.z);
            }
        }
    }
    return 0;
}
