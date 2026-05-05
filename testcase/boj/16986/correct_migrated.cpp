#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class s {
   private:
    int n_, k_;
    vector<vector<int>> cross_;
    vector<int> kyng_, mino_, w_cnt_, l_cnt_;

   public:
    s() {
        cin >> n_ >> k_;
        cross_.assign(n_ + 1, vector<int>(n_ + 1));
        for (int i = 1; i <= n_; i++) {
            for (int j = 1; j <= n_; j++) {
                cin >> cross_[i][j];
            }
        }
        kyng_.assign(20, 0);
        mino_.assign(20, 0);
        for (int i = 0; i < 20; i++) {
            cin >> kyng_[i];
        }
        for (int i = 0; i < 20; i++) {
            cin >> mino_[i];
        }

        w_cnt_.assign(n_ + 1, 0);
        l_cnt_.assign(n_ + 1, 0);
        for (int i = 1; i <= n_; i++) {
            for (int j = 1; j <= n_; j++) {
                if (cross_[i][j] == 0) {
                    w_cnt_[i]++;
                }
            }
            l_cnt_[i] = n_ - w_cnt_[i];
        }
    }

    void show() {
        for (auto i : w_cnt_) cout << i << ' ';
        cout << '\n';
        for (auto i : l_cnt_) cout << i << ' ';
        cout << '\n';
    }

    void Ve() {
        if (n_ < k_) {
            cout << 0;
            return;
        }
        MakeStrategyTable();
    }
    bool Buildable(vector<int> &arr, vector<int> &build) {
        int w_cnt[10] =
            {
                0,
            },
            l_cnt[10] = {
                0,
            };
        for (int i = 0; i < (int)build.size(); i++) {
            if (arr[i]) {
                w_cnt[build[i]]++;
            } else {
                l_cnt[build[i]]++;
            }
        }
        for (int i = 1; i <= n_; i++) {
            if (w_cnt[i] > w_cnt_[i]) return false;
            if (l_cnt[i] > l_cnt_[i]) return false;
        }
        vector<bool> visit(n_ + 1, false);

        return DFS(0, visit, arr, build);
    }

    bool DFS(int round, vector<bool> &visit, vector<int> &arr, vector<int> &build) {
        if (round == (int)build.size()) {
            return true;
        }

        for (int i = 1; i <= n_; i++) {
            if (visit[i]) continue;
            if (arr[round] && cross_[build[round]][i] != 0) {
                continue;
            } else if (!arr[round] && cross_[build[round]][i] == 0) {
                continue;
            }
            visit[i] = true;
            if (DFS(round + 1, visit, arr, build)) return true;

            visit[i] = false;
        }
        return false;
    }

    vector<int> CanWin(vector<int> &arr) {
        vector<int> ret;
        int arr_idx = 0, k_idx = 0, m_idx = 0, j_cnt = 0, k_cnt = 0, m_cnt = 0;
        int status = 1;
        for (; j_cnt < k_ && k_cnt < k_ && m_cnt < k_;) {
            if (status == 1) {
                ret.push_back(kyng_[k_idx]);
                if (arr[arr_idx] == 1) {
                    j_cnt++;
                    status = 2;
                } else {
                    k_cnt++;
                    status = 3;
                }
                arr_idx++, k_idx++;
            } else if (status == 2) {
                ret.push_back(mino_[m_idx]);
                if (arr[arr_idx] == 1) {
                    j_cnt++;
                    status = 1;
                } else {
                    m_cnt++;
                    status = 3;
                }
                arr_idx++, m_idx++;
            } else {
                if (cross_[kyng_[k_idx]][mino_[m_idx]] == 2) {
                    k_cnt++;
                    status = 1;
                } else {
                    m_cnt++;
                    status = 2;
                }
                k_idx++, m_idx++;
            }
        }
        if (j_cnt == k_)
            return ret;
        else
            return vector<int>();
    }

    void MakeStrategyTable() {
        vector<int> arr;
        for (int i = 0; i < k_; i++) arr.push_back(1);
        for (int i = 0; i < (k_ - 1) * 2; i++) arr.push_back(0);
        do {
            auto it = arr.end();
            for (it--; it >= arr.begin(); it--) {
                if (*it == 1) break;
            }
            if (it - arr.begin() >= n_) continue;
            vector<int> build = CanWin(arr);

            if (build.empty()) continue;

            if (Buildable(arr, build)) {
                cout << 1;
                return;
            }

        } while (prev_permutation(arr.begin(), arr.end()));
        cout << 0;
    }
};

int main() {
    s sol;
    sol.Ve();
    return 0;
}
