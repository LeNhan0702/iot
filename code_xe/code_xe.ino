

#include<SPI.h> //chuẩn giao tiêpSPI//
#include<nRF24L01.h> // thư viện điều khiển module NRF24L01
#include<RF24.h> // giao tiếp sóng RF 

int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;


RF24 radio(8, 10);

const byte address[6] = "00001";// địa chỉ 

struct data {
  int xAxis;
  int yAxis;

};
data receive_data;// chuỗi dữ liệu nhận vào 



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
radio.begin(); 
// cấu hình nhận tín hiêu//
radio.openReadingPipe(0,address);// luồng nhận hiêu tín 
radio.setPALevel(RF24_PA_MIN);// cài thông số bộ khuyết đại là -18 dBm .  
radio.setDataRate(RF24_250KBPS);// cài tốc độ truyền dữ liệu là 250kb/s . 
radio.startListening();
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);// dc trái trước .  
pinMode(MotorA2, OUTPUT);// dc phải trước . 
pinMode(MotorB1, OUTPUT);// dc trái sau   
pinMode(MotorB2, OUTPUT);// dc phải sau . 
}


void loop() {
  // put your main code here, to run repeatedly
 while(radio.available()) {
    radio.read(&receive_data, sizeof(data));
   if(receive_data.yAxis < 300) //LUI 
     { 
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, HIGH);
        digitalWrite(MotorB1, HIGH);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);  
      }
  else if(receive_data.yAxis > 370)//TIEN
      {
        digitalWrite(MotorA1, HIGH);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      } 
  else if(receive_data.xAxis < 300) //XOAY_Trai
      {
        digitalWrite(MotorA1, HIGH);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, HIGH);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
  else if(receive_data.xAxis < 320) //TIEN_trai
      {
        digitalWrite(MotorA1, HIGH);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
   else if(receive_data.xAxis > 360) //XOAY_PHAI
      {
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, HIGH);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
  else if(receive_data.xAxis > 345) //tien_PHAI
      {
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, HIGH);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
        else if(receive_data.yAxis > 340) //tien_PHAI
      {
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, HIGH);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
         else if(receive_data.yAxis < 320) //LUI_trai
      {
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, HIGH);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 150);
        analogWrite(ENB, 150);
      }
   else // DUNG_XE
     {
        digitalWrite(MotorA1, LOW);
        digitalWrite(MotorA2, LOW);
        digitalWrite(MotorB1, LOW);
        digitalWrite(MotorB2, LOW);
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
      }
  }
}
