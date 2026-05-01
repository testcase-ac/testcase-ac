#include "testlib.h"
using namespace std;

struct Query {
    int t, L, R, X;
};

int chooseType(int scenario) {
    int pick = rnd.next(1, 100);
    if (scenario == 1) {
        // fairly balanced
        if (pick <= 34) return 1;
        else if (pick <= 67) return 2;
        else return 3;
    } else if (scenario == 2) {
        // sqrt-heavy
        if (pick <= 20) return 1;
        else if (pick <= 75) return 2;
        else return 3;
    } else if (scenario == 3) {
        // add-heavy
        if (pick <= 60) return 1;
        else if (pick <= 80) return 2;
        else return 3;
    } else {
        // query-heavy
        if (pick <= 25) return 1;
        else if (pick <= 50) return 2;
        else return 3;
    }
}

void chooseRange(int N, int scenario, int &L, int &R) {
    if (N == 1) { L = R = 1; return; }
    int mode = rnd.next(1, 10);
    if (scenario == 4) {
        // many singletons
        if (mode <= 5) {
            L = R = rnd.next(1, N);
        } else if (mode <= 7) {
            L = 1; R = N;
        } else {
            L = rnd.next(1, N);
            R = rnd.next(L, N);
        }
    } else {
        if (mode == 1) {
            L = 1; R = N;
        } else if (mode == 2) {
            L = R = rnd.next(1, N);
        } else {
            L = rnd.next(1, N);
            R = rnd.next(L, N);
        }
    }
}

int chooseX(int scenario) {
    int pick = rnd.next(1, 100);
    if (scenario == 3) {
        // adds-heavy: a bit more large values
        if (pick <= 30) return 1;
        else if (pick <= 55) return rnd.next(2, 10);
        else if (pick <= 80) return rnd.next(11, 1000);
        else return rnd.next(1000, 100000);
    } else {
        if (pick <= 40) return 1;
        else if (pick <= 70) return rnd.next(2, 10);
        else if (pick <= 90) return rnd.next(11, 1000);
        else return rnd.next(1000, 100000);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 4);

    int N;
    if (scenario == 2) {
        N = rnd.next(1, 8);
    } else if (scenario == 3) {
        N = rnd.next(5, 12);
    } else {
        N = rnd.next(1, 15);
    }

    vector<int> special = {1,2,3,4,9,16,25,36,49,64,81,100};
    vector<int> A(N);

    if (scenario == 1) {
        int pattern = rnd.next(1, 4);
        if (pattern == 1) {
            for (int i = 0; i < N; i++) A[i] = i + 1;
        } else if (pattern == 2) {
            for (int i = 0; i < N; i++) A[i] = rnd.next(1, 20);
        } else if (pattern == 3) {
            for (int i = 0; i < N; i++) A[i] = rnd.next(50000, 100000);
        } else {
            for (int i = 0; i < N; i++) {
                if (i % 2 == 0) A[i] = rnd.next(1, 20);
                else A[i] = rnd.next(50000, 100000);
                if (rnd.next(0, 99) < 30)
                    A[i] = rnd.any(special);
            }
        }
    } else if (scenario == 2) {
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(90000, 100000);
        }
        // ensure some small values to play with sqrt edge cases
        if (N >= 1) A[0] = 2;
        if (N >= 2) A[1] = 3;
    } else if (scenario == 3) {
        for (int i = 0; i < N; i++) {
            A[i] = rnd.any(special);
        }
    } else { // scenario 4
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0) A[i] = rnd.any(special);
            else if (i % 3 == 1) A[i] = rnd.next(1, 30);
            else A[i] = rnd.next(70000, 100000);
        }
    }

    int M;
    if (N == 1) {
        M = rnd.next(5, 15);
    } else {
        if (scenario == 2) M = rnd.next(8, 18);
        else M = rnd.next(5, 20);
    }

    vector<Query> qs;
    qs.reserve(M);

    vector<int> mandatory = {1, 2, 3};

    for (int i = 0; i < M; i++) {
        int t;
        if (!mandatory.empty() && M - i == (int)mandatory.size()) {
            t = rnd.any(mandatory);
        } else {
            t = chooseType(scenario);
        }

        int L, R;
        chooseRange(N, scenario, L, R);

        int X = 0;
        if (t == 1) {
            X = chooseX(scenario);
        }

        qs.push_back({t, L, R, X});

        // remove from mandatory if used
        for (int j = 0; j < (int)mandatory.size(); j++) {
            if (mandatory[j] == t) {
                mandatory.erase(mandatory.begin() + j);
                break;
            }
        }
    }

    // Output
    println(N);
    println(A);
    println(M);
    for (const auto &q : qs) {
        if (q.t == 1) println(q.t, q.L, q.R, q.X);
        else println(q.t, q.L, q.R);
    }

    return 0;
}
