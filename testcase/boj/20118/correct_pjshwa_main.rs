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

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());

  let mut ans = vec![(1, 1), (2, 2), (1, 1), (2, 2)];
  let (mut x, mut y) = (2, 2);
  loop {
    if x + 2 <= n && y + 2 <= m {
      ans.push((x + 1, y + 1));
      ans.push((x + 2, y + 2));
      ans.push((x + 1, y + 1));
      ans.push((x + 2, y + 2));
      x += 2; y += 2;
    }
    else if x + 2 <= n {
      ans.push((x + 1, y));
      ans.push((x + 2, y));
      ans.push((x + 1, y));
      ans.push((x + 2, y));
      x += 2;
    }
    else if y + 2 <= m {
      ans.push((x, y + 1));
      ans.push((x, y + 2));
      ans.push((x, y + 1));
      ans.push((x, y + 2));
      y += 2;
    }
    else if x == n - 1 && y == m - 1 {
      ans.push((x + 1, y));
      ans.push((x + 1, y + 1));
      ans.push((x + 1, y));
      ans.push((x + 1, y + 1));
      break;
    }
    else if x == n - 1 {
      ans.push((x + 1, y - 1));
      ans.push((x + 1, y));
      ans.push((x + 1, y - 1));
      ans.push((x + 1, y));
      break;
    }
    else if y == m - 1 {
      ans.push((x - 1, y + 1));
      ans.push((x, y + 1));
      ans.push((x - 1, y + 1));
      ans.push((x, y + 1));
      break;
    }
    else {
      break;
    }
  }

  writeln!(out, "{}", ans.len()).ok();
  for (x, y) in ans {
    writeln!(out, "{} {}", x - 1, y - 1).ok();
  }
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
