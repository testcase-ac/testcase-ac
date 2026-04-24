#include "testlib.h"
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of operations
    int Q = rnd.next(5, 20);
    // Probability of a new student join (D) vs query (P)
    double joinProb = rnd.next(3, 7) / 10.0;

    vector<tuple<int, long long, long long>> events;
    vector<pair<long long, long long>> students;
    students.reserve(20);

    int Dcnt = 0;
    for (int i = 0; i < Q; i++) {
        bool doJoin;
        if (i == 0 || Dcnt == 0) {
            // First op or no students yet: must join
            doJoin = true;
        } else {
            // Otherwise random choice
            doJoin = (rnd.next() < joinProb);
        }
        if (doJoin) {
            // Generate unique (A, B)
            long long A, B;
            do {
                int tA = rnd.next(-2, 2);
                int tB = rnd.next(-2, 2);
                A = rnd.wnext(2000000000, tA) + 1;
                B = rnd.wnext(2000000000, tB) + 1;
            } while (find(students.begin(), students.end(), make_pair(A, B)) != students.end());
            students.emplace_back(A, B);
            Dcnt++;
            events.emplace_back(0, A, B); // 0 means D A B
        } else {
            // Query for one of existing students
            int idx = rnd.next(1, Dcnt);
            events.emplace_back(1, idx, 0); // 1 means P idx
        }
    }

    // Output
    println(Q);
    for (auto &e : events) {
        int tp = get<0>(e);
        if (tp == 0) {
            // D A B
            println("D", get<1>(e), get<2>(e));
        } else {
            // P i
            println("P", get<1>(e));
        }
    }

    return 0;
}
