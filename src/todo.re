type action =
  | Change(string);

type todo = {
  title: string,
  completed: bool
};

type state = {editText: string};

let component = ReasonReact.reducerComponent("Todo");

let todoTitleStyle = ReactDOMRe.Style.make(~textAlign="center", ());

let make = (~todoItems, ~onClick, _children) => {
  ...component,
  initialState: () => {editText: ""},
  reducer: action =>
    switch action {
    | Change(text) => ((_) => ReasonReact.Update({editText: text}))
    },
  render: props =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~padding="10px",
          ~width="600px",
          ~height="600px",
          ~margin="0 auto",
          ~border="1px solid #ccc",
          ()
        )
      )>
      <h1 style=todoTitleStyle> (ReasonReact.stringToElement("TodoList")) </h1>
      <input
        _type="text"
        value=props.state.editText
        onChange=(
          event =>
            props.send(
              Change(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
      <button onClick=((_) => onClick(props.state.editText))>
        (ReasonReact.stringToElement("ADD TODO"))
      </button>
      <div> (ReasonReact.arrayToElement(Array.of_list(todoItems))) </div>
    </div>
};