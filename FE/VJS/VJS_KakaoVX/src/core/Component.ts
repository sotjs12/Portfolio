import { observable, observe } from './Observer';

export default class Components {
  state: any;

  props: any;

  $el!: HTMLElement;

  constructor($el: HTMLElement, props?: any) {
    this.$el = $el;
    this.props = props;
    this.setup();
  }

  setup() {
    this.state = observable(this.initState());
    observe(() => {
      this.render();
      this.setEvent();
      this.mounted();
    });
  }

  mounted() { }

  setEvent() { }

  template() { return ''; }

  initState() { return {}; }

  render() { this.$el.innerHTML = this.template(); }
}
