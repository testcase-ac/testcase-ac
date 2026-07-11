#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
using namespace std;

int main(){
    int n, k1, k2;
    cin >> n >> k1 >> k2;
    vector<int> s(n), res(n);
    for(auto &i : s) cin >> i;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j) continue;
            if(s[i] == s[j] && abs(i - j) <= k1) res[i]++;
            if(s[i] != s[j] && abs(i - j) <= k2) res[i]++;
        }
    }

    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
}
