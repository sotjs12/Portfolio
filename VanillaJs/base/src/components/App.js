import Component from "../core/Component.js";
import { store, setA, setB } from "../store.js";

export default class App extends Component {
    template() {
        const { a, b } = store.getState();
        return `
            <input id="stateA" value="${a}" size="5" />
            <input id="stateB" value="${b}" size="5" />
            <p>a + b = ${a + b}</p>
        `;
    }
    setEvent() {
        const { $el } = this;

        $el.querySelector("#stateA").addEventListener('change', ({ target }) => {
            store.dispatch(setA(Number(target.value)));
        });
        $el.querySelector("#stateB").addEventListener('change', ({ target }) => {
            store.dispatch(setB(Number(target.value)));
        });
    }
}