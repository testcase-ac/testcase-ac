const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let input = [];
rl.on('line', function (line) {
  input.push(line.split(" ").map(e => parseInt(e)));
}).on('close', function () {
  let [n, m] = input.shift();
  let numbers = input.map(e => e[0]);

  function do_search(num) {
    var cMoney = 0;
    var cCount = 0;
    for (el of numbers) {
      if (num < el) return 100001;
  
      if (cMoney < el) {
        cMoney = num;
        cCount++;
      }
      cMoney -= el;
    }
    return cCount;
  }

  var left = 1, right = 2000000000;
  var mid = Math.floor((left + right) / 2);

  while (left < right) {
    if (do_search(mid) > m) left = mid + 1;
    else right = mid;
  
    mid = Math.floor((left + right) / 2);
  }
  
  console.log(mid);
  process.exit();
});
