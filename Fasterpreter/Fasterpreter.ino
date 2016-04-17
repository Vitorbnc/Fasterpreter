#define uart Serial




class Fasterpreter {

protected:
const static int dirCount=2;  // Set your number of dirs here
const static int argCount=3;  //Set your number of args here

public:

String dir[dirCount];
String strArg[argCount];
int intArg[argCount];
bool hasStrArg[argCount];
bool hasIntArg[argCount];
// Use the following if you want to check for args, commands or forwardables
bool hasArgs=false;
bool gotCmd=false;
bool gotFwd = false;
bool shouldPrintData = false;
String forwardable;
String cmd;


// constructor here
Fasterpreter(){
        cleanInterpreter();
}


void readStream(HardwareSerial* inStream){
        if(inStream->available()) {
                // inStream->read(); is equivalent to *inStream.read()  ------ reads "value pointed to by inStream", it gets the value pointed by the pointer, not its address
                char c = inStream->read();
                if(c=='>') {
                        String serialTxt = inStream->readStringUntil(')');
                        serialTxt+=')';
                        //uart.println(serialTxt);
                        parse(serialTxt);

                }
                // if you don't want forwardables feature, just comment the lines below
                /*
                   else if (c=='\"') {
                        gotFwd=true;
                        forwardable= inStream->readStringUntil('\"');
                        // use forwardable here
                   }
                 */
        }
}

void printData(){
        for(int i=0; i<dirCount; i++) {
                uart.print("dir "); uart.print(i); uart.print(":");
                uart.println(dir[i]);
        }
        for(int i=0; i<argCount; i++) {
                if(hasStrArg[i]) {
                        uart.print("strArg "); uart.print(i); uart.print(":");
                        uart.println(strArg[i]);
                }
                else {
                        uart.print("Has no strArg "); uart.print(i);
                }
                if(hasIntArg[i]) {
                        uart.print("intArg "); uart.print(i); uart.print(":");
                        uart.println(intArg[i]);
                }
                else{
                        uart.print("Has no intArg "); uart.print(i);
                }
        }
}


void cleanInterpreter(){
        gotFwd=false;
        gotCmd=false;
        //forwardable="";
        /* // clean dirs only if necessary
           for(int i=0;i<dirCount;i++){
           dir[i]="";
           }
         */
        for(int i=0; i<argCount; i++) {
                //intArg[i]=0;
                //strArg[i]=""; // clean String Arguments only if necessary
                hasStrArg[i]=false;
                hasIntArg[i]=false;
        }
}


void  parseArgs(String rawTxt){
        // parses the function arguments. E.g.:(100,10,-25)
        String tmp;
        int old_commaIndex =-1;
        bool oneMore = true;
        for(int i=0; i<argCount; i++) {
                int commaIndex = rawTxt.indexOf(',',old_commaIndex+1);
                if(commaIndex!=-1) {
                        tmp= rawTxt.substring(old_commaIndex+1,commaIndex);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-'&& c!='+') {
                                strArg[i] = tmp;
                                hasStrArg[i] = true;
                        }
                        else {
                                intArg[i] = tmp.toInt();
                                hasIntArg[i] = true;
                        }

                        old_commaIndex = commaIndex;
                }
                else if(oneMore) {
                        oneMore=false;
                        tmp = rawTxt.substring(old_commaIndex+1);
                        char c =  tmp.charAt(0);
                        if(!isDigit(c)&& c!='-'&& c!='+') {
                                /*
                                   // removes the last ')', using length()-1 because the index starts at 0
                                   tmp.remove(tmp.length()-1);
                                 */
                                hasStrArg[i] = true;
                                strArg[i] = tmp;
                        }
                        else {
                                intArg[i] = tmp.toInt();
                                hasIntArg[i] = true;
                        }

                }
        }

}


void  parse(String fullTxt){
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
        for(int i=0; i<dirCount; i++) {
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


// This has to be defined later
void interpret();

};
//----------------- end of Fasterpreter class

// Instantiating the class here
Fasterpreter interpreter;


void setup() {
        uart.begin(115200);
        delay(10);

}

void loop() {

        // This method requires the address of (& operator) a HardwareSerial object. E.g: &Serial or &Serial1
        // You can also read data in another function and call interpreter.parse(Input_String_without_>_)
        interpreter.readStream(&uart);


}

//-------------------------------------- Definition of interpret method here-------------------------------------------
void Fasterpreter::interpret(){
// Useful for debugging or understanding this code
        if(shouldPrintData) printData();

// Using strcmp instead of String1==String2 because the first method is faster
        if(strcmp(dir[0].c_str(),"wifi")==0) {
                if(strcmp(dir[1].c_str(),"led")==0) {
                        uart.println("command is: wifi.led");

                }
        }

        else if(strcmp(dir[0].c_str(),"math")==0) {
                if(strcmp(dir[1].c_str(),"sum")==0) {
                        uart.print("Result is ");
                        uart.println(intArg[0]+intArg[1]);
                }
        }

// try >friends(Batman,Superman)
// Using strncmp to compare just n chars, it should be faster for bigger words
        else if(strncmp(dir[0].c_str(),"friends",4)==0) {
                String tmp = "Wow, ";
                tmp+= strArg[0]; tmp+= " and"; tmp+=strArg[1];
                tmp+=  " are friends now!";
                uart.println(tmp);

        }



// Don't remove this line
        cleanInterpreter();
}
