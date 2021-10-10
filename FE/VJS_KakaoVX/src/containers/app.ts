import Components from '../core/Component';
import { vuex } from './vuex';

const InputA = () => `<input id="stateA" value="${vuex.state.a}" size="5" />`;
const InputB = () => `<input id="stateB" value="${vuex.state.b}" size="5" />`;
const Calculator = () => `<p>a + b = ${vuex.state.a + vuex.state.b}</p>`;

export default class App extends Components {
  setEvent() {
  }

  template() {
    return `
      ${InputA()}
      ${InputB()}
      ${Calculator()}
    `;
  }
}
