# Fasterpreter
###Fast and Simple Command Interpreter 

######This is an Arduino or ESP8266 Command Interpreter that uses C-like function syntax.
######It can be used to create human readable communication between devices. Simply give a command like you would do when coding:

`>car.turn(90)`
`>rgb(124,255,0)`
`>house.room.computer(off)`
`>stop()`
`>lcd.show(Hello world)`
`>print(Thomas,John,Peter)`

The leading **>** is mandatory for commands.You can keep any debug messages you have in your code, they won't break stuff.
It is not necessary, but recommended that you include a *newline*('\n') in the end (if you are using Arduino Serial Monitor, just choose *Newline* instead of *No line ending*):


####How it Works

Just put your code inside the `interpret()` function.
There's also a forwardable text** feature. To use it, put your text within quotes:

`"Good afternoon, Sir!"`

Fasterpreter comes with examples in the code and comments to help you. Try opening Arduino Serial Monitor, and typing `>math.sum(182,233)` or `>versus(Batman,Superman)`

Go ahead and try it!

