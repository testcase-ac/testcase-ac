#include <iostream>
#include <queue>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int n, p;
    cin >> n >> p;
 
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
 
        p -= a;
        pq.push(a);
        while (!pq.empty() && p + pq.top() <= 0) {
            p += pq.top();
            pq.pop();
        }
 
        cout << (p > 0 ? -1 : (int)pq.size()) << " ";
    }
}
