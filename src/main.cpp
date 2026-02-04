#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>


#define STEP_PIN D2
#define DIR_PIN  D1
#define EN_PIN   D8
#define ENCODER_CLK D4
#define ENCODER_DT  D2
#define ENCODER_SW  D7
#define tela_sda D5
#define tela_scl D6

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long tempoInicio;
unsigned long tempoAtual;
long velocidadeAtual = 2000;
long velocidadeAlvo  = 2000;
long velocidadeMin   = 400;
long velocidadeMax   = 3000;
int lastCLK;
bool motorLigado = true;

void girarMotor();
void lerEncoder();
void rampaVelocidade();
void atualizarDisplay();
void pararMotor();
void ligarMotor();
void verificarBotao();

void setup() {
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(ENCODER_CLK, INPUT_PULLUP);
    pinMode(ENCODER_DT, INPUT_PULLUP);
    pinMode(ENCODER_SW, INPUT_PULLUP);
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(EN_PIN, LOW);
    lcd.init();
    lcd.backlight();
    tempoInicio = millis();
    lastCLK = digitalRead(ENCODER_CLK);
}

void loop() {
    verificarBotao();
    lerEncoder();
    rampaVelocidade();
    girarMotor();
    atualizarDisplay();
}

void girarMotor() {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(velocidadeAtual);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(velocidadeAtual);
}

void lerEncoder() {
    int estadoCLK = digitalRead(ENCODER_CLK);
    if (estadoCLK != lastCLK) {
        if (digitalRead(ENCODER_DT) != estadoCLK) {
            velocidadeAlvo -= 100;
        } else {
            velocidadeAlvo += 100;
        }
        if (velocidadeAlvo < velocidadeMin) velocidadeAlvo = velocidadeMin;
        if (velocidadeAlvo > velocidadeMax) velocidadeAlvo = velocidadeMax;
    }
    lastCLK = estadoCLK;
}

void rampaVelocidade() {
    if (velocidadeAtual < velocidadeAlvo) {
        velocidadeAtual += 10;
    } else if (velocidadeAtual > velocidadeAlvo) {
        velocidadeAtual -= 10;
    }
}

void atualizarDisplay() {
    tempoAtual = (millis() - tempoInicio) / 1000;
    lcd.setCursor(0, 0);
    lcd.print("Tempo: ");
    lcd.print(tempoAtual);
    lcd.print("s   ");
    lcd.setCursor(0, 1);
    lcd.print("Vel: ");
    lcd.print(velocidadeAtual);
    lcd.print("    ");
}

void pararMotor() {
    digitalWrite(EN_PIN, HIGH);
    motorLigado = false;
}

void ligarMotor() {
    digitalWrite(EN_PIN, LOW);
    motorLigado = true;
}

void verificarBotao() {
    if (digitalRead(ENCODER_SW) == LOW) {
        if (motorLigado) {
            pararMotor();
        } else {
            ligarMotor();
        }
        delay(500);
    }
}
