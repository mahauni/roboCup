#include <SoftwareSerial.h>
SoftwareSerial MyBlue(2, 3);
int flag = 0;
int weaponSen = 52;
int weaponState = 0;
int weaponStep = 0;
unsigned long startTime = 0;
unsigned long maxTime = 0;
int superPosition = 0;

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


  // problemas
  //
  // a arma dps que o sensor para de ficar ativado, a arma vai parar de andar para frente, podendo nem chegar ao seu alvo
  // precisa ter algo, que quando o sensor identificar, entao ele vai para frente. e faz isso por um tempo determinado.. 
  // usando o mesmo metodo para contar quando voltar depois de um tempo..
  //
  // a arma nao vai voltar depois de um tempo determinado
  // para arrumar isso usar o clock que tem no arduino (existe algo para fazer isso funcionar, mas eu nao sei o nome do commando)

  if (weaponState == 0 && (digitalRead(weaponSen) == "HIGH" || superPosition == 1 && millis() - startTime < 6000)) {
    if (superPosition == 0) {
      superPosition = 1;
      startTime = millis();
    }
    Serial.println("A arma sendo ativada");
    weaponStep++;
    //after weapon being all pushed
    if (weaponStep == 500) {
      Serial.println("A arma foi ativada");
      weaponState = 1;
      weaponStep = 0;
      maxTime = millis();
    }
  }

  if (weaponState == 1 && millis() - maxTime > 10000) {
    Serial.printlnI("Arma esta sendo desativada");
    //after weapon being all pushed
    weaponStep++;
    if (weaponStep == 500) {
      Serial.printlnI("Arma foi desativada");
      weaponState = 0;
      weaponStep = 0;
      startTime = millis();
    }
  }
}
