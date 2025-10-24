// logMessage("Hello from the Embedded V8!");
// logMessage(`2 + 2 is ${2 + 2}`);
console.log(`2 + 2 is ${2 + 2}`);
// `2 + 2 is ${2 + 2}`;
// logMessage(`process.arch = ${process.arch}`);
logMessage(`Date() = ${Date()}`);
// a JavaScript object...:
var myObj = { name: "John", age: 31, city: "New York" };

// ...converted into JSON:
var myJSON = JSON.stringify(myObj);
logMessage(`myJSON using JSON.stringify : ${myJSON}`);
