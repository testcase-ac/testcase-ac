#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    // 테스트라이브러리 초기화
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();
    vector<vector<int>> user(N, vector<int>(N));
    set<int> seen;

    // 사용자 출력 읽기
    for(int i = 0; i < N; i++) {
        int row_sum = 0;
        for(int j = 0; j < N; j++) {
            int x = ouf.readInt();
            if (x < 1 || x > N*N)
                quitf(_wa, "Number %d out of range", x);
            if (seen.count(x))
                quitf(_wa, "Duplicate number %d", x);
            seen.insert(x);
            user[i][j] = x;
            row_sum += x;
        }
    }

    // 모든 숫자가 1~N^2 있는지 확인
    for(int i = 1; i <= N*N; i++)
        if (!seen.count(i))
            quitf(_wa, "Missing number %d", i);

    // 행 합 확인
    int sum_row = accumulate(user[0].begin(), user[0].end(), 0);
    for(int i = 1; i < N; i++) {
        int s = accumulate(user[i].begin(), user[i].end(), 0);
        if (s != sum_row)
            quitf(_wa, "Row %d sum %d != %d", i+1, s, sum_row);
    }

    // 열 합 확인
    for(int j = 0; j < N; j++) {
        int s = 0;
        for(int i = 0; i < N; i++) s += user[i][j];
        if (s != sum_row)
            quitf(_wa, "Column %d sum %d != %d", j+1, s, sum_row);
    }

    // 대각선 합 확인
    int diag1 = 0, diag2 = 0;
    for(int i = 0; i < N; i++) {
        diag1 += user[i][i];
        diag2 += user[i][N-1-i];
    }
    if (diag1 != sum_row || diag2 != sum_row)
        quitf(_wa, "Diagonal sum mismatch");

    quitf(_ok, "All checks passed");
}
