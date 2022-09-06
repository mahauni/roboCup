#include <SoftwareSerial.h>
SoftwareSerial MyBlue(2, 3);
int flag = 0;
int weaponSen = 12;
int weaponState = 0;
int weaponStep = 0;
unsigned long startTime = 0;
int superPosition = 0;
int val = 0;

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

  val = digitalRead(weaponSen);
  if (weaponState == 0 && (!(val == 1) || superPosition == 1)) {
    if (superPosition == 0) {
      superPosition = 1;
    }
    if (weaponStep%10==0){
      Serial.println("A arma sendo ativada");
    }
    weaponStep++;
    analogWrite(4, 250);
    analogWrite(11, 0);
    //after weapon being all pushed
    if (weaponStep == 200) {
      Serial.println("A arma foi ativada");
      weaponState = 1;
      weaponStep = 0;
      startTime = millis();
      superPosition = 0;
      analogWrite(4, 0);
      analogWrite(11, 0);
    }
  }

  if (weaponState == 1 && millis() - startTime > 5000) {
    //after weapon being all pushed
    if (weaponStep%10==0){
      Serial.println("Arma esta sendo desativada");
    }
    weaponStep++;
    analogWrite(4, 0);
    analogWrite(11, 250);
    if (weaponStep == 200) {
      Serial.println("Arma foi desativada");
      weaponState = 0;
      weaponStep = 0;
      analogWrite(4, 0);
      analogWrite(11, 0);
    }
  }
}
