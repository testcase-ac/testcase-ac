for s in[*open(0)]:
  x,y=map(eval,s.split())
  print(["Q"+"1243"[(x<0)+2*(y<0)],'AXIS'][x*y==0])
