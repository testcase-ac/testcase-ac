def f(n):
  assert type(n)==int and n>=0
  def g(n):
    a = [x**3 for x in range(n)]
    print(a)
    return sum(a)

  x=""
  k=0
  while n>=len(x):
    x+=str(g(k))
    k+=1
  return x

print(f(0)) # 0
print(f(9)) # 2
print(f(12)) # 2
# print(f(12345)) # 1
# print(f(2**63-1)) # 6
