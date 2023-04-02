/* Basic Arduino example code for displaying text on 16x2, 20x4 etc. character LCDs. More info:
www.makerguides.com */
// Include the library:
#include <LiquidCrystal.h>
// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);
int stage = 0;
int x = 0;
int y;
int v = 0;
int button0;
int button1;
int button2;
int button3;
int button4;
bool LED1 = false;
bool LED2 = false;
bool LED3 = false;
bool LED4 = false;
bool firstLED1 = false;
bool firstLED2 = false;
bool firstLED3 = false;
bool firstLED4 = false;
bool secondLED1 = false;
bool secondLED2 = false;
bool secondLED3 = false;
bool secondLED4 = false;
bool carry1 = false;
bool carry2 = false;
bool carry3 = false;
bool carry4 = false;
bool sum1 = false;
bool sum2 = false;
bool sum3 = false;
bool comp = false;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
 // Specify the LCD's number of columns and rows. Change to (20, 4) for a 20x4 LCD:
 lcd.begin(16, 2);
}
void loop() {
 buttonChange();
 if (stage == 1 && comp == false){
  stage1();
 }
 if (stage == 2 && comp == false){
  stage2();
 }
 if (stage == 3 && comp == false){
  stage3();
 }
}
void buttonChange(){
  button0 = digitalRead(A0);
  button1 = digitalRead(A1);
  button2 = digitalRead(A2);
  button3 = digitalRead(A3);
  button4 = digitalRead(A4);
  if (button0 == HIGH){
    stage++;
    comp = false;
  }
  if (button1 == HIGH && LED1 == false){
    LED1 = true;
    digitalWrite(12, HIGH);
  } else if (button1 == HIGH && LED1 == true){
    LED1 = false;
    digitalWrite(12,LOW);
  }
  if (button2 == HIGH && LED2 == false){
    LED2 = true;
    digitalWrite(11, HIGH);
  } else if (button2 == HIGH && LED2 == true){
    LED2 = false;
    digitalWrite(11,LOW);
  }
  if (button3 == HIGH && LED3 == false){
    LED3 = true;
    digitalWrite(10, HIGH);
  } else if (button3 == HIGH && LED3 == true){
    LED3 = false;
    digitalWrite(10,LOW);
  }
  if (button4 == HIGH && LED4 == false){
    LED4 = true;
    digitalWrite(9, HIGH);
  } else if (button4 == HIGH && LED4 == true){
    LED4 = false;
    digitalWrite(9,LOW);
  }
  delay(1000);
}
void stage1(){
  firstLED1 = LED1;
  firstLED2 = LED2;
  firstLED3 = LED3;
  firstLED4 = LED4;
  x = binToDec(LED1,LED2,LED3,LED4);
  // Set the cursor on the third column and the first row, counting starts at 0:
 lcd.setCursor(0, 0);
 lcd.print(x);
 lcd.print(" + ");
 lcd.setCursor(0, 1);
 lcd.print(x,HEX);
 lcd.print(" + ");
 comp = true;
 LED1 = false;
 LED2 = false;
 LED3 = false;
 LED4 = false;
digitalWrite(12,LOW);
digitalWrite(11,LOW);
digitalWrite(10,LOW);
digitalWrite(9,LOW);
}
void stage2(){
  secondLED1 = LED1;
  secondLED2 = LED2;
  secondLED3 = LED3;
  secondLED4 = LED4;
  v = binToDec(LED1,LED2,LED3,LED4);
  // Set the cursor on the third column and the first row, counting starts at 0:
 lcd.setCursor(5, 0);
 lcd.print(v);
 lcd.print(" = ");
 lcd.print(x+v);
 lcd.setCursor(5, 1);
 lcd.print(v,HEX);
 lcd.print(" = ");
 lcd.print(x+v,HEX);
 binAdd();
 comp = true;
}
void stage3(){
  LED1 = false;
  LED2 = false;
  LED3 = false;
  LED4 = false;
  firstLED1 = false;
  firstLED2 = false;
  firstLED3 = false;
  firstLED4 = false;
  secondLED1 = false;
  secondLED2 = false;
  secondLED3 = false;
  secondLED4 = false;
  carry1 = false;
  carry2 = false;
  carry3 = false;
  carry4 = false;
  sum1 = false;
  sum2 = false;
  sum3 = false;
  comp = false;
  lcd.clear();
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(9,LOW);
  stage = 0;
}

int binToDec(bool a, bool b, bool c, bool d){
  y = 0;
  if (d == true){
    y += 1;
  }
  if (c == true){
    y += 2;
  }
  if (b == true){
    y += 4;
  }
  if (a == true){
    y += 8;
  }
  return y;
}
void binAdd(){
  LED1 = false;
  LED2 = false;
  LED3 = false;
  LED4 = false;
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  //half adder
  if ((XOR(firstLED4, secondLED4))){
    digitalWrite(9,HIGH);
  }
  if (firstLED4 && secondLED4){
    carry1 = true;
  }
  //full adder 1
  if (XOR(firstLED3, secondLED3)){
    sum1 = true;
  }
  if (XOR(sum1, carry1)){
    digitalWrite(10,HIGH);
  }
  if ((sum1 && carry1) || (firstLED3 && secondLED3)){
    carry2 = true;
  }
  //full adder 2
  if (XOR(firstLED2, secondLED2)){
    sum2 = true;
  }
  if (XOR(sum2, carry2)){
    digitalWrite(11,HIGH);
  }
  if ((sum2 && carry2) || (firstLED2 && secondLED2)){
    carry3 = true;
  }
  //full adder 3
  if (XOR(firstLED1, secondLED1)){
    sum3 = true;
  }
  if (XOR(sum3, carry3)){
    digitalWrite(12,HIGH);
  }
  if ((sum3 && carry3) || (firstLED1 && secondLED1)){
    carry4 = true;
  }
  if (carry4){
    digitalWrite(13,HIGH);
  }
}
bool XOR(bool a, bool b){
  return (!(a && b) && (a || b));
}
