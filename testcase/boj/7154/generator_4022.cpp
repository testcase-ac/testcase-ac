#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    for (int tc = 0; tc < T; tc++) {
        // Number of jobs
        int n = rnd.next(4, 10);
        // Hyper-parameter: maximum capacity per job
        vector<int> capOptions = {1, 2, 3, 5, 10};
        int capMax = rnd.any(capOptions);
        // Generate capacities
        vector<int> p(n);
        int totalCaps = 0;
        for (int i = 0; i < n; i++) {
            p[i] = rnd.next(1, capMax);
            totalCaps += p[i];
        }
        // Number of students
        int m = rnd.next(1, min(totalCaps, 70));
        // Build slot list and assign each student a guaranteed slot
        vector<int> slots;
        for (int i = 0; i < n; i++)
            for (int k = 0; k < p[i]; k++)
                slots.push_back(i);
        shuffle(slots.begin(), slots.end());
        vector<int> assigned(m);
        for (int i = 0; i < m; i++)
            assigned[i] = slots[i];
        // Build student choice lists
        struct Stu { int y; vector<int> c; };
        vector<Stu> students(m);
        for (int i = 0; i < m; i++) {
            // Year hyper-parameter: bias high or low
            vector<int> tOpts = {-1, 0, 1};
            int t = rnd.any(tOpts);
            int y = rnd.wnext(3, t) + 1; // yields 1..3
            // Ensure assigned job is in choices
            vector<int> others;
            for (int j = 0; j < n; j++)
                if (j != assigned[i])
                    others.push_back(j);
            shuffle(others.begin(), others.end());
            vector<int> c = {assigned[i], others[0], others[1], others[2]};
            shuffle(c.begin(), c.end());
            students[i] = {y, c};
        }
        // Randomize student order
        shuffle(students.begin(), students.end());
        // Output this test case
        println(n, m);
        for (int i = 0; i < n; i++)
            println(p[i]);
        for (auto &s : students)
            println(s.y, s.c[0], s.c[1], s.c[2], s.c[3]);
    }
    // Terminate input
    println(0, 0);
    return 0;
}
