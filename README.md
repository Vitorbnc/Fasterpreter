# Fasterpreter
A <em> fully customizable </em> Arduino or ESP8266 Command Interpreter that uses function syntax you're already familiar with!
It can be used to human readable communication between devices. Simply give a command like you would do when coding. See:

*** The leading > is mandatory, without it, you may send any kind of nonsense through the serial port and it won't lead to misbehaviour
<br>
<p> >car.turn(90) </p>
<p> >house.room.computer(off) </p>
<p> >stop() </p>
<p> >lcd.show(Hello world) </p>
<p> >print(Thomas,John,Peter) </p>
<br>
Just put your code inside the <em> interpret() </em> function.<br>
I've also included a </em> forwardable text </em>feature. To use it, put your text within brackets:
<br>
"Good afternoon, Sir!"
<br>
Fasterpreter comes with examples and lots of comments to help you. Try opening Arduino Serial Monitor and typing <em>>math.sum(182,233)</em> or <em>>friends(Batman,Iron Man)</em>.
<br>
<br>
Yeah, simple like that.<br>
Yeah, it's fast, isn't it?
