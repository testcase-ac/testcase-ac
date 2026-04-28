use std::{io, str};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

fn input_integers() -> Vec<i32> {
  let mut s = String::new();

  io::stdin().read_line(&mut s).unwrap();

  let values: Vec<i32> = s
      .as_mut_str()
      .split_whitespace()
      .map(|s| s.parse().unwrap())
      .collect();

  values
}

fn solve(n: usize, m: usize) {
  let l = input_integers();
  let mut a = vec![0; n + m - 1];

  for istate in 0..(1 << m) {
    let mut popcnt = 0;
    for i in 0..m {
      if istate & (1 << i) != 0 {
        popcnt += 1;
      }
    }
    if popcnt != l[0] {
      continue;
    }
    
    let mut cur = popcnt;
    for j in 0..m {
      if istate & (1 << j) == 0 {
        a[j] = 0;
      }
      else {
        a[j] = 1;
      }
    }

    let mut able = true;
    for j in m..(n + m - 1) {
      cur -= a[j - m];
      if cur == l[j - m + 1] {
        a[j] = 0;
      }
      else if cur == l[j - m + 1] - 1 {
        a[j] = 1;
        cur += 1;
      }
      else {
        able = false;
        break;
      }
    }

    if able {
      for i in 0..(n + m - 1) {
        print!("{}", a[i]);
      }
      println!();
      return;
    }
  }

  println!("Goofy");
}

fn main() {
  loop {
    let v = input_integers();
    let n = v[0] as usize;
    let m = v[1] as usize;

    if n == 0 && m == 0 {
      break;
    }

    solve(n, m);
  }
}
