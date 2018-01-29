type action =
  | Change(string)
  | Clear;

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
    | Clear => ((_) => ReasonReact.Update({editText: ""}))
    },
  render: props =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~padding="10px",
          ~width="600px",
          ~margin="0 auto",
          ~border="1px solid #ccc",
          ()
        )
      )>
      <h1 style=todoTitleStyle> (ReasonReact.stringToElement("TodoList")) </h1>
      <input
        _type="text"
        placeholder="write somthing..."
        style=(
          ReactDOMRe.Style.make(
            ~width="100%",
            ~height="30px",
            ~border="1px solid #ccc",
            ~borderRadius="5px",
            ()
          )
        )
        autoFocus=Js.true_
        value=props.state.editText
        onKeyDown=(
          event =>
            if (ReactEventRe.Keyboard.keyCode(event) === 13) {
              onClick(props.state.editText);
              props.send(Clear);
            }
        )
        onChange=(
          event =>
            props.send(
              Change(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
      <div
        style=(ReactDOMRe.Style.make(~overflow="auto", ~height="600px", ()))>
        (ReasonReact.arrayToElement(Array.of_list(todoItems)))
      </div>
    </div>
};