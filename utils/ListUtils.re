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

let rec getNthRandomItems = (l, num) => {
  switch (num) {
  | 0 => []
  | _ =>
    let item = ListLabels.length(l) |> Random.int |> ListLabels.nth(l);
    [item, ...getNthRandomItems(remove(item, l), num - 1)];
  };
};

let rec shuffle = l => {
  switch (l) {
  | [] => []
  | _ =>
    let item = ListLabels.length(l) |> Random.int |> ListLabels.nth(l);
    [item, ...shuffle(remove(item, l))];
  };
};