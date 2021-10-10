import Component from "../core/Component.js";
import NavBar from "./navBar.js";

export default class About extends Component {

    template() {
        return `
            ${NavBar('/')}
            <div>about</div>
        `;
    }
}