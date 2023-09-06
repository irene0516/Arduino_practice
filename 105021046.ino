int bluepin = 9; //select the pin for the red LED   
int greenpin =10; // select the pin for the blue LED   
int redpin =11;
int INA = 8;
int readPin=1;
int INB = 7;
const byte trigPin=5; //Output pin to trigger ultra sound
const byte echoPin=6; //Input pin to receive echo pulse
int readval=0;
int mapVal=0;
long previousTime=0;
long previousTime2=0;
long interval=50;
int i=50;
boolean boo=true;
boolean boo2=true;
boolean boo3=true;
boolean boo4=true;
void setup()

{
 pinMode(trigPin, OUTPUT); //Arduino pin default input
 Serial.begin(9600); 
 pinMode(redpin, OUTPUT);   
 pinMode(bluepin, OUTPUT);   
 pinMode(greenpin, OUTPUT);   
 
 }
void loop()
{
  
  

     
fan();
  
 



}
unsigned long ping() { //send 10us pulse to HC-SR04 trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  //sustain at least 10us HIGH pulse
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
  }
  void fan(){
    unsigned long currentTime2 = millis();
    readval=analogRead(readPin);
    mapVal=map(readval,0,1023,120,230);
    unsigned long d=ping()/58; //calculate distance
    //Serial.print(d);
    //Serial.println("cm");
    if(d<=40 and mapVal<=190){
       led();
      if(currentTime2 - previousTime2 > 3000 and boo4){
      
        //Serial.println(mapVal);
        analogWrite(INA,0);
        analogWrite(INB,mapVal);
        boo4=false;
        previousTime2 = currentTime2;
        }else if(currentTime2 - previousTime2 > 2000 and boo4==false){
        //Serial.println(currentTime2 - previousTime2 );
        //Serial.println(mapVal);
        analogWrite(INA,0);
        analogWrite(INB,0);
        boo4=true;
        previousTime2 = currentTime2;
        }
       
        }else if(d<=20 and mapVal>190){
          led();
          analogWrite(INA,0);
          analogWrite(INB,mapVal);
        
          }else{
            analogWrite(INA,0);
            analogWrite(INB,0);
            analogWrite(bluepin,0);  
            analogWrite(redpin,0); 
            analogWrite(greenpin,0); 
          }
          }
 void led(){
  unsigned long currentTime = millis();

  //Serial.println(currentTime);

  if(currentTime - previousTime > interval){
    if(i<=150 and boo){
      i=i+1;
      analogWrite(bluepin,150-i+50);  
    analogWrite(redpin,i-50); 
    if(i==151){
      analogWrite(bluepin,0);
      boo=false;
      boo2=false;
      i=100;
      }
      }else if(i<=160 and boo2==false){
        i=i+1;
        analogWrite(greenpin,i);
        if(i==161){
          analogWrite(redpin,0);
          i=50;
          boo3=false;
          boo2=true;
        }
        }else if(i<=150 and boo3==false){
           i=i+1;
            analogWrite(greenpin,150-i+50);
             analogWrite(bluepin,i-50);
              if(i==151){
          i=50;
          boo=true;
          boo3=true;
          
        }
          }
    
        
   previousTime = currentTime;   
   
}
}
