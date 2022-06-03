//==========================================
// UNTUK RANGKAIAN PINYA CEK AJA DI BAWAH SUDAH JELAS UNTUK PIN-PINNYA.
// PIN DRIVER MOTOR
// EN A PIN 10
// IN1 PIN 9
// IN2 PIN 8
// IN3 PIN 7
// IN4 PIN 6
// EN B PIN 5

// PIN SENSOR ULTRASONIK
// ECHO PIN A2
// TRIGER A3

// PIN SENSOR PHOTODIODA
// SENSOR KANAN PINA0
// SENSOR KIRI PIN A1

// PIN SERVO
// SERVO PIN A4

// PIN BLUETOOTH
// RX BL PIN 2
// TX BL PIN 3

#include <SoftwareSerial.h>
#include <Servo.h>
Servo buka_tutup;
SoftwareSerial BT_Serial(2, 3); // RX, TX

#define enA 12//Enable1 L298 Pin enA 
#define in1 11 //Motor1  L298 Pin in1 
#define in2 7 //Motor1  L298 Pin in1 
#define in3 6 //Motor2  L298 Pin in1 
#define in4 5 //Motor2  L298 Pin in1 
#define enB 4 //Enable2 L298 Pin enB 

#define sensor_kanan A0 //ir sensor Right
#define sensor_kiri A1 //ir sensor Left

#define echo A2    //Echo pin
#define trigger A3 //Trigger pin

int distance_L, distance_F = 30, distance_R;
//long distance;
int set = 20;

int bt_ir_data; 
int Speed = 130;  
int mode=0;


void setup(){ 

pinMode(sensor_kanan, INPUT); 
pinMode(sensor_kiri, INPUT); 

pinMode(echo, INPUT );
pinMode(trigger, OUTPUT); 

pinMode(enA, OUTPUT); 
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT); 
pinMode(enB, OUTPUT); 
pinMode(12, OUTPUT); 

buka_tutup.attach(A4);
buka_tutup.write(0);

Serial.begin(9600); 
BT_Serial.begin(9600); 
}

void loop(){  
 // ===========================================================
 //INI PROGRAM UNTUK BUKA TUTUP TONG SAMPAH
 //==========================================================
  

if(BT_Serial.available() > 0){ 
bt_ir_data = BT_Serial.read(); 
Serial.println(bt_ir_data);     
if(bt_ir_data > 20){Speed = bt_ir_data;}      
}

delay(100);

     if(bt_ir_data == 8){mode=0; Stop();}    //Mode menggunakan Aplikasi Android dengan Manual
else if(bt_ir_data == 9){mode=1; Speed=130;} //Ini perintah untuk robot line follower pengikut garis


analogWrite(enA, Speed); 
analogWrite(enB, Speed); 

if(mode==0){     
//===============================================================================
//                          INI PROGRAM PERINTAH TOMBOL
//=============================================================================== 
     if(bt_ir_data == 1){maju(); } // jika bt_data adalah '1' motor DC akan maju
else if(bt_ir_data == 2){mundur();}// jika bt_data adalah '2' motor akan Mundur
else if(bt_ir_data == 3){kiri();}  // jika bt_data '3' motor akan belok kiri
else if(bt_ir_data == 4){kanan();} // jika bt_data '4' motor akan belok kanan
else if(bt_ir_data == 5){Stop(); } // jika bt_data '5' motor akan Berhenti

 
else if(bt_ir_data == 6){kiri();  delay(400);  bt_ir_data = 5;}
else if(bt_ir_data == 7){kanan(); delay(400);  bt_ir_data = 5;}
}

if(mode==1){    
//====================================================================================================
//                         INI PROGRAM UNTUK LINE FOLLOWER BERJALAN DI ATAS JALAN HITAM DAN PUTIH
//===============================================================================   =================  
if((digitalRead(sensor_kanan) == 0)&&(digitalRead(sensor_kiri) == 0)){maju();}  
if((digitalRead(sensor_kanan) == 1)&&(digitalRead(sensor_kiri) == 0)){kanan();}
if((digitalRead(sensor_kanan) == 0)&&(digitalRead(sensor_kiri) == 1)){kiri();} 
if((digitalRead(sensor_kanan) == 1)&&(digitalRead(sensor_kiri) == 1)){Stop();}     
} 
 
delay(10);
}

void maju(){  
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW);  
digitalWrite(in3, LOW);  
digitalWrite(in4, HIGH);  
}

void mundur(){ 
digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
digitalWrite(in3, HIGH);  
digitalWrite(in4, LOW); 
}

void kanan(){ 
digitalWrite(in1, LOW);  
digitalWrite(in2, HIGH); 
digitalWrite(in3, LOW);  
digitalWrite(in4, HIGH); 
}

void kiri(){ 
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW);  
digitalWrite(in3, HIGH); 
digitalWrite(in4, LOW);  
}

void Stop(){ 
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);  
digitalWrite(in4, LOW); 
}
