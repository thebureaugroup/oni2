/*
 * GlobalContext.re
 *
 * This is a workaround for the lack of Context API today in brisk-reconciler: https://github.com/briskml/brisk-reconciler/issues/16
 * The idea is, prior to rendering, we'll pull up the stuff we need across the render tree
 * (things that would be provided via `<Provider />`), and store them here.
 *
 * Hopefully, once there is a context API, this can be wholly replaced with it!
 */
open Oni_Core.Types;
open Oni_Model;

type notifyWindowTreeSizeChanged = (~width: int, ~height: int, unit) => unit;
type notifyEditorSizeChanged =
  (~editorGroupId: int, ~width: int, ~height: int, unit) => unit;
type editorScrollDelta = (~deltaY: float, unit) => unit;
type editorSetScroll = (~scrollY: float, unit) => unit;

type t = {
  notifyEditorSizeChanged,
  notifyWindowTreeSizeChanged,
  editorScrollDelta,
  editorSetScroll,
  setActiveWindow: (int, int) => unit,
  openEditorById: int => unit,
  closeEditorById: int => unit,
  hideNotification: int => unit,
  dispatch: Actions.t => unit,
  getState: unit => State.t,
  state: State.t,
};

let viewNoop: Views.viewOperation =
  (~path as _="", ~id as _=0, ~openMethod as _=Buffer, ()) => ();

let default = {
  state: State.create(),
  getState: () => State.create(),
  notifyWindowTreeSizeChanged: (~width as _, ~height as _, ()) => (),
  notifyEditorSizeChanged:
    (~editorGroupId as _, ~width as _, ~height as _, ()) =>
    (),
  editorScrollDelta: (~deltaY as _, ()) => (),
  editorSetScroll: (~scrollY as _, ()) => (),
  hideNotification: _ => (),
  openEditorById: _ => (),
  setActiveWindow: (_, _) => (),
  dispatch: _ => (),
  closeEditorById: _ => (),
};

let _current: ref(t) = ref(default);

let current = () => _current^;

let set = (v: t) => _current := v;
