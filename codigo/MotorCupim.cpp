#include "MotorCupim.h"
#include <Arduino.h>

void MotorCupim::MotorCupim(int i1, int i2, int i3, int i4){
  ini1 = i1;
  ini2 = i2;
  ini3 = i3;
  ini4 = i4;
}

void MotorCupim::setup(){
  pinMode(ini1, OUTPUT);
  pinMode(ini2, OUTPUT);
  pinMode(ini3, OUTPUT);
  pinMode(ini4, OUTPUT);
}

void MotorCupim::frente(){
  analogWrite(ini1, 255);
  analogWrite(ini2, 0);
  analogWrite(ini3, 255);
  analogWrite(ini4, 0);
}

void MotorCupim::tras(){
  analogWrite(ini1, 0);
  analogWrite(ini2, 255);
  analogWrite(ini3, 0);
  analogWrite(ini4, 255);
}

void MotorCupim::direita(){
  analogWrite(ini1, 255);
  analogWrite(ini2, 0);
  analogWrite(ini3, 0);
  analogWrite(ini4, 255);
}

void MotorCupim::esquerda(){
  analogWrite(ini1, 0);
  analogWrite(ini2, 255);
  analogWrite(ini3, 255);
  analogWrite(ini4, 0);
}

void MotorCupim::parado(){
  analogWrite(ini1, 0);
  analogWrite(ini2, 0);
  analogWrite(ini3, 0);
  analogWrite(ini4, 0);
}

