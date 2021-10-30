#include <Servo.h>
#include "Volume3.h"

// CRONOMETRO BOTONES

float tiempoInicial20 = 0;
float tiempoAnterior20 = 0;
float tiempoTranscurrido20 = 0;

int estado20 = 0;
int estadoCheck20 = 0;
int pasaronXsegundos20 = 0;

int sustancia_agregada20 = 0;

//--------------------------
//CRONOMETRO GLOBAL

float tiempoInicialGLOBAL = 0;


//---------------------------
//CRONOMETRO GAMEOVER
float tiempoInicial_CronometroMuerte = 0;
float tiempoAnterior_CronometroMuerte = 0;
float tiempoTranscurrido_CronometroMuerte = 0;
int estado_CronometroMuerte = 0;
int estadoCheck_CronometroMuerte = 0;
int pasaronXsegundos20_CronometroMuerte = 30;

//---------------------------
//CRONOMETRO BUZZER
float tiempoInicial_Buzzer = 0;
float tiempoAnterior_Buzzer = 0;
float tiempoTranscurrido_Buzzer = 0;
int estado_Buzzer = 0;
int estadoCheck_Buzzer = 0;
int pasaronXsegundos_Buzzer = 0;
int volume = 50;
int frecuencia = 440;
//---------------------------

//Servo
float rotacion = 46;
float aumentoXsegundo = 0.01;

int segundos_para_rotacion = 1;

//---------------------------
//Pulsadores
int boton1 = 7;
int boton2 = 6;
int boton3 = 5;
int botonpanico = 10;

//---------------------------
//SERVO
Servo servo_;

//---------------------------
//BUZZER
int pinBuzzer = 11;

//---------------------------
//LEDS
int led1 = 4;
int led2 = 3;
int led3 = 2;


void setup() {
  Serial.begin(9600);
  pinMode(boton1,INPUT);
  pinMode(boton2,INPUT);
  pinMode(boton3,INPUT);
  pinMode(botonpanico,INPUT);
  pinMode(pinBuzzer,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  servo_.attach(9);
  servo_.write(0);
}

void loop() {

  botonPanico();
  rotacionAutomatica();
  flujoBotones();
  //Serial.println(rotacion);
  Serial.println(estado20);//ESTADO PARA CONECTAR CON UNITY-NO DEBE ESTAR CONECTADO
  if(rotacion <= 180 && rotacion >=0){servo_.write(rotacion);}
  flujoBuzzer();
  GameOver();


  
  
  
}

void botonPanico()
{
  if(digitalRead(botonpanico) == 1)
  {
    //Serial.println("activaste el boton de panico");
    delay(30000);
    
  }
}
void rotacionAutomatica()
{
  tiempoInicialGLOBAL = millis()/1000;

  if(int(tiempoInicialGLOBAL)%segundos_para_rotacion==0 && tiempoInicialGLOBAL != 0)
  {
    if(rotacion>45)
    {
      rotacion += aumentoXsegundo;
      }
    else
    {
      rotacion -= aumentoXsegundo;
      }
    
    }
}

void flujoBotones()
{
  estadoCheck20 = estado20;
  
  if(digitalRead(boton1)==1)
   {
    estado20 = 1;
    sustancia_agregada20 = -5;
    pasaronXsegundos20 = 2;
    digitalWrite(led1,HIGH);
    }
  else if(digitalRead(boton2)==1)
   {
    estado20 = 2;
    sustancia_agregada20 = 10;
    pasaronXsegundos20 = 3;
    digitalWrite(led2,HIGH);
    }
  else if(digitalRead(boton3)==1)
   {
    estado20 = 3;
    sustancia_agregada20 = 20;
    pasaronXsegundos20 = 5;
    digitalWrite(led3,HIGH);
    }
  else
  {
    estado20 = 8000;
    pasaronXsegundos20 = 8000;
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    }
  
  //CRONOMETRO DE LOS BOTONES
  bool pasoELtime = Cronometro2_0(estado20,estadoCheck20,tiempoInicial20,tiempoAnterior20,tiempoTranscurrido20,pasaronXsegundos20);
  if(pasoELtime == true)
  {
    //AGREGAR SUSTANCIA
    agregarSustancia(sustancia_agregada20);
  }
  //Serial.println(pasoELtime);
}

void flujoBuzzer()
{
  estadoCheck_Buzzer = estado_Buzzer;
  
  if(rotacion<= 45 && rotacion>=0)
   {
    estado_Buzzer = 1;

    pasaronXsegundos_Buzzer = 8;
    }
  else if(rotacion<= 90 && rotacion>=45)
   {
    estado_Buzzer = 2;

    pasaronXsegundos_Buzzer = 1;
    }
  else if(rotacion<= 135 && rotacion>=90)
   {
    estado_Buzzer = 3;

    pasaronXsegundos_Buzzer = 4;
    }

  else if(rotacion<= 180 && rotacion>=135)
   {
    estado_Buzzer = 4;

    pasaronXsegundos_Buzzer = 2;//debe ser uno pero con truquito
    }
  else
  {
    estado_Buzzer = 8000;
    pasaronXsegundos_Buzzer = 8000;
    }
  
  //CRONOMETRO DE BUZZER
  bool consumioTimeBuzzer = Cronometro2_0(estado_Buzzer,estadoCheck_Buzzer,tiempoInicial_Buzzer,tiempoAnterior_Buzzer,tiempoTranscurrido_Buzzer,pasaronXsegundos_Buzzer);
  //Serial.println(consumioTimeBuzzer);//COMENTADO RECIENTEMENTE
  //vol.tone(pinBuzzer,frecuencia,volume);
  if(consumioTimeBuzzer == true)
  {
    tone(pinBuzzer,450);
  }
  else
  {
    noTone(pinBuzzer);
  }

  //vol.tone(pinBuzzer,frecuencia,volume);
}

void GameOver()
{
  //CRONOMETRO GAME OVER
  estadoCheck_CronometroMuerte = estado_CronometroMuerte;
  
  if(rotacion<45 || rotacion>135)
  {
    estado_CronometroMuerte = 1;
    bool gameover = Cronometro2_0(estado_CronometroMuerte,estadoCheck_CronometroMuerte,tiempoInicial_CronometroMuerte,tiempoAnterior_CronometroMuerte, tiempoTranscurrido_CronometroMuerte,pasaronXsegundos20_CronometroMuerte);
    if(gameover == true || tiempoTranscurrido_CronometroMuerte >=30)
      {
        Serial.println("LOSE");
      }
  }
  else
  {
    estado_CronometroMuerte = 0;
    
  }
  Serial.println("NOLOSE");
  //Serial.println(tiempoTranscurrido_CronometroMuerte);
}

bool Cronometro2_0(int &estado_, int &estadoCheck_, float &tiempoInicial_, float &tiempoAnterior_, float &tiempoTranscurrido_, int &pasaronXsegundos_)
{
  if(estado_!=estadoCheck_)
    {
      tiempoInicial_ = 0;
      tiempoAnterior_ = 0;
      tiempoTranscurrido_ = 0;

      //Serial.println("CAMBIOOOOOOOOOOOO");COMENTADO RECIENTEMENTE
      }

  //Serial.println("T TRANSCURRIDO: "+ String(tiempoTranscurrido_));COMENTADO RECIENTEMENTE
  tiempoAnterior_ = tiempoInicial_;
  tiempoInicial_ = millis()/1000;
    
  if(estado_ == estadoCheck_)
  {
    tiempoTranscurrido_ += tiempoInicial_ - tiempoAnterior_;
  }

  //Serial.println(estado_);COMENTADO RECIENTEMENTE
  if((int)tiempoTranscurrido_%pasaronXsegundos_ == 0 && (int)tiempoTranscurrido_ != 0)
  {
    return true;
    }
  else if((int)tiempoTranscurrido_%pasaronXsegundos_ != 0 || (int)tiempoTranscurrido_ == 0)
  {
    return false;
    }
  else
  {
    return false;
    }
}

void agregarSustancia(float porcentaje)
{
  rotacion += 10*porcentaje/750;//10% de cien 
  //Serial.println("SE AGREGO LA SUSTANCIA");COMENTADO RECIENTEMENTE
}
