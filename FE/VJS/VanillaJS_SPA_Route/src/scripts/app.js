import { Router } from "./router";
import About from './components/about.js';
import Home from './components/home.js';

const routes = [
    {
        path: '/',
        template: Home
    },
    {
        path: '/about',
        template: About
    },
    {
        path: '/about2',
        template: About
    }
]

class App {
    $router;
    $el;
    constructor($el) {
        this.$el = $el;
        this.$router = new Router($el, routes);
    }
}


const $app = new App(document.querySelector("#app"));