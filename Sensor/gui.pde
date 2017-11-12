import processing.serial.*;
Serial Port;
PrintWriter output;
String inString;
int lf = 10;

void setup(){
size(500,100);
Port = new Serial(this,Serial.list()[0],9600);
output = createWriter("log.txt");
Port.bufferUntil(lf);
}

void draw() {
    if(Port.available()>0)
    {
        if(inString !=null)
        {
          output.println(inString);
        }
    }
    background(0);
    text("received: " + inString,10,50);
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}
void serialEvent(Serial p)
{
    inString = p.readString();

}