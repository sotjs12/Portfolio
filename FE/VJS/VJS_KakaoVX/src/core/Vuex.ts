import { observable } from './Observer';

export default class Vuex {
  #state: any;

  #mutations: any;

  #actions: any;

  state: any = {};

  constructor({ state, mutations, actions }: { state: any, mutations?: any, actions?: any }) {
    this.#state = observable(state);
    this.#mutations = mutations;
    this.#actions = actions;

    Object.keys(state).forEach((key) => {
      Object.defineProperty(this.state, key, {
        get: () => this.#state[key],
      });
    });
  }

  commit(action: string, payload: any) {
    this.#mutations[action](this.#state, payload);
  }

  dispatch(action: string, payload: any): any {
    return this.#actions[action]({
      state: this.#state,
      commit: this.commit.bind(this),
      dispatch: this.dispatch.bind(this),
    }, payload);
  }
}
