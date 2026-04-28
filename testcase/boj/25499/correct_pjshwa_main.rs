use io::Write;
use std::{io, str, cmp};

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

#[derive(Clone)]
pub struct Pair {
  pub p: i64,
  pub h: i64,
}

const INF : i64 = 1e18 as i64;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<i64>();
  let mut a = vec![];
  for i in 0..n {
    let v = scan.token::<i64>();
    if v > 0 {
      a.push(Pair { p: i + 1, h: v });
    }
  }

  let z = a.len();
  if z == 0 {
    writeln!(out, "{}", n).ok();
    return;
  }

  // 0: stand still
  // 1: tip to left
  // 2: tip to right
  let mut d = vec![vec![INF; 3]; z];
  d[0][0] = a[0].p - 1;
  if a[0].h <= a[0].p - 1 {
    d[0][1] = a[0].p - 1 - a[0].h;
  }
  d[0][2] = a[0].p;

  for i in 1..z {
    for pj in 0..3 {
      for j in 0..3 {
        if pj == 0 && j == 0 {
          d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - 1);
        }
        if pj == 0 && j == 1 {
          if a[i].h <= a[i].p - a[i - 1].p - 1 {
            d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - 1 - a[i].h);
          }
        }
        if pj == 0 && j == 2 {
          d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p);
        }
        if pj == 1 && j == 0 {
          d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p);
        }
        if pj == 1 && j == 1 {
          if a[i].h <= a[i].p - a[i - 1].p {
            d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - a[i].h);
          }
        }
        if pj == 1 && j == 2 {
          d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p + 1);
        }
        if pj == 2 && j == 0 {
          if a[i - 1].h <= a[i].p - a[i - 1].p - 1 {
            d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - 1 - a[i - 1].h);
          }
        }
        if pj == 2 && j == 1 {
          if a[i - 1].h + a[i].h <= a[i].p - a[i - 1].p - 1 {
            d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - 1 - a[i - 1].h - a[i].h);
          }
        }
        if pj == 2 && j == 2 {
          if a[i - 1].h <= a[i].p - a[i - 1].p {
            d[i][j] = cmp::min(d[i][j], d[i - 1][pj] + a[i].p - a[i - 1].p - a[i - 1].h);
          }
        }
      }
    }
  }

  let mut ans = INF;
  ans = ans.min(d[z - 1][0] + n - a[z - 1].p);
  ans = ans.min(d[z - 1][1] + n - a[z - 1].p + 1);
  if a[z - 1].h <= n - a[z - 1].p {
    ans = ans.min(d[z - 1][2] + n - a[z - 1].p - a[z - 1].h);
  }
  writeln!(out, "{}", ans).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
