#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,a,b,c;
    cin >> n >> m;
    vector<int> arr(n + 1, 0);
    iota(arr.begin(), arr.end(), 0);
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        c=arr[b];
        arr[b]=arr[a];
        arr[a]=c;
    }
    for(int i = 1; i < n+1; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
