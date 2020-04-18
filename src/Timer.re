// Define the shape of timer's state
type state = {
  seconds: int,
  isTicking: bool,
};

// Define actions of the timer
type action =
  | Start
  | Stop
  | Reset
  | Tick;

// Implement a reducer to manage each action
let reducer = (state, action) => {
  switch (action) {
  | Start => {...state, isTicking: true}
  | Stop => {...state, isTicking: false}
  | Reset => {seconds: 30, isTicking: false}
  | Tick =>
    state.isTicking && state.seconds > 0
      ? {...state, seconds: state.seconds - 1} : state
  };
};

let initialState = {seconds: 30, isTicking: false};

// button component as a module
module Button = {
  [@react.component]
  let make = (~label, ~onClick) => {
    <button onClick> {label |> ReasonReact.string} </button>;
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);

    // clear interval when unmounting
    Some(() => Js.Global.clearInterval(timerId));
  });

  // interop in js to log state
  Js.log(state);

  <div
    style={ReactDOMRe.Style.make(
      ~width="600px",
      ~margin="0 auto",
      ~display="flex",
      ~alignItems="center",
      ~justifyContent="center",
      (),
    )}>
    <h3 style={ReactDOMRe.Style.make(~marginRight="5rem", ())}>
      {ReasonReact.string(
         "Pomodoro Timer : " ++ string_of_int(state.seconds),
       )}
    </h3>
    {state.isTicking
       ? <Button onClick={_ => dispatch(Stop)} label="STOP" />
       : <Button onClick={_ => dispatch(Start)} label="START" />}
    <Button onClick={_ => dispatch(Reset)} label="RESET" />
  </div>;
};