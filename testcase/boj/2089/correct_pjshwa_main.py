n = int(input())
stack = []
if n == 0:
  print(0)
  exit()

while n:
  if n % -2:
    stack.append(1)
    n = n // -2 + 1
  else:
    stack.append(0)
    n = n // -2

while stack: print(stack.pop(), end="")
