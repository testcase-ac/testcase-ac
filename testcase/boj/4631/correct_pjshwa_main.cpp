#include <iostream>
#include <string>

using namespace std;

int main(){
    int n;
    int set_no = 0;
    while(true){
        set_no++;
        cin >> n;
        if(n == 0) break;
        cout << "SET " << set_no << '\n';
        
        string *ss = new string[n];
        for(int i = 0; i < n; i++){
            cin >> ss[i];
        }
        for(int i = 0; i < n; i += 2){
            cout << ss[i] << '\n';
        }
        for(int i = 2 * (n/2) - 1; i > 0; i -= 2){
            cout << ss[i] << '\n';
        }
        delete[] ss;
    }
}