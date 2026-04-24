#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
#define int long long

int32_t main() {
    int N;
    cin >> N;
    vector<pair<int, int>> arr(N);
    for(auto &[a, b]: arr)
        cin >> a;
    for(auto &[a, b]: arr)
        cin >> b;
    sort(arr.begin(), arr.end());
    vector<int> invcnt(N);
    int x_inv = 0, y_inv = 0;
    sort(arr.begin(), arr.end(), [](auto a, auto b) {
        return a.second < b.second;
    });
    set_t tmp;
    for(int i=0; i<N; i++) {
        auto [x, y] = arr[i];
        // //printf("tmp = ");
        // for(int t: tmp)
        //     //printf("%d ", t);
        // //printf("\n");
        invcnt[x-1] = x-1-(tmp.order_of_key(x));
        //printf("invcnt %d = %d\n", x-1, invcnt[x-1]);
        y_inv += invcnt[x-1];
        tmp.insert(x);
    }
    if(y_inv % 2) {
        return !(cout << "No");
    }
    vector<pair<int, int>> ans;
    set_t st_2;
    for(int i=0; i<N; i++) {
        auto [x, y] = arr[i];
        int x_add = x-1-st_2.order_of_key(x), y_sub = invcnt[x-1];
        ////printf("x_add = %d, y_sub = %d\n", x_add, y_sub);
        int next_x = x_inv + x_add, next_y = y_inv - y_sub;
        if(next_x < next_y) {
            x_inv = next_x;
            y_inv = next_y;
            ans.push_back({x, y});
            st_2.insert(x);
            continue;
        }
        // found ans
        //printf("stop at i = %d\n", i);
        cout << "Yes\n";
        vector<pair<int, int>> remain;
        sort(arr.begin(), arr.end());
        int t = x-1;
        while(t--) {
            if(arr[t].second < y) continue;
            x_inv++;
            y_inv--;
            //printf("t = %d, x_inv = %d, y_inv = %d\n", t, x_inv, y_inv);
            if(x_inv == y_inv) {
                //printf("swapped %d %d\n", x-1, t);
                auto pr = arr[x-1];
                arr.erase(arr.begin()+x-1);
                arr.insert(arr.begin()+t, pr);
                break;
            }
        }
        for(int i=0; i<N; i++) {
            if(arr[i].second < y) continue;
            ans.push_back(arr[i]);
        }
        for(auto [a, b]: ans) {
            cout << a << ' ';
        }
        cout << '\n';
        for(auto [a, b]: ans) {
            cout << b << ' ';
        }
        cout << '\n';
        return 0;
    }
}
