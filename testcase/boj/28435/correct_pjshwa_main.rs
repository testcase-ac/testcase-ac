use io::Write;
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

const MOD: usize = 1_000_000_007;

fn lpow(x: usize, mut y: usize) -> usize {
  let (mut ret, mut cur) = (1, x);
  while y > 0 {
    if y % 2 == 1 {
      ret = (ret * cur) % MOD;
    }
    cur = (cur * cur) % MOD;
    y /= 2;
  }
  ret
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, k) = (scan.token::<usize>(), scan.token::<usize>());

  let mut cnt = vec![0; k];
  for _ in 0..n {
    let x = scan.token::<usize>();
    cnt[x % k] += 1;
  }

  // one of them, or none
  let mut ans = cnt[0] + 1;
  for i in 1..k {
    if i > k - i { break; }
    if i == k - i { ans = (ans * (cnt[i] + 1)) % MOD; }
    else {
      let (c1, c2) = (cnt[i], cnt[k - i]);
      let s1 = (lpow(2, c1) + MOD - 1) % MOD;
      let s2 = (lpow(2, c2) + MOD - 1) % MOD;

      // either choose elements from one set, or none
      let cur = (s1 + s2 + 1) % MOD;
      ans = (ans * cur) % MOD;
    }
  }

  // only sets with 2 or more elements are good
  ans = (ans + MOD - n - 1) % MOD;
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
