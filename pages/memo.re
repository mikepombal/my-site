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

module Card = {
  [@react.component]
  let make = (~img, ~num, ~show, ~chooseCard) => {
    let onClick = React.useCallback1(_event => chooseCard(num), [||]);
    <div
      className="
        border border-gray-300 rounded-lg w-24 h-24 bg-white flex justify-center items-center shadow overflow-hidden
        sm:w-32 sm:h-32
        md:w-40 md:h-40
        lg:w-48 lg:h-48
      ">
      {show
         ? <div
             className="
            bg-gray-100 w-full h-full flex justify-center items-center text-gray-800 p-6
        ">
             <img src=img alt={"image " ++ string_of_int(num)} />
           </div>
         : <div
             onClick
             className="
            bg-endless-clouds w-full h-full
        "
           />}
    </div>;
  };
};

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

let reducer = (state, action) => {
  switch (state.status, action) {
  | (NoSelectedCard, ChooseCard(numCard)) => {
      ...state,
      status: OneSelectedCard,
      cards: updateCardStatus(state.cards, numCard),
      selectedCards: (Some(numCard), None),
    }
  | (OneSelectedCard, ChooseCard(numCard)) => {
      ...state,
      status: TwoSelectedCards,
      cards: updateCardStatus(state.cards, numCard),
      selectedCards: (fst(state.selectedCards), Some(numCard)),
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

let initialState = size => {
  let randomImages = ListUtils.getNthRandomItems(images, size / 2);
  let cards =
    ListLabels.append(randomImages, randomImages)
    |> ListUtils.shuffle
    |> ListLabels.map(~f=image => {image, show: false});

  {status: NoSelectedCard, size, cards, selectedCards: (None, None)};
};

[@react.component]
let make = (~size=6) => {
  let (state, dispatch) = React.useReducer(reducer, initialState(size));
  let chooseCard =
    React.useCallback1(num => dispatch(ChooseCard(num)), [||]);
  React.useEffect1(
    () => {
      if (state.status == TwoSelectedCards) {
        let _ =
          Js.Global.setTimeout(() => dispatch(HideSelectedCards), 2000);
        ();
      };
      None;
    },
    [|state.status|],
  );

  <div className="flex w-full h-screen items-center justify-center">
    <div
      className="
        grid grid-cols-3 gap-4
        md:grid-cols-4 gap-5
        xl:grid-cols-6
    ">
      {ReasonReact.array(
         Array.map(
           x => {
             let card = ListLabels.nth(state.cards, x);
             <Card
               key={"card-" ++ string_of_int(x)}
               num=x
               show={card.show}
               img={card.image}
               chooseCard
             />;
           },
           Array.of_list(ListUtils.range(0, size - 1)),
         ),
       )}
    </div>
  </div>;
};

let default = make;