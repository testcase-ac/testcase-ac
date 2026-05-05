F='\n'
E=print
B=int(input())
D=sorted(range(1,B+1),key=lambda x:(x%2,x))
C,A=D[:B//2],D[B//2:]
if B%6==3:C.append(C.pop(0));A.append(A.pop(0));A.append(A.pop(0));E(*C+A,sep=F)
elif B%6==2:A[0],A[1]=A[1],A[0];del A[2];E(*C+A+[5],sep=F)
else:E(*D,sep=F)
