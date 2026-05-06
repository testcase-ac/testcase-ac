#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <vector<int> >list(200001);
int N;
int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N;
    while(N--){
        int x, y; cin >> y >> x;
        list[x + 100000].push_back(y);
    }
    for(int i = 0; i < 200001; i++){
        if(list[i].size() > 0){
            sort(list[i].begin(), list[i].end());
            for(const auto& hi : list[i])
                cout << hi << ' ' << i - 100000  << '\n';
        }
    }
}
