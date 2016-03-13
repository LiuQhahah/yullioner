int IA=3;
int IB=4;
void setup(){
    Serial.begin(9600);
    pinMode(IA,OUTPUT);
    pinMode(IB,OUTPUT);
    analogWrite(IA,0);
    digitalWrite(IB,0);

}
    char a[10]; 
    int loc=0;
void loop(){
    while((loc=Serial.available())==0);
    Serial.readBytes(a,10);
    Serial.print("UNO got ");
    Serial.println(a);
    if(a[0]=='3'){
     Serial.print(a[0]);
     Serial.println("==>HIGH");
     analogWrite(IA,255);
     digitalWrite(IB,0);
   }else if(a[0]=='2'){
     Serial.print(a[0]);
     Serial.println("==>MID");
     analogWrite(IA,160);
     digitalWrite(IB,0);
   }else if(a[0]=='1'){
     Serial.print(a[0]);
     Serial.println("==>LOW");
     analogWrite(IA,80);
     digitalWrite(IB,0);
   }else{
     Serial.print(a[0]);
     Serial.println("==>OFF");
     analogWrite(IA,0);
     digitalWrite(IB,0);
   }

   
   a[loc]='\0';
}
