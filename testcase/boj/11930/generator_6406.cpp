#include "testlib.h"
#include <vector>
#include <array>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<string> scen = {"single", "line", "plane", "random"};
    string sc = scen[rnd.next(0, (int)scen.size() - 1)];

    vector<array<int,3>> pts;
    if (sc == "single") {
        int x = rnd.next(-10, 10), y = rnd.next(-10, 10), z = rnd.next(-10, 10);
        pts.push_back({x, y, z});
    }
    else if (sc == "line") {
        int N = rnd.next(2, 5);
        array<int,3> p1 = {rnd.next(-5,5), rnd.next(-5,5), rnd.next(-5,5)}, p2;
        do {
            p2 = {rnd.next(-5,5), rnd.next(-5,5), rnd.next(-5,5)};
        } while (p2 == p1);
        array<int,3> v = {p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]};
        for (int i = 0; i < N; i++) {
            int k = rnd.next(0, 3);
            pts.push_back({p1[0] + v[0]*k, p1[1] + v[1]*k, p1[2] + v[2]*k});
        }
    }
    else if (sc == "plane") {
        int N = rnd.next(3, 6);
        array<int,3> p1, p2, p3;
        while (true) {
            p1 = {rnd.next(-5,5), rnd.next(-5,5), rnd.next(-5,5)};
            p2 = {rnd.next(-5,5), rnd.next(-5,5), rnd.next(-5,5)};
            p3 = {rnd.next(-5,5), rnd.next(-5,5), rnd.next(-5,5)};
            array<int,3> v2 = {p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]};
            array<int,3> v3 = {p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]};
            array<int,3> cr = {
                v2[1]*v3[2] - v2[2]*v3[1],
                v2[2]*v3[0] - v2[0]*v3[2],
                v2[0]*v3[1] - v2[1]*v3[0]
            };
            if (cr[0] != 0 || cr[1] != 0 || cr[2] != 0) break;
        }
        array<int,3> v2 = {p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]};
        array<int,3> v3 = {p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]};
        for (int i = 0; i < N; i++) {
            int a = rnd.next(-2,2), b = rnd.next(-2,2);
            pts.push_back({
                p1[0] + v2[0]*a + v3[0]*b,
                p1[1] + v2[1]*a + v3[1]*b,
                p1[2] + v2[2]*a + v3[2]*b
            });
        }
    }
    else {
        int N = rnd.next(1, 10);
        for (int i = 0; i < N; i++) {
            pts.push_back({rnd.next(-10,10), rnd.next(-10,10), rnd.next(-10,10)});
        }
    }

    shuffle(pts.begin(), pts.end());
    println((int)pts.size());
    for (auto &p : pts)
        println(p[0], p[1], p[2]);
    return 0;
}
