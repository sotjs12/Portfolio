

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