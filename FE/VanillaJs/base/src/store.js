import { Store, createStore } from "./core/store.js";

// const store = new Store({
//     state: {
//         a: 10,
//         b: 20
//     },
//     mutations: {
//         SET_A(state, payload) {
//             state.a = payload;
//         },
//         SET_B(state, payload) {
//             state.b = payload;
//         }
//     },
//     actions: {}
// });

const initState = {
    a: 10,
    b: 20
}

const SET_A = 'SET_A';
const SET_B = 'SET_B';

const store = createStore((state = initState, action = {}) => {
    switch (action.type) {
        case SET_A:
            return { ...state, a: action.payload };
        case SET_B:
            return { ...state, b: action.payload };
        default:
            return state;
    }
});

const setA = (payload) => ({ type: SET_A, payload });
const setB = (payload) => ({ type: SET_B, payload });

export { store, SET_A, SET_B, setA, setB };