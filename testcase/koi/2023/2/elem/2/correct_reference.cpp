#include <iostream>

using namespace std;
using ll = long long;

int n, v[500500], mx[500500];
ll sum;

int main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> v[i];
    for(int i=n;i>=1;i--) mx[i] = min(v[i], mx[i+1]+1);
    for(int i=1;i<=n;i++) sum += mx[i];
    cout << sum;
    return 0;
}