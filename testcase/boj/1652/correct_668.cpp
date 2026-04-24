#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> arr(n);
    
    for (auto& row : arr) {
        cin >> row;
    }

    int ans1 = 0;
    for (int r = 0; r < n; ++r) {
        int c = 0;
        while (c < n) {
            while (c < n && arr[r][c] == 'X') c++;
            if (c < n - 1 && arr[r][c + 1] == '.') ans1++;
            while (c < n && arr[r][c] == '.') c++;
        }
    }

    int ans2 = 0;
    for (int c = 0; c < n; ++c) {
        int r = 0;
        while (r < n) {
            while (r < n && arr[r][c] == 'X') r++;
            if (r < n - 1 && arr[r + 1][c] == '.') ans2++;
            while (r < n && arr[r][c] == '.') r++;
        }
    }

    cout << ans1 << ' ' << ans2 << '\n';
}
