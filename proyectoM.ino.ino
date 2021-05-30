#include<AFMotor.h>
#include<Servo.h>

double Cuenta_;
double Velocidad_inhalaci_C3_B3n;
double Tiempo_Inalacion;
double Velocidad_Exhalaci_C3_B3n;
double Tiempo_Salida_Dijital;
double Tiempo_Exalacion;
double neutro;
double tiempo_apertura_Servo;
double tiempo_espera_retardo_alto_mottor;
double potenciometro = 0 , perillaI = 3, perillaE = 6;
double a = 1,b = 2,c = 4,d = 5,e = 7,f = 8,g = 10;



const int botonIncremento = 12;



int tiempoAntirebote = 10; 
int EstadoIncremento = 0;
int Estadodecremento = 0;
int estadoAnteriorIncremento = 0;
int EstadoDecrementoAnterior = 0;
int contador;
int estadoBotonAnterior;
int EstadoBotonIncremento;
int EstadoBotonDecremento;
int cuenta;
 
boolean b_On_Off_Servo;
boolean b_Encender_Motor;
boolean b_Gatillo;
boolean b_Anular_retardo_Inspiracion_____;
boolean b_Anular_Retardo_Exhalacion____;
boolean b_Salida_Digital_Pin_9;
boolean estado;
boolean estadoAnterior;

unsigned long time_timer=millis();

AF_Stepper motorshield_stepper_2(4096 ,2);

unsigned long task_time_ms=0;

Servo servo_10;

unsigned long task_time_ms2=0;

void Reset_Cronometro() {
  time_timer=millis();
}

void Adelante() {
  motorshield_stepper_2.setSpeed(Velocidad_inhalaci_C3_B3n);
  motorshield_stepper_2.step(500,FORWARD,SINGLE);
}

void atras() {
  motorshield_stepper_2.setSpeed(Velocidad_Exhalaci_C3_B3n);
  motorshield_stepper_2.step(500,BACKWARD,SINGLE);
}

void salida_Dijital_Pin9() {
  if((millis()-task_time_ms)>=Tiempo_Salida_Dijital){
    task_time_ms=millis();
    if ((b_Gatillo == false)) {
      digitalWrite(13, HIGH);

    }
    neutro = (neutro + 1);
    if ((neutro >= 2)) {
      neutro = 0;
      digitalWrite(13, LOW);

    }
  }
}

void Servo_Motor() {
  if ((b_Gatillo == true)) {
    servo_10.write(90);

  }
  if((millis()-task_time_ms2)>=tiempo_apertura_Servo){
    task_time_ms2=millis();
    servo_10.write(0);
  }  
}

void Cambiar_Velocidad(){
  
   pinMode(perillaI,OUTPUT);
   pinMode(perillaE,OUTPUT);
   
    
   Velocidad_inhalaci_C3_B3n = analogRead(potenciometro) / 4;
   Velocidad_Exhalaci_C3_B3n = analogRead(potenciometro) / 4;

   analogWrite(perillaI,Velocidad_inhalaci_C3_B3n);
   analogWrite(perillaE,Velocidad_Exhalaci_C3_B3n);

   delay(50);
}
boolean antiRebote(int pin){

    do{
      estado = digitalRead(pin);
      if(estado != estadoAnterior){

        contador = 0;
        estado = estadoAnterior;
        
      }else{

         contador++;
        
      }
      delay(10);
      
    }while(contador < tiempoAntirebote);

    return estado;
} 
void actualizarNumero(){

     switch(cuenta){

      case 0 :
       digitalWrite(a,HIGH);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,HIGH);
       digitalWrite(e,HIGH);
       digitalWrite(f,HIGH);
       digitalWrite(g,LOW);
       delay (500);
       break;


      case 1 :

        digitalWrite(a,LOW);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,LOW);
        digitalWrite(e,LOW);
        digitalWrite(f,LOW);
        digitalWrite(g,LOW);
        delay (500);
        break;



      case 2 :

      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,LOW);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,LOW);
      digitalWrite(g,HIGH);
      delay (500);
      break;



      case 3 :

       digitalWrite(a,HIGH);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,HIGH);
       digitalWrite(e,LOW);
       digitalWrite(f,LOW);
       digitalWrite(g,HIGH);
       delay (500);
       break;




      case 4 :

      
       digitalWrite(a,LOW);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,LOW);
       digitalWrite(e,LOW);
       digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
       delay (500);
       break;



      case 5 :


       digitalWrite(a,HIGH);
       digitalWrite(b,LOW);
       digitalWrite(c,HIGH);
       digitalWrite(d,HIGH);
       digitalWrite(e,LOW);
       digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
       delay (500);
       break;



      case 6 :


       digitalWrite(a,HIGH);
       digitalWrite(b,LOW);
       digitalWrite(c,HIGH);
       digitalWrite(d,HIGH);
       digitalWrite(e,HIGH);
       digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
       delay (500);
       break;




      case 7 :


       digitalWrite(a,HIGH);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,LOW);
       digitalWrite(e,LOW);
       digitalWrite(f,LOW);
       digitalWrite(g,HIGH);
       delay (500);
       break;



      case 8 :

       digitalWrite(a,HIGH);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,HIGH);
       digitalWrite(e,HIGH);
       digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
       delay (500);



      case 9 :


       digitalWrite(a,HIGH);
       digitalWrite(b,HIGH);
       digitalWrite(c,HIGH);
       digitalWrite(d,LOW);
       digitalWrite(e,LOW);
       digitalWrite(f,HIGH);
       digitalWrite(g,HIGH);
       delay (500);
       break;
     }
}

void setup(){

  Serial.begin(9600);
  pinMode(perillaI,OUTPUT);
  pinMode(perillaE,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(a,OUTPUT );
  pinMode(b,OUTPUT );
  pinMode(c,OUTPUT );
  pinMode(d,OUTPUT );
  pinMode(e,OUTPUT );
  pinMode(f,OUTPUT );
  pinMode(g,OUTPUT );
  servo_10.attach(10);
 

  Cuenta_ = 0;
  // tiempo en segundos del movimiento del motor atras
  Tiempo_Inalacion = 2;
  // tiempo en segundos del movimiento del motor adelante
  Tiempo_Exalacion = 2;
  Velocidad_inhalaci_C3_B3n = 8;
  Velocidad_Exhalaci_C3_B3n = 8;
  tiempo_espera_retardo_alto_mottor = 0.5;
  tiempo_apertura_Servo = 300;
  Tiempo_Salida_Dijital = 1000;

}


void loop()
{

    if ((b_Encender_Motor == true)) {
      if ((b_Gatillo == true)) {
        if ((((millis()-time_timer)/1000) == Tiempo_Inalacion)) {
          Reset_Cronometro();
          b_Gatillo = false;

        } else {
          if ((b_Anular_retardo_Inspiracion_____ == true)) {
            if ((((millis()-time_timer)/1000) >= tiempo_espera_retardo_alto_mottor)) {
              Adelante();

            }

          } else {
            Adelante();

          }

        }

      }
      if ((b_On_Off_Servo == true)) {
        Servo_Motor();

      }

    }
    b_On_Off_Servo = true;
    b_Encender_Motor = true;
    b_Anular_retardo_Inspiracion_____ = true;
    b_Anular_Retardo_Exhalacion____ = true;
    b_Salida_Digital_Pin_9 = true;
    if ((b_Encender_Motor == true)) {
      if ((b_Gatillo == false)) {
        if ((((millis()-time_timer)/1000) == Tiempo_Exalacion)) {
          Reset_Cronometro();
          b_Gatillo = true;

        } else {
          if ((b_Anular_Retardo_Exhalacion____ == true)) {
            if ((((millis()-time_timer)/1000) >= tiempo_espera_retardo_alto_mottor)) {
              atras();

            }

          } else {
            atras();

          }

        }

      }
      if ((b_Salida_Digital_Pin_9 == true)) {
        salida_Dijital_Pin9();

      }

    }
    
  

   EstadoBotonIncremento = digitalRead(perillaI);

   if(EstadoIncremento != estadoAnteriorIncremento){
    if(antiRebote(perillaI)){
      
      cuenta++;

      if(cuenta > 9){
        cuenta = 9; 
      }else if(cuenta < 0){
        cuenta = 0;
      }
    }

    EstadoBotonIncremento = EstadoBotonDecremento;
   }


    
   Velocidad_inhalaci_C3_B3n = analogRead(potenciometro) / 4;
   Velocidad_Exhalaci_C3_B3n = analogRead(potenciometro) / 4;

   analogWrite(perillaI,Velocidad_inhalaci_C3_B3n);
   analogWrite(perillaE,Velocidad_Exhalaci_C3_B3n);

   delay(50);

   actualizarNumero();
   
}
  
