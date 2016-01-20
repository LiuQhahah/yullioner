/****羽良工作室科技分享会 ****/
/**********小机械臂***********/
/******科技实践部_徐杰 *******/
/*工作邮箱  xujie@yullion.com*/
/******内部资料,谢绝外传******/
/*****************************/

#include"Servo.h"
#include"math.h"
#define A 102                                    //保证机械臂与目标在同一条直线上的舵机
#define D 17 
int B=45;                                    //  中下舵机,角度越小越下(45--90)
int C=120;                                  //  中上舵机,角度越小越下(30--120)                                   //  夹子
int j,k;
const float u=3.141592/180;
const int R=2.5/(cos(50*u)-cos(70*u)),r=1.2/(cos(39*u)-cos(59*u));
int angle(float x,float y);
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
void setup()
{  
   Serial.begin(9600);
   servo1.attach(5);
   servo2.attach(3);
   servo3.attach(11);
   servo4.attach(9);                      
   servo1.write(A);                            //保证机械臂与目标在同一条直线上的舵机初始值
   servo2.write(B);                            //中下舵机初始值
   servo3.write(C);                            //中上舵机初始值
   servo4.write(D);                            //夹子初始值
}
void loop()
{
    float a;
    char x,y,z;
    Serial.flush();
    Serial.print("enter x coordinate(cm) between 1 to 9");
    while(Serial.available()==0)
    {}
    x =(Serial.read());
    x-='0';
    x=map(x,1,9,-4,4);
    Serial.print(x,DEC);
    Serial.print("enter y coordinate(cm) between 4 to 9");
    while(Serial.available()==0) 
    {}
    y =(Serial.read()); 
    y-='0';
    Serial.print(y,DEC);
    Serial.print("enter z coordinate(cm)");
     while(Serial.available()==0)
    {}
    z =(Serial.read()); 
    z-='0';
    Serial.print(z,DEC);
    a=x/(y+4);                                                   //由于原点不同,因此y坐标要加一个距离. 
    if(a!=0)
      {
      if((a-(1.0/6.0)*pow(a,3))/u>0) 
        servo1.write(12+(180-(a-(1.0/6.0)*pow(a,3))*3.141592/180));            //三阶泰勒公式模拟反三角函数,底座舵机旋转
      else
        servo1.write(12-(a-(1.0/6.0)*pow(a,3))*3.141592/180);
      }
    else
      servo1.write(A); 
    angle(y,z);
    servo2.write(j);                            //中下舵机旋转.
    servo3.write(k);                            //中上舵机旋转.
    servo4.write(60);
    delay(150);
    servo4.write(D);
    delay(150);
}




int angle(float y,float z)
{
    for(j=45;j<90;j++)
   {
     for(k=30;k<120;k++)
    { 
     if(abs(R*(cos(k*u)-cos(C*u))+ r*(cos(j*u)-cos(B*u))-y)<0.1 && abs(R*(sin(k*u)-sin(C*u))+r*(sin(j*u)-sin(B*u))-z)<0.1 )        //后面的角度见前面的角度!!!!!
        break;
    }
   }
   C=k;
   B=j;
} 
