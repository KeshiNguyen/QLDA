#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); // RX, TX




const int inA1      = 9; 
const int inA2      = 8; 
const int enA  = 10;
const int inB1      = 7; 
const int inB2      = 6;
 const int enB  = 5; 


const int L_S = 12;
const int S_S = 4; 
const int R_S = 11;
int left_sensor_state;
int s_sensor_state;  
int right_sensor_state;

int spd=150;




void setup() {
  pinMode(L_S, INPUT); 
  pinMode(R_S, INPUT);
  pinMode(S_S, INPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  analogWrite(enA, spd);
  analogWrite(enB, spd);
  delay(2000);

}

void forword() { 
  // for (int i=1; i<=spd;i++) {
     digitalWrite (inA1, LOW);
      digitalWrite(inA2, HIGH);
      digitalWrite (inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enA,250);
      analogWrite(enB,250);
  //     delay(10);
  // } 
}

void back() { 

  digitalWrite (inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite (inB1, HIGH);
  digitalWrite(inB2, LOW);
  delay(10);
}


void turnRight() {
  for(int i=spd;i<=200;i++) {
    digitalWrite (inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite (inB1, LOW);
  digitalWrite(inB2, HIGH);
    analogWrite(enA,i);
      analogWrite(enB,i);
  delay(1);
  }

}

void turnLeft() {
  for(int i =spd; i<=200;i++) {
      digitalWrite (inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite (inB1, HIGH);
  digitalWrite(inB2, LOW);
   analogWrite(enA,i);
      analogWrite(enB,i);
    delay(1);

  }
}

void Stop() {

  digitalWrite (inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite (inB1, LOW);
  digitalWrite(inB2, LOW);
}



void loop() {
  delayMicroseconds(2);
  delayMicroseconds(10);

  left_sensor_state = digitalRead(L_S);
  s_sensor_state = digitalRead(S_S);
  right_sensor_state = digitalRead(R_S);

  // 010 di thang
  // 100 trai ddao banh
  // 110 trai cua
  // 011 cua phai
  // 001 phai dao banh
  // 000 dung yen
  // 111 di thang

  if ((digitalRead(L_S) == 0) && (digitalRead(S_S) == 1) && (digitalRead(R_S) == 0)) { 
    forword(); // đi tiến
  }

  else if ((digitalRead(L_S) == 1) && (digitalRead(S_S) == 1) && (digitalRead(R_S) == 0)) {
    turnLeft(); // rẻ trái
  }
  else if ((digitalRead(L_S) == 1) && (digitalRead(S_S) == 0) && (digitalRead(R_S) == 0)) {
    turnLeft(); // rẻ trái dao banh
  }

  else if ((digitalRead(L_S) == 0) && (digitalRead(S_S) == 1) && (digitalRead(R_S) == 1)) {
    turnRight(); // rẻ phải
  }
  else if ((digitalRead(L_S) == 0) && (digitalRead(S_S) == 0) && (digitalRead(R_S) == 1)) {
    turnRight(); // rẻ phải
  }

  else if ((digitalRead(L_S) == 0) && (digitalRead(S_S) == 0) && (digitalRead(R_S) == 0)) {
  // stopO
    int count =0;
    while(count<5) {
      forword();
      delay(5);
      count++;
      if(!digitalRead(L_S) || !digitalRead(S_S) || !digitalRead(R_S)){break;}
    }
    Stop();
  }
  else if((digitalRead(L_S) == 1) && (digitalRead(S_S) == 1) && (digitalRead(R_S) == 1)) {
    forword();
    delay(10);
  }
  else if((digitalRead(L_S) == 1) && (digitalRead(S_S) == 0) && (digitalRead(R_S) == 1)) {
    forword();
    delay(10);
  }
  delay(10);
}




