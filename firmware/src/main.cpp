#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>



#define STEP_PIN D2
#define DIR_PIN  D1

#define EN_PIN   D8
#define ENCODER_CLK D4
#define ENCODER_DT  D3
#define ENCODER_SW  D7

#define tela_sda D5
#define tela_scl D6
#define MENU_VELOCIDADE 0
#define MENU_TEMPO      1
#define ESTADO_RODANDO  2
#define ESTADO_FIM      3

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long tempoInicio;
unsigned long tempoAtual;
unsigned long lastDisplayUpdate = 0;
long velocidadeAtual = 2000;
long velocidadeAlvo  = 2000;
long velocidadeMin   = 400;
long velocidadeMax   = 3000;
int lastCLK;
bool motorLigado = false;
int estadoatual = MENU_VELOCIDADE;
int minutosparados = 0;
int minutosalvo =30;

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
    digitalWrite(EN_PIN, HIGH);
    
    Wire.begin(tela_sda, tela_scl);
    lcd.init();
    lcd.backlight();
    tempoInicio = millis();
    lastCLK = digitalRead(ENCODER_CLK);
}

void loop() {
    verificarBotao();
    lerEncoder();
    rampaVelocidade();

    if (estadoatual == ESTADO_RODANDO)
    {
        girarMotor();
        unsigned long tempoDecorrido = (millis() - tempoInicio) / 1000;
        if (tempoDecorrido >= minutosalvo * 60) {
            estadoatual = ESTADO_FIM;
            pararMotor();
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Processo");
            lcd.setCursor(0, 1);
            lcd.print("Concluido!");
        }
    }
    
if (millis() - lastDisplayUpdate > 200) {
        atualizarDisplay();
        lastDisplayUpdate = millis();
    }
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
        if (estadoatual == MENU_VELOCIDADE) {
            if (digitalRead(ENCODER_DT) != estadoCLK) {
                velocidadeAlvo -= 100;
            } else {
                velocidadeAlvo += 100;
            }
            if (velocidadeAlvo < velocidadeMin) velocidadeAlvo = velocidadeMin;
            if (velocidadeAlvo > velocidadeMax) velocidadeAlvo = velocidadeMax;
        }
        else if (estadoatual == MENU_TEMPO) {
            if (digitalRead(ENCODER_DT) != estadoCLK) {
                minutosalvo += 1;
            } else {
                minutosalvo -= 1;
            }
            if (minutosalvo < 1) minutosalvo = 1;
            if (minutosalvo > 120) minutosalvo = 120;
        }
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
    if (estadoatual == MENU_VELOCIDADE) {
        lcd.setCursor(0, 0);
        lcd.print("Velocidade:     ");
        lcd.setCursor(0, 1);
        lcd.print(velocidadeAlvo);
        lcd.print(" us     ");
    }
    else if (estadoatual == MENU_TEMPO) {
        lcd.setCursor(0, 0);
        lcd.print("Tempo:          ");
        lcd.setCursor(0, 1);
        lcd.print(minutosalvo);
        lcd.print(" min     ");
    }
    else if (estadoatual == ESTADO_RODANDO) {
        tempoAtual = (millis() - tempoInicio) / 1000;
        lcd.setCursor(0, 0);
        lcd.print("T: ");
        lcd.print(tempoAtual);
        lcd.print("s/");
        lcd.print(minutosalvo * 60);
        lcd.print("s  ");
        lcd.setCursor(0, 1);
        lcd.print("Vel: ");
        lcd.print(velocidadeAtual);
        lcd.print("    ");
    }
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
        delay(300); 
        
        if (estadoatual == MENU_VELOCIDADE) {
            estadoatual = MENU_TEMPO; 
            lcd.clear();
        } 
        else if (estadoatual == MENU_TEMPO) {
            estadoatual = ESTADO_RODANDO; 
            tempoInicio = millis(); 
            ligarMotor(); 
            lcd.clear();
        }
        else if (estadoatual == ESTADO_RODANDO) {
            estadoatual = MENU_VELOCIDADE; 
            pararMotor();
            lcd.clear();
        }
        else if (estadoatual == ESTADO_FIM) {
            estadoatual = MENU_VELOCIDADE; 
            lcd.clear();
        }
        
        while (digitalRead(ENCODER_SW) == LOW); 
    }
}