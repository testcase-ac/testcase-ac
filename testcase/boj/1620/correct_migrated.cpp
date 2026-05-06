#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;
    unordered_map<int, string> a;
    unordered_map<string, int> b;

    for (int i = 1; i <= N; ++i) {
        string name;
        cin >> name;
        a[i] = name;
        b[name] = i;
    }

    for (int i = 0; i < M; ++i) {
        string query;
        cin >> query;
        
        if (query[0] >= '0' && query[0] <= '9') {
            int num = 0;
            for (char c : query) {
                num = num * 10 + (c - '0');
            }
            cout << a[num] << '\n';
        } else {
            cout << b[query] << '\n';
        }
    }
}
