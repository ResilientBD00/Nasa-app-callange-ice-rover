/* This code This code recives pid motor offset from 
//computer com ports and execute the values in the motors .. 
*/

#define echopin 9
#define lmotorf 4
#define lmotorb 5
#define rmotorf 7
#define rmotorb 6
#define en2 10
#define en1 11

String inString = "";    
int motorSpeed =0;
int M1=150,M2=150;
//int motorSpeed1=150;
//int motorSpeed2=150;

void motorForword(int e1,int e2)
{
  analogWrite(en1,e1);
  analogWrite(en2,e2);
  digitalWrite(lmotorf,1);
  digitalWrite(lmotorb,0);
  digitalWrite(rmotorf,1);
  digitalWrite(rmotorb,0);

}

void setup() {

  Serial.begin(9600);
  pinMode(en1,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(lmotorf,OUTPUT);
  pinMode(lmotorb,OUTPUT);
  pinMode(rmotorf,OUTPUT);
  pinMode(rmotorb,OUTPUT);

  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  delay(1000);
  digitalWrite(8,LOW);


}
int motorSpeed1=150;
int motorSpeed2=150;
int m1Speed;
int m2Speed;
void loop() { 

  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '*') {
      inString = "";
      motorForword(0,0);
      return ;
    }
    else if (inChar == '#') {
      Serial.println("int : ");
      Serial.println(inString.toInt());

      //motorSpeed1=motorSpeed1+inString.toInt();
      //motorSpeed2=motorSpeed2-inString.toInt();
      motorSpeed = inString.toInt();
      int j= inString.toInt();
      //Serial.println("ok");

      if(j==30)
      {
        digitalWrite(8,HIGH);
        Serial.println("ok");
        //delay(1000);

      }
      inString = "";
    }
    else if (inChar == '@') {
      Serial.println("int : ");
      Serial.println(inString.toInt());

      //motorSpeed1=motorSpeed1-inString.toInt();
      //motorSpeed2=motorSpeed2+inString.toInt();
      motorSpeed = inString.toInt();
      motorSpeed = -1*motorSpeed;
      int j= inString.toInt();
      //Serial.println("ok");

      if(j==30)
      {
        digitalWrite(8,HIGH);
        Serial.println("ok");
        //delay(1000);

      }
      inString = "";
    }
    if (inChar == '\n') {
      inString = "";
    }
    if((M1 + motorSpeed)>255){
    m1Speed = 255;
    m2Speed = M2 - motorSpeed - (M1+motorSpeed-255);
  }
  else if((M2 - motorSpeed)>255){
    m2Speed = 255;
    m1Speed = M1 + motorSpeed - (M2-motorSpeed-255);
  }
  else{
    m1Speed = M1 + motorSpeed;
    m2Speed = M2 - motorSpeed;
  }

  if (m1Speed < 0)
    m1Speed = 0;
  if (m2Speed < 0)
    m2Speed = 0;

  motorForword(m1Speed,m2Speed);
  }      
  
}

