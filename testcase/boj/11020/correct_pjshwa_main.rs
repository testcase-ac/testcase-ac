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

const PI: f64 = std::f64::consts::PI;

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let mut a = vec![];
  for _ in 0..n {
    let (h, _) = (scan.token::<f64>(), scan.token::<f64>());
    a.push(h);
  }
  a.sort_by(|a, b| a.partial_cmp(b).unwrap());

  for s in (1..=n).rev() {
    if n % s != 0 { continue; }

    // i: starting nugget
    for i in 0..n {
      let mut t = vec![0; s];

      for j in 0..n {
        let mut pos = a[j] - a[i];
        if pos < 0.0 { pos += 2.0 * PI; }

        let nth = (pos / (2.0 * PI / s as f64)).floor() as usize;
        t[nth] += 1;
      }

      if t.iter().all(|&x| x == n / s) {
        writeln!(out, "{} slices", s).ok();
        return;
      }
    }

  }
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  // let t = 1;
  let t = scan.token::<usize>();
  for i in 1..=t {
    writeln!(out, "Data Set {}:", i).ok();
    solve(&mut scan, &mut out);
    if i < t { writeln!(out).ok(); }
  }
}
