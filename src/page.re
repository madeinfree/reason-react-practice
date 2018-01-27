type action =
  | ADD_TODO(string);

/* type todoo = Todo.todo;

   type todoList = array(todoo); */
type state = {todos: list(Todo.todo)};

let component = ReasonReact.reducerComponent("Page");

/* let createNewTodo = title : Todo.todo => (
     {title: title, completed: false}: Todo.todo
   ); */
let make = (~message, _children) => {
  ...component,
  initialState: () => {
    let todos = [];
    {todos: todos};
  },
  reducer: (action, state) =>
    switch action {
    | ADD_TODO(text) =>
      let todos = state.todos @ [{title: text, completed: false}];
      ReasonReact.Update({todos: todos});
    },
  render: ({state, send}) => {
    let {todos} = state;
    let todoItems =
      todos
      |> List.map(todo =>
           <div key=(string_of_float(Js.Date.now()) ++ Todo.(todo.title))>
             (ReasonReact.stringToElement(Todo.(todo.title)))
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