[@react.component]
let make = (~onSubmitName) => {
  let (name, setName) = React.useState(() => "");

  let onChange = (e: ReactEvent.Form.t): unit => {
    let value = e->ReactEvent.Form.target##value;
    setName(value);
  };

  let onSubmit = (e: ReactEvent.Form.t): unit => {
    ReactEvent.Form.preventDefault(e);
    Js.log("Submiting");
    onSubmitName(name);
  };

  <div className="w-full max-w-xs">
    <form className="bg-white shadow-md rounded px-8 pt-6 pb-8 mb-4" onSubmit>
      <div className="mb-4">
        <label
          className="block text-gray-700 text-sm font-bold mb-2"
          htmlFor="name">
          {S.str("Choose a name")}
        </label>
        <input
          className="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
          id="name"
          type_="text"
          placeholder="Name"
          value=name
          onChange
        />
      </div>
      <div className="flex items-center justify-between">
        <button
          className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline"
          type_="submit"
          disabled={String.length(name) == 0}>
          {S.str("Create")}
        </button>
      </div>
    </form>
  </div>;
};