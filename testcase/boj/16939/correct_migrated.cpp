#include <iostream>
using namespace std;

int u[2][2], d[2][2], l[2][2], f[2][2], r[2][2], b[2][2];
int U[2][2], D[2][2], L[2][2], F[2][2], R[2][2], B[2][2];

void copy_state() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            U[i][j] = u[i][j];
            D[i][j] = d[i][j];
            L[i][j] = l[i][j];
            F[i][j] = f[i][j];
            R[i][j] = r[i][j];
            B[i][j] = b[i][j];
        }
    }
}

void restore_state() {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            u[i][j] = U[i][j];
            d[i][j] = D[i][j];
            l[i][j] = L[i][j];
            f[i][j] = F[i][j];
            r[i][j] = R[i][j];
            b[i][j] = B[i][j];
        }
    }
}

bool is_solved() {
    return (
        (u[0][0] == u[0][1] && u[0][0] == u[1][0] && u[0][0] == u[1][1]) &&
        (d[0][0] == d[0][1] && d[0][0] == d[1][0] && d[0][0] == d[1][1]) &&
        (l[0][0] == l[0][1] && l[0][0] == l[1][0] && l[0][0] == l[1][1]) &&
        (f[0][0] == f[0][1] && f[0][0] == f[1][0] && f[0][0] == f[1][1]) &&
        (r[0][0] == r[0][1] && r[0][0] == r[1][0] && r[0][0] == r[1][1]) &&
        (b[0][0] == b[0][1] && b[0][0] == b[1][0] && b[0][0] == b[1][1])
    );
}

void rotate_U() {
    int temp1 = f[0][0], temp2 = f[0][1];
    f[0][0] = r[0][0]; f[0][1] = r[0][1];
    r[0][0] = b[0][0]; r[0][1] = b[0][1];
    b[0][0] = l[0][0]; b[0][1] = l[0][1];
    l[0][0] = temp1;   l[0][1] = temp2;
}

void rotate_D() {
    int temp1 = f[1][0], temp2 = f[1][1];
    f[1][0] = r[1][0]; f[1][1] = r[1][1];
    r[1][0] = b[1][0]; r[1][1] = b[1][1];
    b[1][0] = l[1][0]; b[1][1] = l[1][1];
    l[1][0] = temp1;   l[1][1] = temp2;
}

void rotate_L() {
    int temp1 = f[0][0], temp2 = f[1][0];
    f[0][0] = d[0][0]; f[1][0] = d[1][0];
    d[0][0] = b[1][1]; d[1][0] = b[0][1];
    b[1][1] = u[0][0]; b[0][1] = u[1][0];
    u[0][0] = temp1;   u[1][0] = temp2;
}

void rotate_R() {
    int temp1 = f[0][1], temp2 = f[1][1];
    f[0][1] = d[0][1]; f[1][1] = d[1][1];
    d[0][1] = b[1][0]; d[1][1] = b[0][0];
    b[1][0] = u[0][1]; b[0][0] = u[1][1];
    u[0][1] = temp1;   u[1][1] = temp2;
}

void rotate_F() {
    int temp1 = u[1][0], temp2 = u[1][1];
    u[1][0] = l[1][1]; u[1][1] = l[0][1];
    l[1][1] = d[0][1]; l[0][1] = d[0][0];
    d[0][1] = r[0][0]; d[0][0] = r[1][0];
    r[0][0] = temp1;   r[1][0] = temp2;
}

void rotate_B() {
    int temp1 = u[0][0], temp2 = u[0][1];
    u[0][0] = l[1][0]; u[0][1] = l[0][0];
    l[1][0] = d[1][1]; l[0][0] = d[1][0];
    d[1][1] = r[0][1]; d[1][0] = r[1][1];
    r[0][1] = temp1;   r[1][1] = temp2;
}

bool can_solve() {
    copy_state();
    void (*moves[])() = {rotate_U, rotate_D, rotate_L, rotate_R, rotate_F, rotate_B};
    
    for (int i = 0; i < 6; i++) {
        moves[i]();  
        if (is_solved()) return true;
        restore_state();
    }
    return false;
}

int main() {
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> u[i][j];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> f[i][j];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> d[i][j];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> l[i][j];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> r[i][j];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) cin >> b[i][j];
    cout << (can_solve() ? 1 : 0);
}
