#include <Arduino.h>
#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x2, 16, 2);

Servo myservo;

int pos = 0;

int PRE1 = 2;
int INDU = 3;
int PRE2 = 4;

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int s0 = A0;
const int s1 = A1;
const int s2 = A2;
const int s3 = A3;
const int out = 6;

int red = 0;
int green = 0;
int blue = 0;

const int passosPorPosicao = 512;

void setup() {
  lcd.init();
  lcd.backlight();
  
  myStepper.setSpeed(60);

  myservo.attach(12);

  Serial.begin(9600);

  pinMode(PRE1, INPUT);
  pinMode(INDU, INPUT);
  pinMode(PRE2, INPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}

void abre_fecha_servo() {
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  delay(200);

  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}

void movimenta_motor_passo() {
  myStepper.step(passosPorPosicao);
  delay(2000);
}

void volta_para_zero(int posicaoAtual) {
  myStepper.step(-passosPorPosicao * posicaoAtual);
  delay(2000);
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void loop() {
  if (digitalRead(PRE1) == LOW) {
    lcd.clear(); // Limpa ao detectar lixo
    
    int posicaoAtual = 0;
    bool lixoEncontrado = false;

    movimenta_motor_passo();
    posicaoAtual++;

    if (digitalRead(INDU) == LOW) {
      Serial.println("Sensor indutivo detectou lixo");
      
      lcd.setCursor(0, 0);
      lcd.print("      METAL!");
      
      abre_fecha_servo();
      lixoEncontrado = true;
    }

    if (!lixoEncontrado) {
      movimenta_motor_passo();
      posicaoAtual++;

      color();

      if (red < blue && red < green && red < 100) {
        Serial.println("Vermelho detectado");
        
        lcd.setCursor(0, 0);
        lcd.print("    PLASTICO!");
        
        abre_fecha_servo();
        lixoEncontrado = true;
      }
    }

    if (!lixoEncontrado) {
      movimenta_motor_passo();
      posicaoAtual++;

      if (digitalRead(PRE2) == LOW) {
        Serial.println("Sensor de presença 2 detectou lixo");
        
        lcd.setCursor(0, 0);
        lcd.print("      PAPEL!");
        
        abre_fecha_servo();
        lixoEncontrado = true;
      }
    }

    volta_para_zero(posicaoAtual);
    delay(500);
  } 
  else {
    lcd.setCursor(0, 0);
    lcd.print("COLOQUE O LIXO!");
  }
}