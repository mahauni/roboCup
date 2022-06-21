#include <SoftwareSerial.h>
SoftwareSerial MyBlue(2, 3);
int flag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyBlue.begin(9600);
  Serial.println("Ready to command\nDefault password is 1234 or 000");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (MyBlue.available()) {
    flag = MyBlue.read();
    Serial.println(flag);

    if (flag == 117) {
      Serial.println("Andei para frente");
      analogWrite(5, 250);
      analogWrite(6, 0);
      analogWrite(9, 205);
      analogWrite(10, 0);
    } else if (flag == 108) {
      Serial.println("Andei para e esquerda");
      analogWrite(5, 0);
      analogWrite(6, 190);
      analogWrite(9, 180);
      analogWrite(10, 0);
    } else if (flag == 114) {
      Serial.println("Andei para a direita");
      analogWrite(5, 190);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 180);
    } else if (flag == 100) {
      Serial.println("Andei para tras");
      analogWrite(5, 0);
      analogWrite(6, 190);
      analogWrite(9, 0);
      analogWrite(10, 180);
    } else if (flag == 115) {
      Serial.println("Parei de andar");
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 0);
    }
    
  }
}
