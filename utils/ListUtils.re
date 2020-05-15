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

let rec remove = (value, l) => {
  switch (l) {
  | [] => []
  | [head, ...tail] when head == value => tail
  | [head, ...tail] => [head, ...remove(value, tail)]
  };
};