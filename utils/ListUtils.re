let rec range = (start: int, end_: int) => {
  start > end_ ? [] : [start, ...range(start + 1, end_)];
};

let rec removeAll = (value, l) => {
  switch (l) {
  | [] => []
  | [head, ...tail] when head == value => removeAll(value, tail)
  | [head, ...tail] => [head, ...removeAll(value, tail)]
  };
};

let rec getNthRandomItems = (l, num) => {
  switch (num) {
  | 0 => []
  | _ =>
    let item = ListLabels.nth(l, Random.int(num));
    [item, ...getNthRandomItems(removeAll(item, l), num - 1)];
  };
};