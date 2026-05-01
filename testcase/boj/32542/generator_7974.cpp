#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Classic Koch snowflake segment (upward peak)
        int n = 5;
        vector<pair<double,double>> pts = {
            {0.0, 0.0},
            {1.0/3.0, 0.0},
            {0.5,       sqrt(3.0)/6.0},
            {2.0/3.0,  0.0},
            {1.0,       0.0}
        };
        printf("%d\n", n);
        for (auto &p : pts)
            printf("%.6f %.6f\n", p.first, p.second);
    } else if (type == 1) {
        // Mirrored Koch (downward peak)
        int n = 5;
        vector<pair<double,double>> pts = {
            {0.0, 0.0},
            {1.0/3.0, 0.0},
            {0.5,      -sqrt(3.0)/6.0},
            {2.0/3.0,  0.0},
            {1.0,       0.0}
        };
        printf("%d\n", n);
        for (auto &p : pts)
            printf("%.6f %.6f\n", p.first, p.second);
    } else if (type == 2) {
        // Flat segment (all y = 0), variable n
        int n = rnd.next(2, 10);
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            double x = (double)i / (n - 1);
            printf("%.6f %.6f\n", x, 0.0);
        }
    } else {
        // Random wiggly polyline
        int n = rnd.next(3, 12);
        vector<double> xs;
        xs.push_back(0.0);
        for (int i = 0; i < n - 2; i++) {
            int xi = rnd.next(1, 999998);
            xs.push_back(xi / 1e6);
        }
        xs.push_back(1.0);
        sort(xs.begin() + 1, xs.end() - 1);
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            double x = xs[i];
            double y = 0.0;
            if (i != 0 && i != n - 1) {
                int yi = rnd.next(-499999, 499999);
                y = yi / 1e6;
            }
            printf("%.6f %.6f\n", x, y);
        }
    }
    return 0;
}
