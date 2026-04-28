macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let txt = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec quis lectus sit amet ante suscipit tempor. Aenean dapibus finibus tortor vitae facilisis. Nulla facilisi. Donec suscipit ante a sapien gravida eleifend. Curabitur in lectus ut enim semper venenatis. Aenean elit nibh, hendrerit nec nunc in, dictum cursus dolor. Aenean eget lectus risus. Cras sollicitudin quam vitae augue mollis bibendum. Aliquam euismod vulputate dolor at tristique. Praesent elementum pretium velit non interdum. Nunc posuere faucibus magna id pretium. Maecenas congue, velit eget semper porttitor, tellus tortor porttitor dui, tristique lobortis quam sem ac odio.";

  let (a, b) = parse_line!(i16, i16);
  let mut iter = txt.split_whitespace();
  for i in 1..=b {
    let res = iter.next().unwrap();
    if i < a {continue;}

    print!("{} ", res);
  }
  print!("\n");
}
