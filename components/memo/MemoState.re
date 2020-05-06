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

type status =
  | NoSelectedCard
  | OneSelectedCard
  | TwoSelectedCards;

type card = {
  image: string,
  show: bool,
};

type state = {
  status,
  size: int,
  cards: list(card),
  selectedCards: (option(int), option(int)),
};

type action =
  | ChooseCard(int)
  | HideSelectedCards;

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

let initialState = size => {
  let randomImages = ListUtils.getNthRandomItems(images, size / 2);
  let cards =
    ListLabels.append(randomImages, randomImages)
    |> ListUtils.shuffle
    |> ListLabels.map(~f=image => {image, show: false});

  {status: NoSelectedCard, size, cards, selectedCards: (None, None)};
};

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
    | (a, Some(b)) when are2CardsEqual(state.cards, a, b) => {
        ...state,
        status: NoSelectedCard,
        cards: updateCardStatus(state.cards, numCard),
        selectedCards: (None, None),
      }

    | _ => {
        ...state,
        status: TwoSelectedCards,
        cards: updateCardStatus(state.cards, numCard),
        selectedCards: (fst(state.selectedCards), Some(numCard)),
      }
    }

  | (TwoSelectedCards, HideSelectedCards) => {
      ...state,
      status: NoSelectedCard,
      cards: hideSelectedCards(state.cards, state.selectedCards),
      selectedCards: (None, None),
    }
  | _ => state
  };
};