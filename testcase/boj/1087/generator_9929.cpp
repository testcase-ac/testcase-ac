#include "testlib.h"
using namespace std;

struct Mouse {
    int px, py, vx, vy;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Mouse> mice;

    int type = rnd.next(0, 6); // 7 different scenario types (0..6)

    if (type == 0) {
        // Generic small random case
        int N = rnd.next(2, 7);
        mice.resize(N);
        bool anyMoving = false;
        for (int i = 0; i < N; i++) {
            mice[i].px = rnd.next(-20, 20);
            mice[i].py = rnd.next(-20, 20);
            mice[i].vx = rnd.next(-5, 5);
            mice[i].vy = rnd.next(-5, 5);
            if (mice[i].vx != 0 || mice[i].vy != 0) anyMoving = true;
        }
        // Ensure at least one mouse moves
        if (!anyMoving) {
            mice[0].vx = 1;
            mice[0].vy = 0;
        }
    } else if (type == 1) {
        // All mice share the same velocity (effectively static relative positions)
        int N = rnd.next(3, 8);
        mice.resize(N);
        int vx0 = 0, vy0 = 0;
        while (vx0 == 0 && vy0 == 0) {
            vx0 = rnd.next(-5, 5);
            vy0 = rnd.next(-5, 5);
        }
        for (int i = 0; i < N; i++) {
            mice[i].px = rnd.next(-30, 30);
            mice[i].py = rnd.next(-30, 30);
            mice[i].vx = vx0;
            mice[i].vy = vy0;
        }
    } else if (type == 2) {
        // Two groups moving towards each other along x-axis
        int N = 2 * rnd.next(2, 5); // 4,6,8
        mice.clear();
        int s = rnd.next(1, 5);
        int yBase = rnd.next(-5, 5);
        for (int i = 0; i < N / 2; i++) {
            Mouse m;
            m.px = rnd.next(-20, -5);
            m.py = yBase + rnd.next(-3, 3);
            m.vx = s;
            m.vy = 0;
            mice.push_back(m);
        }
        for (int i = 0; i < N / 2; i++) {
            Mouse m;
            m.px = rnd.next(5, 20);
            m.py = yBase + rnd.next(-3, 3);
            m.vx = -s;
            m.vy = 0;
            mice.push_back(m);
        }
    } else if (type == 3) {
        // Rectangular loop: four corners with orthogonal velocities (like example 4 but varied)
        mice.clear();
        int L0 = rnd.next(5, 15);
        int speed = rnd.next(1, 3);
        Mouse m1{0, 0, speed, 0};
        Mouse m2{L0, 0, 0, speed};
        Mouse m3{L0, L0, -speed, 0};
        Mouse m4{0, L0, 0, -speed};
        mice.push_back(m1);
        mice.push_back(m2);
        mice.push_back(m3);
        mice.push_back(m4);
    } else if (type == 4) {
        // Cluster plus one distant fast mouse
        mice.clear();
        int clusterN = rnd.next(2, 4);
        for (int i = 0; i < clusterN; i++) {
            Mouse m;
            m.px = rnd.next(-5, 5);
            m.py = rnd.next(-5, 5);
            m.vx = rnd.next(-2, 2);
            m.vy = rnd.next(-2, 2);
            mice.push_back(m);
        }
        Mouse out;
        out.px = rnd.next(40, 80);
        out.py = rnd.next(-5, 5);
        out.vx = rnd.next(-10, -3);
        out.vy = rnd.next(-2, 2);
        mice.push_back(out);
    } else if (type == 5) {
        // 1D motion along x-axis only
        int N = rnd.next(3, 10);
        mice.resize(N);
        bool anyMoving = false;
        for (int i = 0; i < N; i++) {
            mice[i].px = rnd.next(-30, 30);
            mice[i].py = rnd.next(-10, 10);
            mice[i].vx = rnd.next(-5, 5);
            mice[i].vy = 0;
            if (mice[i].vx != 0) anyMoving = true;
        }
        if (!anyMoving) {
            mice[0].vx = 1;
        }
    } else if (type == 6) {
        // Use one of the official examples directly
        int which = rnd.next(1, 6);
        mice.clear();
        if (which == 1) {
            // Example 1
            mice.push_back(Mouse{0, 0, 10, 0});
            mice.push_back(Mouse{10, 10, -10, 0});
        } else if (which == 2) {
            // Example 2
            mice.push_back(Mouse{0, 0, 1, 4});
            mice.push_back(Mouse{10, 0, -6, 5});
            mice.push_back(Mouse{0, 10, 4, -4});
        } else if (which == 3) {
            // Example 3
            mice.push_back(Mouse{50, -10, -5, 40});
            mice.push_back(Mouse{10, 30, -10, -10});
            mice.push_back(Mouse{30, 20, -15, -1});
            mice.push_back(Mouse{15, 40, -5, -50});
        } else if (which == 4) {
            // Example 4
            mice.push_back(Mouse{0, 0, 1, 0});
            mice.push_back(Mouse{10, 0, 0, 1});
            mice.push_back(Mouse{10, 10, -1, 0});
            mice.push_back(Mouse{0, 10, 0, -1});
        } else if (which == 5) {
            // Example 5
            mice.push_back(Mouse{13, 20, 4, 1});
            mice.push_back(Mouse{50, 20, 50, 1});
            mice.push_back(Mouse{100, -150, 41, 1});
            mice.push_back(Mouse{40, -40, -41, 3});
            mice.push_back(Mouse{-100, 63, -79, -1});
        } else {
            // Example 6
            mice.push_back(Mouse{0, 0, 5, 3});
            mice.push_back(Mouse{10, 0, 5, 3});
        }
    }

    // Optionally shuffle order of mice
    shuffle(mice.begin(), mice.end());

    int N = (int)mice.size();
    println(N);
    for (int i = 0; i < N; i++) {
        println(mice[i].px, mice[i].py, mice[i].vx, mice[i].vy);
    }

    return 0;
}
