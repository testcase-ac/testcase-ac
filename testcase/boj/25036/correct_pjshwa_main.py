def ftest(n):
  assert type(n)==int and n>=0
  def g(n): return (n * (n - 1) // 2) ** 2

  x=""
  k=0
  while n>=len(x):
    x+=str(g(k))
    k+=1
  return x


print(ftest(0)) # 0
print(ftest(9)) # 2
print(ftest(12)) # 2
# print(f(12345)) # 1
# print(f(2**63-1)) # 6

# exit(0)


def f(n):
    assert type(n)==int and n>=0
    g=lambda n: (n * (n - 1) // 2) ** 2
    x=""
    k=0
    while n>=len(x):
        x+=str(g(k))
        k+=1
    return int(x[n])

print(f(0)) # 0
print(f(9)) # 2
print(f(12345)) # 1
# print(optimizing(2**63-1)) # 6


def optimizing(n):
  return 0

######### SUBMIT THE ABOVE CODE ONLY #########

print(optimizing(0)) # 0
print(optimizing(9)) # 2
print(optimizing(12345)) # 1
print(optimizing(2**63-1)) # 6

