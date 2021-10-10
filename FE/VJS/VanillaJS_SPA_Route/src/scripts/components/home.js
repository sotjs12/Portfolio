import Component from "../core/Component.js";
import NavBar from "./navBar.js";

export default class Home extends Component {

    template() {
        return `
            ${NavBar('/')}
            <div>home</div>
        `;
    }
}