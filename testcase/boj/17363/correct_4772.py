mp = {'.': '.',
      'O': 'O',
      '-': '|',
      '|': '-',
      '/': '\\',
      '\\': '/',
      '^': '<',
      '<': 'v',
      'v': '>',
      '>': '^'}

n, m = map(int, input().split())

arr = [input() for i in range(n)]

out = [['' for i in range(n)] for j in range(m)]

for i in range(n):
    for j in range(m):
        out[m-1-j][i] = mp[arr[i][j]]
print('\n'.join(''.join(a) for a in out))
