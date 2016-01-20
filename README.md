# arduino-interpreter
A fully <em> customizable </em> Arduino or ESP8266 Command Interpreter that uses function syntax you're already familiar with!
It can be used to human readable communication between devices. Simply give a command like you would do when coding. See:

*** The leading > is mandatory, without it, you may send any kind of nonsense through the serial port and it won't lead to misbehaviour

>car.turn(90)
>house.room.computer(off)
>stop()
>lcd.show(Hello world)
>print(Thomas,John,Peter)

Just put your code inside the interpret() function.
I've also included a forwardable text feature. To use it, put your text within brackets.

"Good afternoon, Sir!"

Interpreter comes with examples and lots of comments to help you. Try opening Arduino Serial Monitor and typing ">math.sum(182,233)" or ">friends(Batman,Iron Man)".

Yeah, simple like that.
Yeah, it's fast, isn't it?
