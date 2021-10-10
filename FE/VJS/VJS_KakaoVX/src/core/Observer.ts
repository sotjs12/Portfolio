let currentObserver: Function | null;

const observe = (fn: Function) => {
  currentObserver = fn;
  fn();
  currentObserver = null;
};

const observable = (state: any) => {
  const observerMap: any = {};
  return new Proxy(state, {
    get(target: any, name: string) {
      observerMap[name] = observerMap[name] || new Set();
      if (currentObserver) observerMap[name].add(currentObserver);
      return target[name];
    },
    set(target: any, name: string, value: any) {
      if (target[name] === value) return true;
      if (JSON.stringify(target[name]) === JSON.stringify(value)) return true;

      // eslint-disable-next-line no-param-reassign
      target[name] = value;
      observerMap[name].forEach((fn: Function) => fn());
      return true;
    },
  });
};

export { observe, observable };
