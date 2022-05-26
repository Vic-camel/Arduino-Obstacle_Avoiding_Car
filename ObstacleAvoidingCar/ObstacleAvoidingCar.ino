#define TRIGPIN1 A3
#define ECHOPIN1 A2

#define TRIGPIN2 12
#define ECHOPIN2 13

#define TRIGPIN3 A0
#define ECHOPIN3 A1

//on_off
const byte interruptPin = 2;
int state = 0;
bool flag =false;
unsigned long lastMillis = 0;

void intFunc(){
  unsigned long newMillis = millis();
  if(newMillis - lastMillis >200){
     flag = true;
     if(state>=1){
        state=0; 
     }
     else{
        state=state+1;
     }
     lastMillis=newMillis;    
  }
}

//motor
int M1a=6,M1b=7; // 這組用來控制第一顆馬達正反轉
int ENa=5; //第一顆馬達的速度
int M2a=9,M2b=8; // 這組用來控制第 2 顆馬達
int ENb=10; //第二顆馬達的速度

void forward(){
    digitalWrite(M1a,HIGH);
    digitalWrite(M1b, LOW);
    analogWrite(ENa, 121); // 左馬達
    delay(20);

    digitalWrite(M2a,LOW);
    digitalWrite(M2b,HIGH);
    analogWrite(ENb,101); // 右馬達
    delay(20);  
}

void back(){
    digitalWrite(M1a,LOW);
    digitalWrite(M1b, HIGH);
    analogWrite(ENa, 100); // 左馬達

    digitalWrite(M2a,HIGH);
    digitalWrite(M2b,LOW);
    analogWrite(ENb,81); // 右馬達
    delay(150);  
}

void stopgoing(){

    digitalWrite(M1a,HIGH);
    digitalWrite(M1b, LOW);
    analogWrite(ENa, 0); // 左馬達
    //delay(500);

    digitalWrite(M2a,LOW);
    digitalWrite(M2b,HIGH);
    analogWrite(ENb,0); // 右馬達
    delay(130);    
}

void left(){

    digitalWrite(M2a,LOW);
    digitalWrite(M2b,HIGH);
    analogWrite(ENb,141); // 右馬達 因為右馬力小20
    delay(30);
    
    digitalWrite(M1a,LOW);
    digitalWrite(M1b, HIGH);
    analogWrite(ENa, 121); // 左馬達
   // delay(100);

}

void right(){

    digitalWrite(M1a,HIGH);
    digitalWrite(M1b, LOW);
    analogWrite(ENa, 161); // 左馬達
    delay(100);
    
    digitalWrite(M2a,HIGH);
    digitalWrite(M2b,LOW);
    analogWrite(ENb,141); // 右馬達

}

void backleft(){
    digitalWrite(M2a,LOW);
    digitalWrite(M2b,HIGH);
    analogWrite(ENb,119); // 右馬達
    delay(100);
    
    digitalWrite(M1a,LOW);
    digitalWrite(M1b, HIGH);
    analogWrite(ENa, 99); // 左馬達
   // delay(100);
}

//1-->middle;   2-->right；   3-->left
// HC-SR04
float ping1(){
    digitalWrite(TRIGPIN1,LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN1,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN1,LOW);
    return pulseIn(ECHOPIN1,HIGH)*0.017;    

}

float ping2(){
    digitalWrite(TRIGPIN2,LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN2,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN2,LOW);
    return pulseIn(ECHOPIN2,HIGH)*0.017;    

}

float ping3(){
    digitalWrite(TRIGPIN3,LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN3,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN3,LOW);
    return pulseIn(ECHOPIN3,HIGH)*0.017;    

}


void setup()
{
   //motor
   pinMode(M1a,OUTPUT);
   pinMode(M1b,OUTPUT);
   pinMode(ENa,OUTPUT);
   pinMode(M2a,OUTPUT);
   pinMode(M2b,OUTPUT);
   pinMode(ENb,OUTPUT);
  
    //sensor
    Serial.begin(9600);
    pinMode(TRIGPIN1,OUTPUT);
    pinMode(TRIGPIN2,OUTPUT);
    pinMode(TRIGPIN3,OUTPUT);
    pinMode(ECHOPIN1,INPUT);
    pinMode(ECHOPIN2,INPUT);
    pinMode(ECHOPIN3,INPUT);


    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(0,intFunc,FALLING);
    Serial.begin(9600);


}
/*

       float MMM = ping1();
       float RRR = ping2();
       float LLL = ping3();
*/       
void loop()
{

    int distance=20;
    int number=0;
    while(state){
       
       //sensor
       float MMM = ping1();
       float RRR = ping2();
       float LLL = ping3();
       Serial.print("LEFT MIDDLE RIGHT: ");
       Serial.print(LLL);
       Serial.print("   ");
       Serial.print(MMM);
       Serial.print("   ");
       Serial.print(RRR);
       Serial.print("   ");
       Serial.println(" cm");    
  
       //motor ( 0 means no object and 1 means object )
       //000 FORWARD 
       if(LLL>distance && MMM>distance && RRR>distance){
        
              forward();
              
            
       }
       
       //001 LEFT
       if(LLL>distance && MMM>distance && RRR<distance){


              while(1){
                if(LLL>distance && MMM>distance && MMM<distance){
                   stopgoing();
                   back(); 
                   left();
                   number=number+1;
                   Serial.print("   ");
                   Serial.println(number);
                }
                break;
              }  
                forward();
                delay(100);
                for(int a=number;a=0;a--){
                  stopgoing();
                  back(); 
                  right();
                  Serial.print("   ");
                  Serial.println(number);
                }
                break;
                
            
       }


       //010 LEFT
       if(LLL>distance && MMM<=distance && RRR>distance){
        
              stopgoing();
              back(); 
              left();
      
       }

       //011 LEFT
       if(LLL>distance && MMM<=distance && RRR<=distance){
        
              stopgoing();
              back(); 
              left();
            
       }

       //100 RIGHT
       if(LLL<=distance && MMM>distance && RRR>distance){
        
              stopgoing();
              back(); 
              right();
            
       }

       //101 FORWARD
       if(LLL<=distance && MMM>distance && RRR<=distance){
        
              forward();
              
            
       }

       //110 RIGHT
       if(LLL<=distance && MMM<=distance && RRR>distance){
        
              stopgoing();
              back(); 
              right();
            
       }

       //111 back+left
       if(LLL<distance && MMM<=distance && RRR<=distance){
         
              back();          
              backleft();
            
       }

       if(state==0)break;
    }

    digitalWrite(M1a,LOW);
    digitalWrite(M1b,LOW);
    digitalWrite(ENa,LOW);
    digitalWrite(M2a,LOW);
    digitalWrite(M2b,LOW);
    digitalWrite(ENb,LOW);

    
}
