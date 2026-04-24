#include <iostream>
#include <cstring>
using namespace std;

int N, M, R;
int A[100][100], T[100][100];
void op1() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = T[N-i-1][j];
        }
    }
}

void op2() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = T[i][M-j-1];
        }
    }
}

void op3() {
    // rotate to right
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[j][N-i-1] = T[i][j];
        }
    }
    swap(N, M);
}

void op4() {
    // rotate to left
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[M-j-1][i] = T[i][j];
        }
    }
    swap(N, M);
}

void op5() {
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < M/2; j++) {
            A[i][j+M/2] = T[i][j];
        }
    }
    for (int i = 0; i < N/2; i++) {
        for (int j = M/2; j < M; j++) {
            A[i+N/2][j] = T[i][j];
        }
    }
    for (int i = N/2; i < N; i++) {
        for (int j = M/2; j < M; j++) {
            A[i][j-M/2] = T[i][j];
        }
    }
    for (int i = N/2; i < N; i++) {
        for (int j = 0; j < M/2; j++) {
            A[i-N/2][j] = T[i][j];
        }
    }
}

void op6() {
    for (int i = 0; i < N/2; i++) {
        for (int j = 0; j < M/2; j++) {
            A[i+N/2][j] = T[i][j];
        }
    }
    for (int i = N/2; i < N; i++) {
        for (int j = 0; j < M/2; j++) {
            A[i][j+M/2] = T[i][j];
        }
    }
    for (int i = N/2; i < N; i++) {
        for (int j = M/2; j < M; j++) {
            A[i-N/2][j] = T[i][j];
        }
    }
    for (int i = 0; i < N/2; i++) {
        for (int j = M/2; j < M; j++) {
            A[i][j-M/2] = T[i][j];
        }
    }

}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> N >> M >> R;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < R; i++) {
        int op;
        cin >> op;
        memcpy(T, A, sizeof(A));
        memset(A, 0, sizeof(A));
        switch (op) {
            case 1: op1(); break;
            case 2: op2(); break;
            case 3: op3(); break;
            case 4: op4(); break;
            case 5: op5(); break;
            case 6: op6(); break;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
}
