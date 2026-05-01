#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 3);
    int N;

    if (scenario == 0) {
        N = rnd.next(1, 3);
    } else if (scenario == 1) {
        N = rnd.next(4, 10);
    } else {
        N = rnd.next(8, 15);
    }

    int patternType = rnd.next(0, 4);
    vector<int> A(N);
    int FULL = (1 << 20) - 1;

    for (int i = 0; i < N; i++) {
        if (patternType == 0) {
            A[i] = 0;
        } else if (patternType == 1) {
            A[i] = i % 16;
        } else if (patternType == 2) {
            A[i] = (N - i) % 16;
        } else if (patternType == 3) {
            A[i] = (i % 2 ? FULL : 0);
        } else {
            if (rnd.next(0, 4) == 0)
                A[i] = rnd.next(0, FULL);
            else
                A[i] = rnd.next(0, (1 << 12) - 1);
        }
    }

    int M;
    if (scenario == 0) {
        M = rnd.next(1, 7);
    } else if (scenario == 1) {
        M = rnd.next(N, min(3 * N, 30));
    } else {
        M = rnd.next(2 * N, 30);
    }

    vector< vector<int> > queries;
    queries.reserve(M);
    bool has3 = false;

    for (int i = 0; i < M; i++) {
        int t;
        if (scenario == 0) {
            if (i == M - 1 || i % 2 == 0) t = 3;
            else t = (rnd.next(0, 1) == 0 ? 1 : 2);
        } else if (scenario == 1) {
            int r = rnd.next(0, 9);
            if (r < 4) t = 3;
            else if (r < 7) t = 1;
            else t = 2;
        } else {
            int r = rnd.next(0, 9);
            if (r < 3) t = 3;
            else if (r < 7) t = 1;
            else t = 2;
        }

        int kind = rnd.next(0, 9);
        int L, R;
        if (N == 1) {
            L = R = 1;
        } else if (kind < 2) {
            L = 1;
            R = N;
        } else if (kind < 4) {
            L = 1;
            R = rnd.next(1, N);
        } else if (kind < 6) {
            L = rnd.next(1, N);
            R = N;
        } else {
            L = rnd.next(1, N);
            R = rnd.next(L, N);
        }

        if (t == 3) {
            vector<int> q(3);
            q[0] = 3; q[1] = L; q[2] = R;
            queries.push_back(q);
            has3 = true;
        } else {
            int X;
            if (scenario == 2) {
                int roll = rnd.next(0, 9);
                if (roll < 3) X = 0;
                else if (roll < 6) X = FULL;
                else if (roll < 8) X = 1 << rnd.next(0, 19);
                else X = rnd.next(0, FULL);
            } else {
                if (rnd.next(0, 4) == 0)
                    X = rnd.next(0, FULL);
                else
                    X = rnd.next(0, (1 << 12) - 1);
            }
            vector<int> q(4);
            q[0] = t; q[1] = L; q[2] = R; q[3] = X;
            queries.push_back(q);
        }
    }

    if (!has3) {
        vector<int> q(3);
        q[0] = 3;
        q[1] = 1;
        q[2] = N;
        queries.back() = q;
    }

    println(N);
    println(A);
    println((int)queries.size());
    for (auto &q : queries) {
        if (q[0] == 3)
            println(q[0], q[1], q[2]);
        else
            println(q[0], q[1], q[2], q[3]);
    }

    return 0;
}
