int ledPin=A0;
void setup(){
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
}
char a[10]; 
int loc=0;
void loop(){
  //Serial.println("Hello!");
  while((loc=Serial.available())==0);
  
        Serial.readBytes(a,10);
   
   Serial.print("UNO got ");
   Serial.println(a);
   if(a[0]=='1'){
     Serial.print(a[0]);
     Serial.println("==>HIGH");
   digitalWrite(ledPin,HIGH);
   }
   else{
      Serial.print(a[0]);
       Serial.println("==>LOW");
     digitalWrite(ledPin,LOW);
   }
   
   a[loc]='\0';
}

