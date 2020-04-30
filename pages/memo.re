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
  let make = (~img, ~num, ~show=true) =>
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
             className="
            bg-endless-clouds w-full h-full
        "
           />}
    </div>;
};

[@react.component]
let make = () => {
  <div className="flex w-full h-screen items-center justify-center">
    <div
      className="
        grid grid-cols-3 gap-4
        md:grid-cols-4
        xl:grid-cols-6
    ">
      {ReasonReact.array(
         Array.map(
           x =>
             <Card
               key={"card-" ++ string_of_int(x)}
               num=x
               img={ListLabels.nth(images, x - 1)}
             />,
           Array.of_list(ListUtils.range(1, 12)),
         ),
       )}
    </div>
  </div>;
};

let default = make;