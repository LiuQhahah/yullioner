/*****羽良工作室科技分享会*****/
/**可跟踪人脸摄像头下位机源码**/
/********科技实践部_彭曾*******/
/*工作邮箱pengzeng@yullion.com*/
/******内部资料,谢绝外传*******/
/******************************/
#define horz_X_PIN 9
#define vert_Y_PIN 10

#include <Servo.h>

Servo horz;
Servo vert;


char buffer[10];

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  horz.attach(horz_X_PIN);
  vert.attach(vert_Y_PIN);
  horz.write(80);
  vert.write(50);
}

void loop()
{
  if (Serial.available()>0)
  {
    int index=0;
    delay(100);//等待缓冲区充满
    int numChar = Serial.available();//确定字符串长度
    if (numChar>10)
    {
      numChar=10;
    }
    while (numChar--)
    {
      buffer[index++]=Serial.read();//用字符串填满缓存
    }
    char* parameter;
    parameter=strtok(buffer," ,");//到逗号的字符串
    while (parameter != NULL)//如果还没到字符串结尾
    {
      if ((parameter[0]=='X')||(parameter[0]=='x'))
      {
        int firstVal=strtol(parameter+1,NULL,10);//字符串转换为长整型
        firstVal=constrain(firstVal,0,160);//数值约束
        horz.write(firstVal);
      }
      
      if ((parameter[0]=='Y')||(parameter[0]=='y'))
      {
        int secondVal=strtol(parameter+1,NULL,10);//字符串转换为长整型
        secondVal=constrain(secondVal,0,180);//数值约束
        vert.write(secondVal);
      }
      parameter=strtok(NULL," ,");
    }
    //清除串口缓冲器的文本
    for(int x=0;x<9;x++)
    {
      buffer[x]='\0';
    }
    Serial.flush();
  }
}
