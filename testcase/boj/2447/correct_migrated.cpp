#include <iostream>
#include <vector>
using namespace std;

void dr(vector<vector<char>>& grid, int x, int y, int size) {
    if (size == 3) {
        grid[x][y] = '*';
        grid[x][y + 1] = '*';
        grid[x][y + 2] = '*';
        grid[x + 1][y] = '*';
        grid[x + 1][y + 2] = '*';
        grid[x + 2][y] = '*';
        grid[x + 2][y + 1] = '*';
        grid[x + 2][y + 2] = '*';
        return;
    }
    int new_size = size / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            dr(grid, x + i * new_size, y + j * new_size, new_size);
        }
    }
}
int main() {
    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n, ' '));
    dr(grid, 0, 0, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
