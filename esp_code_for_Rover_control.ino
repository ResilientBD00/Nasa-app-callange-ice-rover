// This code implements controling the rover with esp 8266 in duplex mode. 
// It has also interface of rover arm control.. 



#include <SoftwareSerial.h>
 #include <Servo.h> 
 int s1,s2,s3,s4;

// Servo declaretion for hand.
 
Servo myservo1;  
 
Servo myservo2;
 
Servo myservo3;
 
Servo myservo4;

// Fixed position for hand to be fixed.

int pos1 = 180;    
int pos2 = 180;
int pos3 = 150;
int pos4 = 180;

#define DEBUG true

// pin declaretion for motors.
// #define trigpin 8
//#define echopin 9
#define lmotorf 4
#define lmotorb 5
#define rmotorf 7
#define rmotorb 6
#define en1 10
#define en2 11

//  esp wifi module configure pin declaretion.


#define esp_pin 13
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3

// functions for motor rotatio.
                            
void straight()
{
  digitalWrite(lmotorf,1);
  digitalWrite(lmotorb,0);
  digitalWrite(rmotorf,1);
  digitalWrite(rmotorb,0);
  
}
void motorForword(int e1,int e2)
{
  analogWrite(e1,255);
  analogWrite(e2,255);
  straight();
}
//void right()
//{
//  analogWrite(en1,255);
//  analogWrite(en2,255);
//  digitalWrite(lmotorf,0);
//  digitalWrite(lmotorb,1);
//  digitalWrite(rmotorf,1);
//  digitalWrite(rmotorb,0);
////motorForword(255,0);
//}
//void left()
//{
//  analogWrite(en1,255);
//  analogWrite(en2,255);
//  digitalWrite(lmotorf,0);
//  digitalWrite(lmotorb,1);
//  digitalWrite(rmotorf,1);
//  digitalWrite(rmotorb,0);
//  //motorForword(0,255);
//}
//void back()
//{
//  analogWrite(en1,255);
//  analogWrite(en2,255);
// 
//   digitalWrite(lmotorf,0);
//  digitalWrite(lmotorb,1);
//  digitalWrite(rmotorf,0);
//  digitalWrite(rmotorb,1);
//}
//void _stop()
//{
//   digitalWrite(lmotorf,1);
//  digitalWrite(lmotorb,1);
//  digitalWrite(rmotorf,1);
//  digitalWrite(rmotorb,1);
//}
void left()
{
  digitalWrite(lmotorf,0);
  digitalWrite(lmotorb,1);
  digitalWrite(rmotorf,1);
  digitalWrite(rmotorb,0);
}
void right()
{
  digitalWrite(lmotorf,1);
  digitalWrite(lmotorb,0);
  digitalWrite(rmotorf,0);
  digitalWrite(rmotorb,1);
}
void back()
{
   digitalWrite(lmotorf,0);
  digitalWrite(lmotorb,1);
  digitalWrite(rmotorf,0);
  digitalWrite(rmotorb,1);
}
void _stop()
{
   digitalWrite(lmotorf,1);
  digitalWrite(lmotorb,1);
  digitalWrite(rmotorf,1);
  digitalWrite(rmotorb,1);
}


// initialize fixed values.

void setup()
{
  Serial.begin(115200);
  esp8266.begin(115200); // your esp's baud rate might be different
  
//  pinMode(trigpin,OUTPUT);
//  pinMode(echopin,INPUT);

// comands for activate esp wifi module.
   
  sendCommand("AT+RST\r\n",2000,DEBUG); // reset module
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
  sendCommand("AT+CWJAP=\"Faisal@CSE2\",\"faisal35\"\r\n",3000,DEBUG);
  delay(10000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80

  // output pin declaretion. 

  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(lmotorf,OUTPUT);
  pinMode(lmotorb,OUTPUT);
  pinMode(rmotorf,OUTPUT);
  pinMode(rmotorb,OUTPUT);
  analogWrite(en1,255);
  analogWrite(en2,255);
  Serial.println("Server Ready");


  // servo pins declaretion
 myservo1.attach(7);  
  myservo2.attach(8);
  myservo3.attach(9);
  myservo4.attach(10);

  myservo1.write(pos1);  
  myservo2.write(pos2);  
  myservo3.write(pos3);  
  myservo4.write(pos4);  
  delay(500);
  
}
int incomingByte; 
//int ultra()
//{
//   float duration,distance;
//  digitalWrite(trigpin,HIGH);
//  delay(10);
//  digitalWrite(trigpin,LOW);
//  duration=pulseIn(echopin,HIGH);
//  distance=((duration/2)/30);
//  return distance;
//}


// connect and send signals. 

int connectionId=0;
void loop()
{
  String content;
//  int dis=ultra();
   if(esp8266.find("IPD,"))
    {
          
      connectionId = esp8266.read()-48;
  if (esp8266.available()>=0) {
   delay(10);
      while(esp8266.available())
      {
        incomingByte = esp8266.read();
      }
    
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'U') {
      motorForword(150,150);
      Serial.println("UP");
  
    }
    if (incomingByte == 'D') {
      back();
      Serial.println("DOWN");
    }
    if (incomingByte == 'L') {
      left();
      Serial.println("LEFT");
    }
    if (incomingByte == 'R') {
     right();
      Serial.println("RIGHT");
    }
    if (incomingByte == '1') {
     motorForword(255,255);
      Serial.println("1");
    }
    if (incomingByte == '2') {
      motorForword(100,100);
      Serial.println("2");
    }
    if (incomingByte == '3') {
     motorForword(0,255);
      Serial.println("3");
    }
    if (incomingByte == '4') {
     motorForword(255,0);
      Serial.println("4");
    }
    if (incomingByte == 'M') {

      Serial.println("M");
    }
    if (incomingByte == 'S')
    {
      _stop();
      Serial.println("S");
    }
if (incomingByte == 'P') {
  
s1 = myservo1.read();
if (s1<180)
{myservo1.write(s1+1);
delay (15);
}
      Serial.println("P");
    }
if (incomingByte == 'r') {
  
s1 = myservo1.read();
if (s1>0 &&  181>s1)
{myservo1.write(s1-1);
delay (15);
}
      Serial.println("r");
    }

    if (incomingByte == 'V') {
  
s2 = myservo2.read();
if (s2<180)
{myservo2.write(s2+1);
delay (15);
}
      Serial.println("V");
    }
if (incomingByte == 'a') {
  
s2 = myservo2.read();
if (s2>0 &&  181>s2)
{myservo2.write(s2-1);
delay (15);
}
      Serial.println("a");
    }

    if (incomingByte == 'c') {
  
s3 = myservo3.read();
if (s3<180)
{myservo3.write(s1+1);
delay (15);
}
      Serial.println("c");
    }
if (incomingByte == 'g') {
  
s3 = myservo3.read();
if (s3>0 &&  181>s3)
{myservo1.write(s3-1);
delay (15);
}
      Serial.println("g");
    }





    
   
  }
 
    }
//    if((dis>=1)&&(dis<=60))
//    {
//      content="v";
//    
//      sendHTTPResponse(connectionId,content);
//        Serial.println(dis);
//    }

}
 
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);
           
    esp8266.write(data,dataSize); // send the read character to the esp8266

    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
   
    
    return response;
}
 
/*
* Name: sendHTTPResponse
* Description: Function that sends HTTP 200, HTML UTF-8 response
*/
void sendHTTPResponse(int connectionId, String content)
{
     
     // build HTTP response
     String httpResponse;
     String httpHeader="";
     httpResponse =content+"\r\n"; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
     sendCIPData(connectionId,httpResponse);
}
 
/*
* Name: sendCIPDATA
* Description: sends a CIPSEND=<connectionId>,<data> command
*
*/
void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommand(cipSend,10,DEBUG);
   sendData(data,10,DEBUG);
}
 
/*
* Name: sendCommand
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
   
    
    return response;
}
 
