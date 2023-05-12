
#include "pitches-2.h"

typedef struct {
 // Declaramos alguna variables
  long sequence[15];             // Array que alberga la secuencia
  int contador = 0;              // Contador
  long input = 5;                // Indicador de boton pulsado
  int wait = 500;                // Retraso segun la secuencia se incrementa
  int puntuacion_maxima = 10;    // Puntuación máxima donde acaba el juego
  int nivel_1 =2;
  int nivel_2 =4; 
  int nivel_3 = 6;
  int nivel_4 = 8;
  }FSM_T;

FSM_T Simon_0;
FSM_T Simon_1;



 // Declaramos los pins de salida para los LED
  const int led_rojo = 2;         
  const int led_azul = 3;
  const int led_amarillo = 4;
  const int led_verde = 5;
  
 // Declaramos el pin para el zumbador piezoelectrico
  const int Pin_zumbador = 6;  

  
 // Declaramos los pins de salida para los botones
  const int boton_rojo = 9;      
  const int boton_azul = 10;
  const int boton_amarillo = 11; 
  const int boton_verde = 12;   
 


  void mostrar_boton_correcto( FSM_T  *);
  void resetcontador( FSM_T  *);
  void mostrar_secuencia( FSM_T  *);
  void leer_secuencia( FSM_T  *);  
  void Play_Tone( FSM_T *);  
  void flash_rojo( FSM_T  );
  void flash_azul( FSM_T  );
  void flash_amarillo( FSM_T  );
  void flash_verde( FSM_T  );

  void setup(void)
{
   // Configuramos los pines de los leds y del zumbador como salidas
  pinMode(led_rojo, OUTPUT);      
  pinMode(led_verde, OUTPUT); 
  pinMode(led_amarillo, OUTPUT); 
  pinMode(led_azul, OUTPUT); 
  pinMode(Pin_zumbador, OUTPUT);

    
 // Configuramos los pines de los botones como entradas
  pinMode(boton_rojo, INPUT);    
  pinMode(boton_verde, INPUT);
  pinMode(boton_amarillo, INPUT);
  pinMode(boton_azul, INPUT);
    
 // Iniciamos las resistencias PullUp internas para los botones
  digitalWrite(boton_rojo, HIGH);
  digitalWrite(boton_verde, HIGH);
  digitalWrite(boton_amarillo, HIGH);
  digitalWrite(boton_azul, HIGH);
    
   /*Reproduce melodia de inicio al empezar el juego*/
    Melodia_Inicio(&Simon_0);


} /* setup */


void loop(void)
{

  mostrar_secuencia(&Simon_0);
  leer_secuencia(&Simon_0);
  delay(500);// Espera 1 segundo
  
  }/*loop*/


   // Funcion para definir las notas segun la duración y el tono
  void playtone(FSM_T   *fsm_ptr, int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone *2) {
      digitalWrite(Pin_zumbador, HIGH);
      delayMicroseconds(tone);
      digitalWrite(Pin_zumbador, LOW);
      delayMicroseconds(tone);
    }
  }


  
 // Funciones para encender los leds y reproducir el tono correspondiente
  void flash_rojo(FSM_T  *fsm_ptr) {
  digitalWrite(led_rojo, HIGH);
  playtone(&Simon_0, 2273,fsm_ptr->wait);            
  digitalWrite(led_rojo, LOW);
  }
  
  void flash_azul(FSM_T  *fsm_ptr) {
  digitalWrite(led_azul, HIGH);
  playtone(&Simon_0, 1700,fsm_ptr->wait);            
  digitalWrite(led_azul, LOW);
  }
  
  void flash_amarillo(FSM_T  *fsm_ptr) {
  digitalWrite(led_amarillo, HIGH);
  playtone(&Simon_0, 1275,fsm_ptr->wait);             
  digitalWrite(led_amarillo, LOW);
  } 
  
  void flash_verde(FSM_T  *fsm_ptr) {
  digitalWrite(led_verde, HIGH);
  playtone(&Simon_0, 1136,fsm_ptr->wait);             
  digitalWrite(led_verde, LOW);
  }


   // Funcion para mostrar que botón se tenia que pulsar en caso de error del jugador
  void mostrar_boton_correcto(FSM_T   *fsm_ptr, long led) {
    switch (led) {
        case 0:
          flash_rojo(&Simon_0);
          break;
        case 1:
          flash_verde(&Simon_0);
          break;
        case 2:
          flash_amarillo(&Simon_0);
          break;
        case 3:
          flash_azul(&Simon_0);
          break;
      }
      delay(50);
  }


   // Reseteamos contadores
  void resetcontador(FSM_T   *fsm_ptr) {
  fsm_ptr->contador = 0;
  fsm_ptr->wait = 500;
  }
  
//  Funcion para crear y reproducir los patrones
  void mostrar_secuencia(FSM_T   *fsm_ptr) {
 // Con esto hacemos que la función Random sea aun mas aleatoria
  randomSeed(analogRead(8));
    
  fsm_ptr->sequence[fsm_ptr->contador] = random(4);       
    for ( int i = 0; i < fsm_ptr->contador; i++) {  
      mostrar_boton_correcto(&Simon_0, fsm_ptr->sequence[i]);             
    }
  fsm_ptr->wait = 500 - (fsm_ptr->contador * 15);
  fsm_ptr->contador++;                          
  }


  // Funcion para leer los botones que pulsa el jugador
 void leer_secuencia(FSM_T   *fsm_ptr) {
   for (int i=1; i < fsm_ptr->contador; i++) {              
      while (fsm_ptr->input==5){                          
        if (digitalRead(boton_rojo) == LOW) {    
          fsm_ptr->input = 0;
        }
        if (digitalRead(boton_verde) == LOW) {  
          fsm_ptr->input = 1;
        }
        if (digitalRead(boton_amarillo) == LOW) {
          fsm_ptr->input = 2;
        }
        if (digitalRead(boton_azul) == LOW) {   
          fsm_ptr->input = 3;
        }
      }
    
  if (fsm_ptr->sequence[i-1] == fsm_ptr->input) {              
        mostrar_boton_correcto(&Simon_0, fsm_ptr->input);                     
        if (i == fsm_ptr->nivel_1) { 
          //Melodia_Inicio(&Simon_0); 
          fsm_ptr->wait = 400 - (fsm_ptr->contador * 15);
            
                       
        }else if(i == fsm_ptr->nivel_2){
           Melodia_Nivel(&Simon_0); 
        fsm_ptr->wait = 300 - (fsm_ptr->contador * 15);         
          }
          else if(i == fsm_ptr->nivel_3){
           Melodia_Nivel(&Simon_0); 
        fsm_ptr->wait = 200 - (fsm_ptr->contador * 15);         
          }
          else if(i == fsm_ptr->nivel_4){
           Melodia_Nivel(&Simon_0); 
        fsm_ptr->wait = 100 - (fsm_ptr->contador * 15);         
          }
         else if(i == fsm_ptr->puntuacion_maxima){
           Melodia_Nivel(&Simon_0); 
        Melodia_Inicio(&Simon_0);         
          }
      } else if(fsm_ptr->sequence[i-1] != fsm_ptr->input){
      Melodia_Loser(&Simon_0);                
          delay(500);
          mostrar_boton_correcto(&Simon_0, fsm_ptr->sequence[i-1]);                 
          mostrar_boton_correcto(&Simon_0, fsm_ptr->sequence[i-1]);                 
          delay(1000);
          //melodia de perdedor
          resetcontador(&Simon_0);                          
      } 
    fsm_ptr->input = 5; 

      
    }
 }

/*************** MELODIAS *****************/
void Melodia_Inicio(FSM_T  *fsm_ptr)
  {
      digitalWrite(led_rojo, HIGH);     
       playtone(&Simon_0, D3,300); 
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH);  
       playtone(&Simon_0, F3,200);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, D3,100);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, D3,100);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, G3,100);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, D3,100);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, C3,200);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, D3,300);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, G3,200);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, D3,100);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, D3,100);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, AS3,200);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, A3,200);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, F3,200);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, D3,200);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, A3,200);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, F3,200);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, D3,200);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, A3,200);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, D4,200);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, D3,200);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, C3,200);
       digitalWrite(led_verde, LOW);
       digitalWrite(led_amarillo, HIGH); 
       playtone(&Simon_0, C3,200);
       digitalWrite(led_amarillo, LOW);
       digitalWrite(led_azul, HIGH); 
       playtone(&Simon_0, A2,200);
       digitalWrite(led_azul, LOW);
       digitalWrite(led_rojo, HIGH); 
       playtone(&Simon_0, E3,200);
       digitalWrite(led_rojo, LOW);
       digitalWrite(led_verde, HIGH); 
       playtone(&Simon_0, D3,400);
       digitalWrite(led_verde, LOW); 
  }
  


void Melodia_Loser(FSM_T  *fsm_ptr)
  {
       digitalWrite(led_rojo, HIGH);
       playtone(&Simon_0, C5,800); 
       digitalWrite(led_verde, HIGH);
       playtone(&Simon_0, AS4,800);
       digitalWrite(led_amarillo, HIGH);
       playtone(&Simon_0, GS4,800);
       digitalWrite(led_azul, HIGH);
       playtone(&Simon_0, G4,800);
       digitalWrite(led_rojo, LOW);
       playtone(&Simon_0, GS4,800);
       digitalWrite(led_verde, LOW);
       playtone(&Simon_0, G4,800);
       digitalWrite(led_amarillo, LOW);
       playtone(&Simon_0, F4,450);
       digitalWrite(led_azul, LOW);
       playtone(&Simon_0, DS4,800);    
  }

  void Melodia_Nivel(FSM_T   *fsm_ptr)
    {
      digitalWrite(led_rojo, HIGH);
      digitalWrite(led_verde, HIGH);
    playtone(&Simon_0, F4,150); 
     digitalWrite(led_rojo, LOW);
     digitalWrite(led_verde, LOW);
    playtone(&Simon_0, GS4,150); 
    digitalWrite(led_rojo, HIGH);
     digitalWrite(led_verde, HIGH);
    playtone(&Simon_0, AS4,150); 
    digitalWrite(led_rojo, LOW);
     digitalWrite(led_verde, LOW);
    playtone(&Simon_0, AS4,300); 
    digitalWrite(led_azul, HIGH);
     digitalWrite(led_amarillo, HIGH);
    playtone(&Simon_0, GS4,150); 
    digitalWrite(led_azul, LOW);
     digitalWrite(led_amarillo, LOW);
    playtone(&Simon_0, QT,2000);
    digitalWrite(led_azul, HIGH);
     digitalWrite(led_amarillo, HIGH); 
    playtone(&Simon_0, F4,150); 
    digitalWrite(led_azul, LOW);
     digitalWrite(led_amarillo, LOW);
    playtone(&Simon_0, GS4,150); 
    digitalWrite(led_rojo, HIGH);
     digitalWrite(led_amarillo, HIGH);
    playtone(&Simon_0, AS4,150); 
    digitalWrite(led_rojo, LOW);
     digitalWrite(led_amarillo, LOW);
    playtone(&Simon_0, AS4,150); 
    digitalWrite(led_azul, HIGH);
     digitalWrite(led_verde, HIGH);
    playtone(&Simon_0, GS4,150); 
    digitalWrite(led_azul, LOW);
     digitalWrite(led_verde, LOW);
    playtone(&Simon_0, F4,150); 
    digitalWrite(led_rojo, LOW);
    playtone(&Simon_0, DS4,150);
     digitalWrite(led_rojo, LOW);
     digitalWrite(led_verde, HIGH); 
    playtone(&Simon_0, F4,150); 
     digitalWrite(led_verde, LOW);
     digitalWrite(led_amarillo, HIGH);
    playtone(&Simon_0, QT,1000); 
     digitalWrite(led_amarillo, LOW);
     digitalWrite(led_azul, HIGH);
    playtone(&Simon_0, AS4,150); 
     digitalWrite(led_azul, LOW);
    playtone(&Simon_0, GS4,150);
     digitalWrite(led_rojo, HIGH);
    digitalWrite(led_verde, HIGH);
      digitalWrite(led_azul, HIGH);
     digitalWrite(led_amarillo, HIGH); 
    playtone(&Simon_0, F4,150); 
         digitalWrite(led_rojo, LOW);
     digitalWrite(led_verde, LOW);
      digitalWrite(led_azul, LOW);
     digitalWrite(led_amarillo, LOW); 
    playtone(&Simon_0, DS4,150); 
         digitalWrite(led_rojo, HIGH);
     digitalWrite(led_verde, HIGH);
      digitalWrite(led_azul, HIGH);
     digitalWrite(led_amarillo, HIGH); 
    playtone(&Simon_0, F4,150); 
         digitalWrite(led_rojo, LOW);
     digitalWrite(led_verde, LOW);
      digitalWrite(led_azul, LOW);
     digitalWrite(led_amarillo, LOW); 

    }

  

  





     
  
