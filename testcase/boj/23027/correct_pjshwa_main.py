import re
s = input()
if 'A' in s:
  print(re.sub('[BCDF]', 'A', s))
elif 'B' in s:
  print(re.sub('[CDF]', 'B', s))
elif 'C' in s:
  print(re.sub('[DF]', 'C', s))
else:
  print('A' * len(s))
