//밸리데이터 오류로 M=0 케이스를 넣으면 코드 검증 실패가 떠요
#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(1,1000),m=rnd.next(1,50);
	cout<<n<<' '<<m<<'\n';
	set<int> s;
    while(m--) {
        int a;
        while(1) {
            a=rnd.next(1,1000);
            if(s.find(a)==s.end()) break;
        } if(!s.empty()) cout<<' ';
        cout<<a;
        s.insert(a);
    } cout<<'\n';
}
