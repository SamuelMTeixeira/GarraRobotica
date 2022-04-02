#include <Servo.h>

// =====================================================================================//
// SOBRE OS SERVOS...

// PORTA DIGITAL QUE CADA SERVO ESTÁ CONECTADO
const int pinServoAvancar = 2;
const int pinServoGarra   =  4;
const int pinServoGiro    =  7;
const int pinServoElevar  = 8;

// CLASSE COM OS COMANDOS DOS SERVOS
class ServoGarra {
    Servo servo;
    boolean isStuck = false;
    int posicao = 0;
  public:
    // CONFIGURA A PORTA DIGITAL DO SERVO MOTOR E SEU ANGULO INICIAL
    void setConfig(int porta, int anguloInicial) {
      servo.attach(porta);
      servo.write(anguloInicial);
      posicao = anguloInicial;
    }

    // FAZ O SERVO IR PRA FRENTE/CIMA/DIREITA
    void paraFrente () {
      int pos = posicao + 2;
      if (pos < 180) {
        servo.write(pos);
        posicao = pos;
      }
      delay(5);
    }

    // FAZ O SERVO IR PRA TRÁS/BAIXO/ESQUERDA
    void paraTras () {
      int pos = posicao - 2;
      if (pos > 0) {
        servo.write(pos);
        posicao = pos;
      }
      delay(5);
    }

    // ABRE E FECHA A GARRA
    void agarrar() {

      if (isStuck == false) {
        for (int i = 0; i < 90; i++) { // FECHA A GARRA
          servo.write(i);
          delay(2);
        }
        isStuck = true;
      }

      else {  // ABRE A GARRA
        for (int i = 90; i > 0; i--) {
          servo.write(i);
          delay(2);
        }
        isStuck = false;
      }

    }

};

// INSTÂNCIA AS CLASSES DO SERVO
ServoGarra girar, avancar, elevar, garra;

// =====================================================================================//
// SOBRE O JOYSTICK...
const int eixo_X = A0; //PINO REFERENTE A LIGAÇÃO DO EIXO X
const int eixo_Y = A1; //PINO REFERENTE A LIGAÇÃO DO EIXO Y
const int eixo_alavanca = A2; // PINO REFERENTE A LIGAÇÃO DA ALAVANCA
const int botao = 3; //PINO REFERENTE AO BOTÃO

void setup() {
  Serial.begin (9600);

  // CONFIGURA A PORTA E ANGULAGEM PADRÃO DE CADA SERVO
  girar.setConfig(pinServoGiro, 90);
  avancar.setConfig(pinServoAvancar, 0);
  elevar.setConfig(pinServoElevar, 0);
  garra.setConfig(pinServoGarra, 0);

  // ATIVA O RESISTOR INTERNO PARA O BOTAO
  pinMode (botao, INPUT_PULLUP);
}

void loop() {

  // LADO PARA "TRÁS" DO JOYSTICK || LEVANTA A GARRA
  if ((analogRead(eixo_X)) == 0) {
    avancar.paraTras();
  }

  // LADO PARA "FRENTE" DO JOYSTICK || ABAIXA A GARRA
  else if ((analogRead(eixo_X)) == 1023) {
    avancar.paraFrente();
  }

  // VIRA PRA "ESQUERDA" PELO JOYSTICK || VIRA A GARRA
  else if ((analogRead(eixo_Y)) == 0) {
    girar.paraTras();
  }

  // VIRA PRA  "DIRETA" PELO JOYSTICK || VIRA A GARRA
  else if ((analogRead(eixo_Y)) == 1023) {
    girar.paraFrente();
  }

  // BOTÃO DO JOYSTICK
  else if (digitalRead(botao) == LOW) {
    garra.agarrar();
  }

  // VIRA PRA "CIMA" PELO JOYSTICK
  else if ((analogRead(eixo_alavanca)) == 0) { //SE LEITURA FOR IGUAL A 0, FAZ
    elevar.paraTras();
  }

  // VIRA PRA "BAIXO" PELO JOYSTICK
  else if ((analogRead(eixo_alavanca)) == 1023) { //SE LEITURA FOR IGUAL A 1023, FAZ
    elevar.paraFrente();
  }

}
