#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
	int n=rnd.next(2,50); //N=1인 경우는 현재 데이터에 없음
	cout<<n<<'\n';
	while(n--) cout<<rnd.next(-50000,50000)<<' '<<rnd.next(-50000,50000)<<'\n';
}
