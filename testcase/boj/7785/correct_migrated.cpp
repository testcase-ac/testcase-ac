#include <iostream>
#include <string>
#include <set>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    set<string, greater<string>> mans;
    string name, enter_or_leave;
    int is_enter;

    for (int i = 0; i < N; i++) {
        cin >> name >> enter_or_leave;
        if (enter_or_leave == "enter") {
            mans.insert(name);
        }
        else {
            mans.erase(mans.find(name));
        }
    }

    for (string x : mans) {
        cout << x + "\n";
    }
    return 0;
}
