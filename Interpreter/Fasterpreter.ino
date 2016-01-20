
// Variables used by the Interpreter

const int dirFields=2;  // Set your number of dirs here
const int argFields=3;  //Set your number of args here
String dir[dirFields];
String strArg[argFields];
int intArg[argFields];
// Use the following if you want to check for args, commands or forwardables
bool hasArgs=false;
bool gotCmd=false;
bool gotFwd = false;

String forwardable;

// Just a small name convention
 #define serialPort Serial

// This is optional, just for debugging
void  printData(){
        if(gotCmd) {
                for(int i=0; i<dirFields; i++) {
                        serialPort.print("printing dir");
                        serialPort.print(i);
                        serialPort.print(":");
                        serialPort.print(dir[i]);
                        serialPort.println();
                }
                for(int i=0; i<argFields; i++) {
                        serialPort.print("printing arg");
                        serialPort.print(i);
                        serialPort.print(":");
                        serialPort.print(intArg[i]);
                        serialPort.print(" and ");
                        serialPort.print(strArg[i]);
                        serialPort.println();
                }
        }

        if(gotFwd) {
                serialPort.println(forwardable);
        }

}

void  parseArgs(String rawTxt){
        // parses the function arguments. E.g.:(100,10,-25)
        String tmp;
        int old_commaIndex =-1;
        bool oneMore = true;
        for(int i=0; i<argFields; i++) {
                int commaIndex = rawTxt.indexOf(',',old_commaIndex+1);
                if(commaIndex!=-1) {
                        tmp= rawTxt.substring(old_commaIndex+1,commaIndex);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-') strArg[i] = tmp;
                        else intArg[i] = tmp.toInt();

                        old_commaIndex = commaIndex;
                }
                else if(oneMore) {
                        oneMore=false;
                        tmp = rawTxt.substring(old_commaIndex+1);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-'){
                          /*
                           // removes the last ')', using length()-1 because the index starts at 0
                          tmp.remove(tmp.length()-1);
                          */
                          strArg[i] = tmp;
                        }
                        else intArg[i] = tmp.toInt();

                }
        }

}
void cleanInterpreter(){
        gotFwd=false;
        gotCmd=false;
        forwardable="";
        //mqttCmd ="";
        for(int i=0; i<argFields; i++) {
                intArg[i]=0;
                strArg[i]="";
        }
}

void  parseDirs(String fullTxt){
        //Eg.: >car.go(100,100,20)
        //>car.turn(10)
        //display.show(lalalal)
        //Obs.: fullTxt must already be without '>', use '>' to detect a command in the desired data stream before calling this.
        gotCmd=true;
        int argStartIndex =  fullTxt.indexOf('(');
        int argEndIndex = fullTxt.indexOf(')');
        String rawTxt = fullTxt.substring(0,argStartIndex);

        int old_dotIndex =-1;
        bool oneMore = true;
        for(int i=0; i<dirFields; i++) {
                int dotIndex = rawTxt.indexOf('.',old_dotIndex+1);
                if(dotIndex!=-1) {
                        dir[i] = rawTxt.substring(old_dotIndex+1,dotIndex);
                        old_dotIndex = dotIndex;
                }
                else if(oneMore) {
                        dir[i] = rawTxt.substring(old_dotIndex+1);
                        oneMore =false;
                }
                else dir[i] = "";

        }

        // if there are no arguments, just skip to Interpreter. E.g.: led.red()
        if(argStartIndex+1==argEndIndex) {
                hasArgs=false;
                interpret();
        }
        else {
                String justArgs = fullTxt.substring(argStartIndex+1,argEndIndex);
                hasArgs=true;
                parseArgs(justArgs);
                interpret();
        }
}

void interpret(){
// Uncomment the line below to print every dir and arg. Useful for debugging or understanding this code
//printData();

if(dir[0]=="wifi"){
  if(dir[1]=="led"){
    serialPort.println("command is: wifi.led");

  
 }
}

// try >math.sum(1,2);
else if(dir[0]=="math"){

  if(dir[1]=="sum"){

    String tmp = "Result is:";
    int a = intArg[0];
    int b = intArg[1];
    tmp += a+b;
    serialPort.println(tmp);
  }

}
// try >friends(Batman,Iron Man)
else if(dir[0]=="friends"){
String tmp = "Wow, ";
tmp+= strArg[0]; tmp+= " and"; tmp+=strArg[1];
tmp+=  " are friends now!";
serialPort.println(tmp);

}


// Don't remove this line
  cleanInterpreter();
}

void  readSerial(){
        if(serialPort.available()) {

                char c = serialPort.read();
                if(c=='>') {
                        String serialTxt = serialPort.readStringUntil(')');
                        serialTxt+=')';
                        //serialPort.println(serialTxt);
                        parseDirs(serialTxt);


                }
                else if (c=='\"') {
                        gotFwd=true;
                        forwardable= serialPort.readStringUntil('\"');
                        // use forwardable here
                }
        }
}

void setup(){
        serialPort.begin(115200);
        // You have to call this one time
        cleanInterpreter();

}

void loop(){
    // The only function you must call to run the interpreter
        readSerial();
}
