let images = [
  "undraw_aircraft_fbvl.svg",
  "undraw_Beer_celebration_cefj.svg",
  "undraw_cabin_hkfr.svg",
  "undraw_fast_car_p4cu.svg",
  "undraw_game_world_0o6q.svg",
  "undraw_Golden_gate_bridge_jkph.svg",
  "undraw_Ordinary_day_3gk3.svg",
  "undraw_Outer_space_drqu.svg",
  "undraw_Playful_cat_rchv.svg",
  "undraw_playing_cards_cywn.svg",
  "undraw_Ride_till_I_can_no_more_44wq.svg",
  "undraw_true_love_cy8x.svg",
];

type level = {
  number: int,
  size: int,
  lives: int,
  cols: int,
  rows: int,
};

let levels = [
  {number: 1, size: 6, lives: 3, cols: 3, rows: 2},
  {number: 2, size: 8, lives: 4, cols: 4, rows: 2},
  {number: 3, size: 12, lives: 6, cols: 4, rows: 3},
  {number: 4, size: 16, lives: 8, cols: 4, rows: 4},
  {number: 5, size: 20, lives: 12, cols: 5, rows: 4},
  {number: 6, size: 24, lives: 16, cols: 6, rows: 4},
  {number: 7, size: 24, lives: 12, cols: 6, rows: 4},
];

type status =
  | NoSelectedCard
  | OneSelectedCard
  | TwoSelectedCards
  | GameWon
  | GameLost;

type card = {
  image: string,
  show: bool,
};

type state = {
  status,
  currentLevel: level,
  cards: list(card),
  livesLeft: int,
  selectedCards: (option(int), option(int)),
};

type action =
  | ChooseCard(int)
  | HideSelectedCards
  | SetNewGame(int);

let updateCardStatus = (cards, numCard) =>
  ListLabels.mapi(
    ~f=(index, item) => index == numCard ? {...item, show: true} : item,
    cards,
  );

let hideSelectedCards = (cards, selected) =>
  switch (selected) {
  | (Some(card1), Some(card2)) =>
    ListLabels.mapi(
      ~f=
        (index, item) =>
          index == card1 || index == card2 ? {...item, show: false} : item,
      cards,
    )
  | _ => cards
  };

let prepareNewGame = levelNumber => {
  let level = ListLabels.nth(levels, levelNumber - 1);
  let randomImages =
    Belt.Array.makeByAndShuffle(ListLabels.length(images), i => i)
    |> Belt.Array.slice(~len=level.size / 2, ~offset=0)
    |> ArrayLabels.map(~f=index => ListLabels.nth(images, index))
    |> Array.to_list;
  let cards =
    Belt.Array.makeByAndShuffle(level.size, i =>
      ListLabels.nth(randomImages, i mod level.size / 2)
    )
    |> Array.to_list
    |> ListLabels.map(~f=image => {image, show: false});
  {
    status: NoSelectedCard,
    currentLevel: level,
    livesLeft: level.lives,
    cards,
    selectedCards: (None, None),
  };
};

let initialState = levelNumber => prepareNewGame(levelNumber);

let are2CardsEqual = (l, i1, i2) =>
  ListLabels.nth(l, i1).image == ListLabels.nth(l, i2).image;

let reducer = (state, action) => {
  switch (state.status, action) {
  | (NoSelectedCard, ChooseCard(numCard)) => {
      ...state,
      status: OneSelectedCard,
      cards: updateCardStatus(state.cards, numCard),
      selectedCards: (Some(numCard), None),
    }
  | (OneSelectedCard, ChooseCard(numCard)) =>
    switch (numCard, fst(state.selectedCards)) {
    | (a, Some(b)) when are2CardsEqual(state.cards, a, b) =>
      let cards = updateCardStatus(state.cards, numCard);
      let isGameFinished = !ListLabels.exists(~f=i => !i.show, cards);
      if (isGameFinished) {
        Analytics.logEvent(
          ~category="Memo",
          ~action=
            "Concluded Level " ++ string_of_int(state.currentLevel.number),
        );
      };
      {
        ...state,
        status: isGameFinished ? GameWon : NoSelectedCard,
        cards,
        selectedCards: (None, None),
      };

    | _ =>
      let livesLeft = state.livesLeft - 1;
      if (livesLeft <= 0) {
        Analytics.logEvent(
          ~category="Memo",
          ~action="Lost Level " ++ string_of_int(state.currentLevel.number),
        );
      };
      {
        ...state,
        status: livesLeft <= 0 ? GameLost : TwoSelectedCards,
        cards: updateCardStatus(state.cards, numCard),
        selectedCards: (fst(state.selectedCards), Some(numCard)),
        livesLeft,
      };
    }

  | (TwoSelectedCards, HideSelectedCards) => {
      ...state,
      status: NoSelectedCard,
      cards: hideSelectedCards(state.cards, state.selectedCards),
      selectedCards: (None, None),
    }
  | (_, SetNewGame(levelNumber)) => prepareNewGame(levelNumber)
  | _ => state
  };
};