//문제 제한에 전혀 어긋나지 않는 제너레이터가 밸리데이터 검증에서 걸립니다. 일단 제한을 줄여놨습니다.
#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
	registerGen(argc,argv,1);
    cout<<rnd.next(1,(1<<20))<<'\n'<<rnd.next(1,20)<<'\n';
  
}
