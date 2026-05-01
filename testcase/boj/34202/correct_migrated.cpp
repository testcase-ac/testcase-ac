#include <iostream>
#include <array>
#include <vector>

using namespace std;

constexpr int MAX_N = 200'000;

array<int, MAX_N> arr;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        cin >> arr[i];
    }

    vector<int> st;
    st.reserve(n);
    st.push_back(0);
    cout << "1 ";

    for (int i = 1; i < n-1; i++) {
        int j = st.back();
        if (arr[i] < arr[j]) {
            cout << i+1 << " " << j+1 << " ";
            st.pop_back();
        } else if (arr[i] == arr[j]) {
            cout << i+1 << " ";
        } else {
            st.push_back(i);
        }
    }

    cout << n << "\n";

    return 0;
}
