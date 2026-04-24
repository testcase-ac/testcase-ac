#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5+2;
int B[MX], A[MX];
vector<int> can[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=1; i<=N; i++)  {
        cin >> B[i];
    }
    B[0] = 1;
    for(int i=1; i<=N; i++) {
        if(B[i-1] > B[i]) {
            return !(cout << "No\n");
        }
        if(B[i] > B[i-1]) {
            //printf("confirmed %d = %d\n", i, B[i-1]);
            A[i] = B[i-1];
            for(int t=B[i-1]+1; t<B[i]; t++) {
                can[i].push_back(t);
            }
        }
    }
    set<int> st;
    for(int i=N; i>=1; i--) {
        if(can[i].size()) {
            for(int t: can[i]) {
                st.insert(t);
            }
        }
        if(!A[i]) {
            if(st.empty()) {
                return !(cout << "No\n");
            }
            auto it = st.begin();
            if(*it == B[i]) {
                if(st.size() == 1) {
                    return !(cout << "No\n");
                }
                it = next(it);
                A[i] = *it;
                st.erase(it);
            } else {
                A[i] = *it;
                st.erase(it);
            }
        }
    }
    cout << "Yes\n";
    for(int i=1; i<=N; i++) {
        cout << A[i] << ' ';
    }
}
