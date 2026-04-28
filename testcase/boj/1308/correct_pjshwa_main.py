def how_many_days(year_start, year_end):
  if year_start > year_end: return 0
  def add_up(year, d):
    r = year % d - 1
    if r < 0: return r + d
    else: return r
  total_years = year_end - year_start + 1
  four_div_years = (total_years + add_up(year_start, 4)) // 4
  h_div_years = (total_years + add_up(year_start, 100)) // 100
  fh_div_years = (total_years + add_up(year_start, 400)) // 400
  lunar_years = four_div_years - h_div_years + fh_div_years
  return (total_years - lunar_years) * 365 + lunar_years * 366

import sys
r = sys.stdin.readline

cy, cm, cd = map(int, r().split())
ny, nm, nd = map(int, r().split())

if ny - cy >= 1000:
  if ny - cy > 1000 or ((nm > cm) or (nm == cm and nd >= cd)):
    print("gg")
    sys.exit(0)

days_dict = {
  1:31,
  2:28,
  3:31,
  4:30,
  5:31,
  6:30,
  7:31,
  8:31,
  9:30,
  10:31,
  11:30,
  12:31,
}

def is_lunar(year):
  return how_many_days(year, year) == 366

def date_value_inclusive(y, m, d):
  bef = how_many_days(1, y-1)
  for i in range(1,m): bef += days_dict[i]
  if m > 2 and is_lunar(y):
    bef += 1
  return bef + d

def one_day_small(y,m,d):
  if d == 1:
    if m == 1:
      y -= 1
      m, d = 12, 31
    else:
      m -= 1
      if m == 2 and is_lunar(y): d = 29
      else: d = days_dict[m]
  else:
    d -= 1
  return y, m, d
  
cy, cm, cd = one_day_small(cy, cm, cd)
ny, nm, nd = one_day_small(ny, nm, nd)
print("D-{}".format(date_value_inclusive(ny,nm,nd)-date_value_inclusive(cy,cm,cd)))
