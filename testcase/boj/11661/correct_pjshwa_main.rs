a, b, c, x1, x2, y1, y2 = gets.split.map(&:to_i)
(puts 0; exit) if x1 > x2 || y1 > y2

def extended_euclidean(a, b)
  return [a, 1, 0] if b.zero?

  g, x, y = extended_euclidean(b, a % b)
  [g, y, x - (a / b) * y]
end

def solve_for_one(a, c, x1, x2)
  if a == 0 && c == 0
    x2 - x1 + 1
  elsif a != 0 && c % a == 0 && a * x1 <= c && c <= a * x2
    1
  else
    0
  end
end

def solve_for_two(a, b, c, x1, x2, y1, y2)
  g, x0, y0 = extended_euclidean(a, b)

  x0 *= -c / g
  y0 *= -c / g

  start1, end1 = [Rational(x1 - x0, b) * g, Rational(x2 - x0, b) * g].sort
  start2, end2 = [Rational(y0 - y1, a) * g, Rational(y0 - y2, a) * g].sort

  start_point = [start1, start2].max.ceil
  end_point = [end1, end2].min.floor

  [end_point - start_point + 1, 0].max
end

fn main() {
  
}

if a == 0
  puts solve_for_one(b, c, y1, y2) * (x2 - x1 + 1)
elsif b == 0
  puts solve_for_one(a, c, x1, x2) * (y2 - y1 + 1)
elsif c % a.gcd(b) == 0
  puts solve_for_two(a, b, c, x1, x2, y1, y2)
else
  puts 0
end
