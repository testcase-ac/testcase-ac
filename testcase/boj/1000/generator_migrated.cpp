// python은 느려서
// C++로 작성하는 랜덤 예제입니다.
#include "testlib.h"

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  // main 함수 맨 위에 이거 넣어야 합니다.
  int a = rnd.next(1, 9);
  int b = rnd.next(1, 9);
  // rnd.next(a, b)
  // 이 함수는 a이상 b이하의 랜덤한 값을 반환하는 함수일 겁니다.
  // stdlib의 rand 함수와 time의 time(NULL)로 만드는 랜덤은 여기서는 쓰일 수 없습니다.
  // 저걸 쓰면 아마 아래에서 도움말이 나오는데, 솔직히 무슨 말인지 모르겠습니다.
  // 게다가 %N+a 이런 형식을 추가해야 해서 머리 아프죠.
  // 참고로 이 테크닉(맨 위 주석)은 여기서만 사용가능합니다.
  printf("%d %d\n",a,b);
  return 0; 
}

// 참고로 C언어에서도 가능하나, 위에 쓰는게 귀찮아서 C++로 씁니다.
