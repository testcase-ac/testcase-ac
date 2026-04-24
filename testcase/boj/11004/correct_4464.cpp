#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rec_randomized_select(vector<int>& v, int t, int l, int r) {
    if(r - l == 1) {
        return v[l];
    }
    int pivot_index = l + rng() % (r - l);
    int pivot = v[pivot_index];
    int i = l, j = l, k = r - 1;
    // three way partition
    while(j <= k) {
        if(v[j] < pivot) {
            swap(v[i], v[j]);
            i++;
            j++;
        } else if(v[j] > pivot) {
            swap(v[j], v[k]);
            k--;
        } else {
            j++;
        }
    }
    if(i <= t && t < j) {
        return v[i];
    } else if(t >= j) {
        return rec_randomized_select(v, t, j, r);
    } else {
        return rec_randomized_select(v, t, l, i);
    }
}

int randomized_select(vector<int>& v, int t) {
    return rec_randomized_select(v, t, 0, v.size());
}

int rec_deterministic_select(vector<int>& v, int t, int l, int r) {
    if(r - l <= 5) {
        // insertion sort
        for(int i = l + 1; i < r; i++) {
            int j = i;
            while(j > l && v[j] < v[j - 1]) {
                swap(v[j], v[j - 1]);
                j--;
            }
        }
        return v[t];
    }
    int n = r - l;
    vector<int> medians;
    for(int x=l; x<r; x+=5) {
        int y = min(x + 5, r);
        for(int i=x+1; i<y; i++) {
            int j = i;
            while(j > x && v[j] < v[j - 1]) {
                swap(v[j], v[j-1]);
                j--;
            }
        }
        medians.push_back(v[(x + y) / 2]);
    }
    int pivot = rec_deterministic_select(medians, (medians.size() - 1) / 2, 0, medians.size());
    
    // same as select()
    int i = l, j = l, k = r - 1;
    // three way partition
    while(j <= k) {
        if(v[j] < pivot) {
            swap(v[i], v[j]);
            i++;
            j++;
        } else if(v[j] > pivot) {
            swap(v[j], v[k]);
            k--;
        } else {
            j++;
        }
    }

    if(i <= t && t < j) {
        return v[i];
    } else if(t >= j) {
        return rec_randomized_select(v, t, i + 1, r);
    } else {
        return rec_randomized_select(v, t, l, i);
    }
}

int deterministic_select(vector<int>& v, int t) {
    return rec_deterministic_select(v, t, 0, v.size());
}

int32_t main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int version = 1;
    int n, t;
    cin >> n >> t;
    t--;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int ans = version == 1 ? randomized_select(v, t) : deterministic_select(v, t);
    cout << ans << endl;
    // if(version != 1 && version != 2) {
    //     cerr << "Invalid version number" << endl;
    //     return -1;
    // }
    // int n, t;

    // // open file in argv[2]
    // ifstream fin(argv[2]);
    // fin >> n >> t;
    // t--;
    // vector<int> v(n);
    // for (int i = 0; i < n; i++) {
    //     fin >> v[i];
    // }
    // fin.close();

    // // get ans
    // int ans = version == 1 ? randomized_select(v, t) : deterministic_select(v, t);

    // // write file in argv[3]
    // ofstream fout(argv[3]);
    // fout << ans << endl;
    // fout.close();
}
