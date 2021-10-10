/* eslint-disable no-param-reassign */
import Vuex from '../core/Vuex';

export const ACTION_TYPE = {
  SET_A: 'SET_A',
  SET_B: 'SET_B',
};

interface State {
  a: number;
  b: number;
}

const initState: State = {
  a: 10,
  b: 20,
};

export const vuex = new Vuex({
  state: initState,
  mutations: {
    [ACTION_TYPE.SET_A](state: State, payload: any) {
      state.a = payload;
    },
    [ACTION_TYPE.SET_B](state: State, payload: any) {
      state.b = payload;
    },
  },
});

export const redux = {};
