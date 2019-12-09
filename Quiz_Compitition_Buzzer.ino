////////////////////////W.M.G.C.Weerasihge////////////////////////
////////////////////////////2019-02-12////////////////////////////
/////////////////Inter University Quiz Compitition////////////////
/////////////////////////Arduino Pro-mini/////////////////////////

#define buzzer_Pin 3
#define right_Led_Pin 4
#define left_Led_Pin 5
#define wait_Led_Pin 6

#define left_Button A0
#define right_Button A1
#define wait_Button A2

int button_Value=1;
byte start=0;

int left_Value, right_Value, wait_Value;
long startTime1=millis(),startTime2=millis(), startTime3=millis(), resetCount=millis();
int buzzer_Delay=1000;
int wait_Time=30000;

void setup() {

    pinMode(buzzer_Pin,OUTPUT);
    pinMode(right_Led_Pin,OUTPUT);
    pinMode(left_Led_Pin,OUTPUT);
    pinMode(wait_Led_Pin,OUTPUT);

    pinMode(left_Button,INPUT);
    pinMode(right_Button,INPUT);
    pinMode(wait_Button,INPUT);
    //Serial.begin(9600);
}

void loop() {

  get_Button_Values();

    if(start==2 && wait_Value==button_Value && left_Value!=button_Value && right_Value!=button_Value){
        digitalWrite(left_Led_Pin,LOW);
        digitalWrite(right_Led_Pin,LOW);
        digitalWrite(buzzer_Pin,LOW);
            for(byte x=0; x<5; x++){
                digitalWrite(wait_Led_Pin,HIGH);
                delay(200);
                digitalWrite(wait_Led_Pin,LOW);
                delay(100);  
            }
        digitalWrite(wait_Led_Pin,LOW);
            start=0;
            delay(1000);
            wait_Value=0;
    }
    
    if(start==0 &&  wait_Value==button_Value && left_Value!=button_Value && left_Value!=button_Value){ 
        startTime1=millis();
        startTime2=millis();
        startTime3=millis();
        resetCount=millis();
        
        digitalWrite(wait_Led_Pin,HIGH);
        delay(400);
        digitalWrite(wait_Led_Pin,LOW);
        delay(100);
            wait_Value=0;
            start=1; 
    }

    if(start==1 && millis()-startTime1>1000 && wait_Value!=button_Value && left_Value!=button_Value && left_Value!=button_Value){
        startTime1=millis();
        digitalWrite(wait_Led_Pin,!digitalRead(wait_Led_Pin));     
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(start==1 &&  millis()-resetCount<(wait_Time+500) && wait_Value==button_Value && left_Value!=button_Value && left_Value!=button_Value){ 
        resetCount=millis();
        digitalWrite(wait_Led_Pin,HIGH);
            start=2; 
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
    if(start==1 && millis()-startTime2>(wait_Time+500) && wait_Value!=button_Value && left_Value!=button_Value && left_Value!=button_Value){
        startTime2=millis();
        digitalWrite(wait_Led_Pin,LOW); 
        digitalWrite(wait_Led_Pin,HIGH);
            start=2;     
    }
    
    if(start==1 && millis()-startTime3<(wait_Time+500) && wait_Value!=button_Value && left_Value==button_Value && right_Value!=button_Value){
        startTime3=millis();                   //30000ms =14s
        digitalWrite(wait_Led_Pin,LOW);
        digitalWrite(left_Led_Pin,HIGH);
        digitalWrite(buzzer_Pin,HIGH);
        delay(buzzer_Delay);
        digitalWrite(buzzer_Pin,LOW);
            start=2;  
    }
    
    if(start==1 && millis()-startTime3<(wait_Time+500) && wait_Value!=button_Value && left_Value!=button_Value && right_Value==button_Value){
        startTime3=millis();
        digitalWrite(wait_Led_Pin,LOW);
        digitalWrite(right_Led_Pin,HIGH);
        digitalWrite(buzzer_Pin,HIGH);
        delay(buzzer_Delay);
        digitalWrite(buzzer_Pin,LOW);
            start=2;  
    }   
}

void get_Button_Values(){
  left_Value=digitalRead(left_Button);
  wait_Value=digitalRead(wait_Button);
  right_Value=digitalRead(right_Button);
}


