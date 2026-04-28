q = input().rstrip()
if q == 'Marathon Edition 우승자':
  ans = ['대상', '레고 타워 브리지 - 10214', 'sait2000']
if q == 'Marathon Edition 준우승자 및 ReguIar Edition 준우승자':
  ans = ['장려상', 'Katamari Damacy REROLL', 'cubelover']
if q == 'ReguIar Edition 우승자 및 Speedrun Edition 우승자':
  ans = ['장려상', '(도서) Speedrun Science: A Long Guide To Short Playthroughs', 'xiaowuc1']
if q == 'Speedrun Edition 준우승자':
  ans = ['장려상', '치킨 기프티콘', 'rubix']
if q == '이 대회에 참가하지 않은 사람 중 2019년 대회 최고 등수':
  ans = ['결근상', '치킨 기프티콘', 'hyeonguk']
if q == '모든 에디션에서 총점이 160억점에 가장 가까운 사람':
  ans = ['대상', '16GB USB', '2u_my_light']
if q == '홀수와 짝수의 대결 문제의 오류를 발견한 사람':
  ans = ['QA 상', '치킨 기프티콘', 'namnamseo']
if q == '4차 산업 혁명을 기계학습 없이 서브태스크 2까지만 푼 사람 중 추첨':
  ans = ['UPWF 위원회 특별상', '(도서) 4차 산업혁명은 없다', 'pichulia']
if q == '배중률교를 정해가 아닌 방법으로 푼 사람 중 추첨':
  ans = ['직관주의자상', '치킨 기프티콘', 'dotorya']
if q == 'Marathon Edition에서 Nonogram QR을 마지막으로 1점 이상 획득한 사람':
  ans = ['QR 분해 상', '바코드 스캐너', '201812106']
if q == '연속합 2147483647 첫 0점자':
  ans = ['Re: 제로부터 시작하는 다이나믹 프로그래밍 상', '빵', 'zigui']
if q == 'Beginning the Hunt 첫 만점자':
  ans = ['"Ghudegy Cup looks too intense for me" 상', 'Roller Coaster Tycoon 2: Triple Thrill Pack', 'portableangel']
if q == '대회에 참여하였고 A+B (MC)에 제출하지 않은 사람 중 추첨':
  ans = ['You Need a Minecraft 상', 'Minecraft', 'greimul']

print("\n".join(ans))
