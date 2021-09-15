class Router {
    routes = [];
    $routeView;
    pathName;

    constructor($el, routes) {
        this.routes = routes;
        this.$routeView = document.createElement('div');
        $el.appendChild(this.$routeView);
        this.#loadInitialRoute();
    }
    loadRoute(...urlSegments) {
        const matchedRoute = this.#matchUrlToRoute(urlSegments);
        const url = `/${urlSegments.join('/')}`;
        if (window.location.pathname != url)
            window.history.pushState({}, '', window.location.origin + url);

        this.$routeView.innerHTML = '';
        new matchedRoute.template(this.$routeView, matchedRoute.params);

        const links = document.querySelectorAll('.nav-link');
        links.forEach($el => {
            $el.addEventListener('click', e => {
                const $target = e.target.closest('.nav-link');
                const route = $target.getAttribute('route');

                this.loadRoute(...this.#getPathSegments(route));
            });
        })
    }
    #matchUrlToRoute(urlSegments) {
        const routeParams = {};
        const matchedRoute = this.routes.find(route => {
            const routePathSegments = route.path.split('/').slice(1);
            if (routePathSegments.length !== urlSegments.length) return false;
            const match = routePathSegments.every((routePathSegment, i) => {
                return routePathSegment === urlSegments[i] || routePathSegment[0] === ':';
            });
            if (match) {
                routePathSegments.forEach((segment, i) => {
                    if (segment[0] === ':') {
                        const propName = segment.slice(1);
                        routeParams[propName] = decodeURIComponent(urlSegments[i]);
                    }
                });
            }
            return match
        });
        return { ...matchedRoute, parms: routeParams };
    }
    #getPathSegments(route) {
        const pathnameSplit = route.split('/');
        const pathSegments = pathnameSplit.length > 1 ? pathnameSplit.slice(1) : '';
        return pathSegments;
    }
    #loadInitialRoute() {
        this.loadRoute(...this.#getPathSegments(window.location.pathname));
        window.onpopstate = (e) => {
            this.loadRoute(...this.#getPathSegments(window.location.pathname));
        }
    }

}

const NavLink = (route, template) => {
    return `
    <div class="nav-link" route = ${route}>
        ${template}
    </div>
    `
}
export { Router, NavLink };