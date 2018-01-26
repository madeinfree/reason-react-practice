type action =
  | ADD_TODO(Todo.todo);

type state = {todos: list(Todo.todo)};

let component = ReasonReact.reducerComponent("Page");

let make = (~message, _children) => {
  ...component,
  initialState: () => {todos: []},
  reducer: (action, state) =>
    switch action {
    | ADD_TODO(todo) => ReasonReact.Update({todos: [todo, ...state.todos]})
    },
  render: (_) =>
    <div>
      <h1 style=(ReactDOMRe.Style.make(~textAlign="center", ()))>
        (ReasonReact.stringToElement(message))
      </h1>
      <div> <Todo /> </div>
    </div>
};