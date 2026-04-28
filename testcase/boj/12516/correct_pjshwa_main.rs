// IMPL:parse_line
macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let t = parse_line!(u16);
  let stdin = std::io::stdin();

  for tc in 1..=t {
    let n = parse_line!(u16);

    let mut buf = String::new();
    let mut cnt = 0;
    stdin.read_line(&mut buf).unwrap();
    let mut iter = buf.split_whitespace();
    for j in 1..=n {
      let i = iter.next().unwrap().parse::<u16>().unwrap();
      if i != j {cnt += 1;}
    }

    println!("Case #{}: {}.000000", tc, cnt)
  }
}
