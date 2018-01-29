type action =
  | ADD_TODO(string)
  | REMOVE_TODO(Todo.todo);

type state = {todos: list(Todo.todo)};

let component = ReasonReact.reducerComponent("Page");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    let todos = [];
    {todos: todos};
  },
  reducer: (action, state) =>
    switch action {
    | ADD_TODO(text) =>
      switch text {
      | "" => ReasonReact.NoUpdate
      | _ =>
        let todos = state.todos @ [{title: text, completed: false}];
        ReasonReact.Update({todos: todos});
      }
    | REMOVE_TODO(todo) =>
      let todos = state.todos |> List.filter(candidate => candidate !== todo);
      ReasonReact.Update({todos: todos});
    },
  render: ({state, send}) => {
    let {todos} = state;
    let todoItems =
      todos
      |> List.mapi((i, todo) =>
           <div
             style=(
               ReactDOMRe.Style.make(
                 ~display="flex",
                 ~justifyContent="space-between",
                 ()
               )
             )>
             <div
               style=(
                 ReactDOMRe.Style.make(
                   ~fontSize="20px",
                   ~margin="10px 10px",
                   ~borderBottom="1px solid #ccc",
                   ()
                 )
               )
               key=(string_of_int(i) ++ Todo.(todo.title))>
               (ReasonReact.stringToElement(Todo.(todo.title)))
             </div>
             <div>
               <button onClick=((_) => send(REMOVE_TODO(todo)))>
                 (ReasonReact.stringToElement("Remove"))
               </button>
             </div>
           </div>
         );
    <div>
      <h1 style=(ReactDOMRe.Style.make(~textAlign="center", ()))>
        (ReasonReact.stringToElement(message))
      </h1>
      <div> <Todo todoItems onClick=(text => send(ADD_TODO(text))) /> </div>
    </div>;
  }
};