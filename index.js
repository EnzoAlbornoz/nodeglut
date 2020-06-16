const lib = require("./build/Release/nodeglut.node")
console.log(lib)

lib.glutInit(process.argv.length, process.argv);
console.log(lib.glutCreateWindow("teste"));

setTimeout(() => lib.glutSetWindowTitle("glutNode"),2000);
setTimeout(() => lib.glutSetIconTitle("minimizedGlut"),5000);


setTimeout(() => process.exit(0),30000)
