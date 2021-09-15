import { NavLink } from "../router";
import Component from "../core/Component";

const NavItem = (content) => `
    <div class='nav-item'>${content}</div>
`;
const NavBar = (pathname) => `
    ${NavLink('/', NavItem('Home'))}
    ${NavLink('/about', NavItem('About'))}
    ${NavLink('/about2', NavItem('About2'))}
`;

export default NavBar;