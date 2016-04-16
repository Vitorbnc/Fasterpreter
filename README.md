# Fasterpreter
###Your Robot's Fast and Simple Command Interpreter 
A **fully customizable** Arduino or ESP8266 Command Interpreter that **uses function syntax** you're already familiar with!
It can be used to **human readable communication** between devices. Simply give a command like you would do when coding. See:

The leading **>** is mandatory, without it, your commands won't do anything. This means you can keep any debug messages you have in your code.
<br>
`>car.turn(90)`
`>house.room.computer(off)`
`>stop()`
`>lcd.show(Hello world)`
`>print(Thomas,John,Peter)`

Just put your code inside the `interpret()` function.
I've also included a **forwardable text** feature. To use it, put your text within quotes:
<br>
*"Good afternoon, Sir!"*
<br>
**Fasterpreter** comes with examples in the code and lots of comments to help you. Try opening Arduino Serial Monitor and typing <em>>math.sum(182,233)</em> or <em>>friends(Batman,Iron Man)</em>.
<br>
<br>
Yeah, fast simple like that.<br>

