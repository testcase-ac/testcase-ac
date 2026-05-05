#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int MAXLEN = 200000;

char cmd() {
    return "LRUD"[rnd.next(4)];
}

string plain(int len){
    string s;
    for(int i=0;i<len;i++) s+=cmd();
    return s;
}

string gen(){
    string res;

    while((int)res.size() < MAXLEN-20){
        int type = rnd.next(3);

        if(type==0){
            res += cmd();
        }
        else{
            int len = rnd.next(1,15);
            int num = rnd.next(1,1000000000);
            res += "(" + plain(len) + ")" + to_string(num);
        }

        if(rnd.next(10)==0) break;
    }

    return res;
}

int main(int argc,char* argv[]){
    registerGen(argc, argv, 1);

    vector<string> name={
        "구데기컵","하이퍼","0초제출","알파고","박승원","애이불비",
        "배중률교","미니앨범","주령구","QR","퍼즐헌트","데쿼리",
        "연속합","대결!"
    };

    cout<<name[rnd.next(14)]<<" "<<name[rnd.next(14)]<<"\n";
    cout<<gen()<<"\n";
}
