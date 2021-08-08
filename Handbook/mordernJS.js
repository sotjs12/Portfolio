

/////////////////////
// 구조 분해 할당
/////////////////////
let [a, b, c] = "abc"; // ["a", "b", "c"]
let [one, two, three] = new Set([1, 2, 3]);

function topSalary(salaries) {

    let max = 0;
    let maxName = null;

    for (const [name, salary] of Object.entries(salaries)) {
        if (max < salary) {
            max = salary;
            maxName = name;
        }
    }

    return maxName;
}

/////////////////////
// 나머지 매개변수와 전개문법
/////////////////////
/*
화살표 함수에는 \'arguments\'가 없습니다.
화살표 함수에서 arguments 객체에 접근하면, 외부에 있는 ‘일반’ 함수의 arguments 객체를 가져옵니다.

예시:
*/
function f() {
    let showArg = () => alert(arguments[0]);
    showArg();
}
f(1); // 1

/////////////////////
// 변수의 유효 범위와 클로저
/////////////////////
function makeArmy() {
    let shooters = [];

    let i = 0;
    while (i < 10) {
        let shooter = function () { // shooter 함수
            alert(i); // 몇 번째 shooter인지 출력해줘야 함
        };
        shooters.push(shooter);
        i++;
    }

    return shooters;
}

let army = makeArmy();

army[0](); // 0번째 shooter가 10을 출력함
army[5](); // 5번째 shooter 역시 10을 출력함
// 모든 shooter가 자신의 번호 대신 10을 출력하고 있음

function makeArmy() {
    let shooters = [];

    for (let i = 0; i < 10; i++) {
        let shooter = function () { // shooter function
            alert(i); // should show its number
        };
        shooters.push(shooter);
    }
    return shooters;
}

let army = makeArmy();
army[0](); // 0
army[5](); // 5

// call/apply와 데코레이터, 포워딩
/*
Debouncer, Throttle, Delaying 등 기능추가 가능
리엑티브 프로그래밍으로도 구현 가능.
arrow function + apply 조합
아래 나올 바인딩으로도 문제 해결 가능
결국 this 컨텍스트를 갖고다니냐의 문제.
*/
function debounce(func, ms) {
    let timeout;
    return function () {
        clearTimeout(timeout);
        timeout = setTimeout(() => func.apply(this, arguments), ms);
    };
}
function throttle(func, ms) {
    let isThrottled = false,
        savedArgs,
        savedThis;

    function wrapper() {
        if (isThrottled) { // (2)
            savedArgs = arguments;
            savedThis = this;
            return;
        }
        func.apply(this, arguments); // (1)
        isThrottled = true;

        setTimeout(function () {
            isThrottled = false; // (3)
            if (savedArgs) {
                wrapper.apply(savedThis, savedArgs);
                savedArgs = savedThis = null;
            }
        }, ms);
    }

    return wrapper;
}


/////////////////////
// 함수 바인딩
/////////////////////
// 인수만 고정시킬때 파티셜 핼퍼 만드는법
function partial(func, ...argsBound) {
    return function (...args) { // (*)
        return func.call(this, ...argsBound, ...args);
    }
}
// 사용법:
let user = {
    firstName: "John",
    say(time, phrase) {
        alert(`[${time}] ${this.firstName}: ${phrase}!`);
    }
};
// 시간을 고정한 부분 메서드를 추가함
user.sayNow = partial(user.say, new Date().getHours() + ':' + new Date().getMinutes());
user.sayNow("Hello");
// 출력값 예시:
// [10:00] John: Hello!

function askPassword(ok, fail) {
    let password = prompt("비밀번호를 입력해주세요.", '');
    if (password == "rockstar") ok();
    else fail();
}

let user = {
    name: 'John',
    loginOk() {
        alert(`${this.name}님이 로그인하였습니다.`);
    },

    loginFail() {
        alert(`${this.name}님이 로그인에 실패하였습니다.`);
    },
};

askPassword(user.loginOk.bind(user), user.loginFail.bind(user));

/////////////////////
//프로퍼티 플래그와 설명자
/////////////////////
/*

객체 프로퍼티는 값(value) 과 함께 플래그(flag)라 불리는 특별한 속성 세 가지를 갖습니다.

writable – true이면 값을 수정할 수 있습니다. 그렇지 않다면 읽기만 가능합니다.
enumerable – true이면 반복문을 사용해 나열할 수 있습니다. 그렇지 않다면 반복문을 사용해 나열할 수 없습니다.
configurable – true이면 프로퍼티 삭제나 플래그 수정이 가능합니다. 그렇지 않다면 프로퍼티 삭제와 플래그 수정이 불가능합니다.
Object.getOwnPropertyDescriptor메서드를 사용하면 특정 프로퍼티에 대한 정보를 모두 얻을 수 있습니다.

메서드 Object.defineProperty를 사용하면 플래그를 변경할 수 있습니다.

특정 프로퍼티의 enumerable 플래그 값을 false로 설정하면 
for..in 반복문에 나타나지 않게 할 수 있습니다. 커스텀 toString도 열거가 불가능하게 할 수 있습니다.
*/
let user = {};

Object.defineProperty(user, "name", {
    value: "John"
});

let descriptor = Object.getOwnPropertyDescriptor(user, 'name');

alert(JSON.stringify(descriptor, null, 2));
/*
{
  "value": "John",
  "writable": false,
  "enumerable": false,
  "configurable": false
}
 */


/////////////////////
//프로토타입 상속
/////////////////////
/*
for..in은 상속 프로퍼티도 순회대상에 포함시킵니다.
*/
// animal엔 다양한 메서드가 있습니다.
let animal = {
    walk() {
        if (!this.isSleeping) {
            alert(`동물이 걸어갑니다.`);
        }
    },
    sleep() {
        this.isSleeping = true;
    }
};

let rabbit = {
    name: "하얀 토끼",
    __proto__: animal
};

// rabbit의 프로퍼티 isSleeping을 true로 변경합니다.
rabbit.sleep();

alert(rabbit.isSleeping); // true
alert(animal.isSleeping); // undefined (프로토타입에는 isSleeping이라는 프로퍼티가 없습니다.)

/////////////////////
//함수의 prototype 프로퍼티
/////////////////////
/*
개발자가 특별히 할당하지 않더라도 모든 함수는 "prototype" 프로퍼티를 갖습니다.
기본 프로퍼티인 "prototype"은 constructor 프로퍼티 하나만 있는 객체를 가리키는데, 이 constructor 프로퍼티는 함수 자신을 가리킵니다.

ex)
function Rabbit() {}

기본 prototype
Rabbit.prototype = { constructor: Rabbit };

*/

function User(name) {
    this.name = name;
}

let user = new User('John');
let user2 = new user.constructor('Pete');

alert(user2.name); // Pete (잘 동작하네요!)

function User(name) {
    this.name = name;
}
User.prototype = {}; // (*)

let user = new User('John');
let user2 = new user.constructor('Pete');

alert(user2.name); // undefined

/////////////////////
//프로퍼티 getter와 setter
/////////////////////
/*
모던 프로그래밍에서 네이티브 프로토타입 변경을 허용하는 경우는 딱 하나뿐입니다. 바로 폴리필을 만들 때입니다.

*/
if (!String.prototype.repeat) { // repeat이라는 메서드가 없다고 가정합시다
    // 프로토타입에 repeat를 추가

    String.prototype.repeat = function (n) {
        // string을 n회 반복(repeat)합니다.

        // 실제 이 메서드를 구현하려면 코드는 더 복잡해질겁니다.
        // 전체 알고리즘은 명세서에서 확인할 수 있겠죠.
        // 그런데 완벽하지 않은 폴리필이라도 충분히 쓸만합니다.
        return new Array(n + 1).join(this);
    };
}

alert("La".repeat(3)); // LaLaLa

function f() {
    alert("Hello!");
}

Function.prototype.defer = function (ms) {
    setTimeout(this, ms);
}
f.defer(1000); // 1초 후 "Hello!" 출력

//모든 함수의 프로토타입에 ms 밀리세컨초 지연 호출 래퍼를 반환하는 defer(ms) 메서드를 추가하세요.

Function.prototype.defer = function (ms) {
    let f = this;
    return function (...args) {
        setTimeout(() => {
            f.apply(this, args);
        }, ms)
    }
}

function f(a, b) {
    alert(a + b);
}

f.defer(1000)(1, 2); // 1초 후 3을 출력


/////////////////////
//프로토타입 메서드와 __proto__가 없는 객체
/////////////////////

let animal = {
    eats: true
};

// 프로토타입이 animal인 새로운 객체를 생성합니다.
let rabbit = Object.create(animal);

alert(rabbit.eats); // true

alert(Object.getPrototypeOf(rabbit) === animal); // true

Object.setPrototypeOf(rabbit, {}); // rabbit의 프로토타입을 {}으로 바꿉니다.

//shallow copy
let clone = Object.create(Object.getPrototypeOf(obj), Object.getOwnPropertyDescriptors(obj));
//Object.create를 호출하면 obj의 모든 프로퍼티를 포함한 완벽한 사본이 만들어집니다, 
//사본엔 열거 가능한 프로퍼티와 불가능한 프로퍼티, 데이터 프로퍼티, getter, setter 등 모든 프로퍼티가 복제됩니다. [[Prototype]]도 복제되죠.

/*
key/value 쌍을 저장하기 위해 Object.create(null)로 생성된 dictionary 객체가 있습니다.
그 안에 쉼표로 구분된 키 목록을 반환하는 dictionary.toString()메서드를 추가하십시오. toString은 객체 위의 for..in에 나타나서는 안 됩니다.
작동 방식은 다음과 같습니다.
*/
let dictionary = Object.create(null, {
    toString: {
        value() {
            return Object.keys(this).join();
        }
    }
});
// dictionary.toString 메서드를 추가하는 코드

// 데이터를 추가합니다.
dictionary.apple = "Apple";
dictionary.__proto__ = "test"; // __proto__는 여기서 일반적인 프로퍼티 키입니다.

// 반복문에는 apple과 __proto__ 만 있습니다.
for (let key in dictionary) {
    alert(key); // "apple" 다음 "__proto__"입니다.
}

// toString이 동작하는 부분입니다.
alert(dictionary); // "apple,__proto__"


function Rabbit(name) {
    this.name = name;
}
Rabbit.prototype.sayHi = function () {
    alert(this.name);
};

let rabbit = new Rabbit("Rabbit");
rabbit.sayHi();                        // Rabbit
Rabbit.prototype.sayHi();              // undefined 모두 Rabbit.prototype 가 this
Object.getPrototypeOf(rabbit).sayHi(); // undefined
rabbit.__proto__.sayHi();              // undefined

function solution(participant, completion) {

    let completionMap = completion.reduce((ret, key) => {
        if (!ret[key]) ret[key] = 0;
        ret[key]++;
        return ret;
    }, {});

    let answer = "";
    for (let i = 0, key = ""; i < participant.length; ++i) {
        key = participant[i];
        if (completionMap[key]) {
            completionMap[key]--;
            if (completionMap[key] < 0) {
                answer = key;
                break;
            }
        }
        else {
            answer = key;
            break;
        }
    }
    return answer;
}

class Animal {
    constructor(name) {
        this.speed = 0;
        this.name = name;
    }

    run = (speed) => {
        this.speed = speed;
        alert(`${this.name}가 속도 ${this.speed}로 달립니다.`);
    }

    stop() {
        this.speed = 0;
        alert(`${this.name}가 멈췄습니다.`);
    }

}

class Rabbit extends Animal {
    hide() {
        alert(`${this.name}가 숨었습니다!`);
    }

    stop() {
        super.stop(); // 부모 클래스의 stop을 호출해 멈추고,
        this.hide(); // 숨습니다.
    }
}

let rabbit = new Rabbit("흰 토끼");

rabbit.run(5); // 흰 토끼가 속도 5로 달립니다.
rabbit.stop(); // 흰 토끼가 멈췄습니다. 흰 토끼가 숨었습니다!


//   아래 코드에서 Rabbit은 Animal을 상속받습니다.

// 그런데 Rabbit 객체를 만들 수가 없습니다. 무엇이 잘못된 것일까요? 코드를 수정해보세요.

class Animal {

    constructor(name) {
        this.name = name;
    }

}

class Rabbit extends Animal {
    constructor(name) {
        this.name = name;
        this.created = Date.now();
    }
}

let rabbit = new Rabbit("White Rabbit"); // Error: this is not defined
alert(rabbit.name);


class Animal {

    constructor(name) {
        this.name = name;
    }

}
class Rabbit extends Animal {
    constructor(name) {
        super(name);
        this.created = Date.now();
    }
}

// extends 로 선언한 클래스의 생성자 함수를 호출해주지 않으면 this가 없음
// 생성자 오버라이딩을 안해주면 자동으로 super 생성자를 호출해주지만 커스텀에선 super객체를 명시적으로 해줘야 this 가 생김
// 하지만 
let rabbit = new Rabbit("White Rabbit");
alert(rabbit.name);


// 매 초마다 시간을 출력해주는 클래스 Clock이 있습니다.

class Clock {
    constructor({ template }) {
        this.template = template;
    }

    render() {
        let date = new Date();

        let hours = date.getHours();
        if (hours < 10) hours = '0' + hours;

        let mins = date.getMinutes();
        if (mins < 10) mins = '0' + mins;

        let secs = date.getSeconds();
        if (secs < 10) secs = '0' + secs;

        let output = this.template
            .replace('h', hours)
            .replace('m', mins)
            .replace('s', secs);

        console.log(output);
    }

    stop() {
        clearInterval(this.timer);
    }

    start() {
        this.render();
        this.timer = setInterval(() => this.render(), 1000);
    }
}
// Clock을 상속받는 ExtendedClock을 만들고, precision(정확도)이라는 매개변수도 추가해보세요. precision은 ‘초’ 사이의 간격을 의미하고, 기본값은 1000(1초)이 되어야 합니다.

// 새로운 파일(extended-clock.js)을 만들어 답을 작성해주세요.
// clock.js은 수정하면 안 됩니다. 상속을 사용하세요.

class ExtendedClock extends Clock {
    constructor({ template, precision = 1000 }) {
        super({ template });
        this.template = template;
        this.precision = precision;
    }
    start() {
        this.render();
        this.timer = setInterval(() => this.render(), this.precision);
    }
}

class CoffeeMachine {
    // ...

    constructor(power) {
        this._power = power;
    }

    get power() {
        return this._power;
    }

}

// 커피 머신 생성
let coffeeMachine = new CoffeeMachine(100);

alert(`전력량이 ${coffeeMachine.power}인 커피머신을 만듭니다.`); // 전력량이 100인 커피머신을 만듭니다.

coffeeMachine.power = 25; // Error (setter 없음)

let evMixin = {
    on(eventName, handler) {
        if (!this._handlers) this._handlers = {};
        if (!this._handlers[eventName]) {
            this._handlers[eventName] = [];
        }
        this._handlers[eventName].push(handler);
    },
    off(eventName, handler) {
        let handlers = this._handlers?.[eventName];
        if (!handlers) return;
        for (let i = 0; i < handlers.length; ++i) {
            if (handlers[i] === handler) {
                handlers.slice(i--, 1);
            }
        }
    },
    trigger(eventName, ...args) {
        let handlers = this._handlers?.[eventName];
        if (!handlers) return;
        handlers.forEach(handler => handler.call(this, ...args));
    }
}

class Menu {
    choose(val) {
        this.trigger("select", val);
    }
}
Object.assign(Menu.prototype, evMixin);

let menu = new Menu();
menu.on("select", val => console.log(val));
menu.choose("1222");


function delay(fn, ms) {
    return function (...args) {
        setTimeout(() => fn.call(this, ...args), ms);
    }
}
function f(x) {
    alert(x);
}

// create wrappers
let f1000 = delay(f, 1000);
let f1500 = delay(f, 1500);

f1000("test"); // shows "test" after 1000ms
f1500("test"); // shows "test" after 1500ms

function debounce(func, ms) {
    let timeout;
    return function () {
        clearTimeout(timeout);
        timeout = setTimeout(() => func.apply(this, arguments), ms);
    };
}


function throttle(func, ms) {
    let lastArgs, isThrottled = false;
    function wrapper() {
        if (isThrottled) {
            lastArgs = arguments;
            return;
        }
        isThrottled = true;
        func.apply(this, arguments);
        setTimeout(() => {
            isThrottled = false;
            if (lastArgs) {
                wrapper.apply(this, lastArgs);
                lastArgs = null;
            }
        }, ms);
    };
    return wrapper;
}



function f(a) {
    console.log(a);
}

// f1000 passes calls to f at maximum once per 1000 ms
let f1000 = throttle(f, 1000);

f1000(1); // shows 1
f1000(2); // (throttling, 1000ms not out yet)
f1000(3); // (throttling, 1000ms not out yet)


/*

내장된 SyntaxError 클래스를 상속하는 FormatError 클래스를 만들어 봅시다.

만들어진 클래스에서 message, name, stack를 참조할 수 있어야 합니다.

참고 예시입니다.

*/
class FormatError extends SyntaxError {
    constructor(message) {
        super(message);
        this.name = this.constructor.name;
    }
}

let err = new FormatError("formatting error");

alert(err.message); // formatting error
alert(err.name); // FormatError
alert(err.stack); // stack

alert(err instanceof FormatError); // true
alert(err instanceof SyntaxError); // true (SyntaxError 클래스를 상속받았기 때문입니다.)


function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

delay(3000).then(() => alert('3초후 실행'));

function loadScript(src) {
    return new Promise(function (resolve, reject) {
        let script = document.createElement('script');
        script.src = src;

        script.onload = () => resolve(script);
        script.onerror = () => reject(new Error(`${src}를 불러오는 도중에 에러가 발생함`));

        document.head.append(script);
    });
}

loadScript("/article/promise-chaining/one.js")
    .then(script => loadScript("/article/promise-chaining/two.js"))
    .then(script => loadScript("/article/promise-chaining/three.js"))
    .then(script => {
        // 스크립트를 정상적으로 불러왔기 때문에 스크립트 내의 함수를 호출할 수 있습니다.
        one();
        two();
        three();
    });


Promise.allSettled = function (promises) {
    return Promise.all(promises.map(p => Promise.resolve(p).then(value => (
        {
            status: "fulfilled",
            value
        }), reason => ({
            status: "rejected",
            reason
        })
    )));
}


async function loadJson(url) {
    let response = await fetch(url);
    if (response.status == 200) {
        return response.json();
    } else {
        throw new Error(response.status);
    }
}

loadJson('no-such-user.json')
    .catch(alert); // Error: 404


/*
async와 await를 사용해서 '다시 던지기' 예시 재작성하기
프라미스 체이닝 챕터에서 다뤘던 ‘다시 던지기(rethrow)’ 관련 예시를 기억하실 겁니다. 이 예시를 .then/catch 대신 async/await를 사용해 다시 작성해 봅시다.

그리고 demoGithubUser 안의 반복(recursion)은 반복문(loop)을 사용해 작성하도록 합시다. async/await를 사용하면 쉽게 작성할 수 있습니다.
*/
// 유효한 사용자를 찾을 때까지 반복해서 username을 물어봄
class HttpError extends Error {
    constructor(response) {
        super(`${response.status} for ${response.url}`);
        this.name = 'HttpError';
        this.response = response;
    }
}

async function loadJson(url) {
    let response = await fetch(url);
    if (response.status == 200) {
        return response.json();
    } else {
        throw new Error(response.status);
    }
}
async function demoGithubUser() {
    while (true) {
        try {
            let name = prompt("GitHub username을 입력하세요.", "iliakan");
            let user = await loadJson(`https://api.github.com/users/${name}`);
            alert(`이름: ${user.name}.`);
            return user;
        } catch (err) {
            if (err instanceof HttpError && err.response.status == 404) {
                alert("일치하는 사용자가 없습니다. 다시 입력해 주세요.");
            } else {
                throw err;
            }
        }
    }
}

demoGithubUser();

async function wait() {
    await new Promise(resolve => setTimeout(resolve, 1000));

    return 10;
}

function f() {
    // shows 10 after 1 second
    wait().then(result => alert(result));
}

f();



let repo = 'javascript-tutorial/en.javascript.info'; // 커밋 정보를 얻어올 GitHub 리포지토리

async function* fetchCommits(repo) {
    let url = `https://api.github.com/repos/${repo}/commits`;
    while (url) {
        const response = await fetch(url, {
            headers: { 'User-Agent': 'Our script' }
        });
        const body = await response.json();
        let nextPage = response.headers.get("Link").match(/<(.*?)>; rel="next"/);
        nextPage = nextPage?.[1];

        url = nextPage;
        for (let commit of body) {
            yield commit
        }
    }
}


(async () => {

    let count = 0;

    for await (const commit of fetchCommits('javascript-tutorial/en.javascript.info')) {

        console.log(commit.author.login);

        if (++count == 10) { // 100번째 커밋에서 멈춥니다.
            break;
        }
    }

})();