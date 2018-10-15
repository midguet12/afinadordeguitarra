/*
FRECUENCIMETRO

 Este frecuencímetro puede leer frecuencias de 1Hz a 3Khz.
 
 El error puede rondar el +/- 1Hz.

 Muestra las lecturas a través del puerto serie a intervalos de 1 segundo.
 
 Este frecuencímetro dispone de un ajuste automático de ganancia, que le permite ajustarse a la mayor señal y eliminar así, lecturas correspondientes a ruidos de fondo de algún tipo.

PLATAFORMA

Este programa a sido probado en un arduino duemilanove y a sido comprobado su correcto funcionamiento.

CONEXIONADO

 El pin analógico CERO, es el pin de entrada de frecuencias. 
 
Si se quieren medir corrientes alternas, será necesario poner dos resistencias de entorno a 1000 ohmios en serie y conectar un extremo de las resistencias en serie a masa y el otro extremo al polo positivo. De entre las dos resistencias puestas en serie, se conectaría al pin cero analógico y del pin cero analógico sacaríamos un terminal, que sería por el que entraría la señal a medir. Las resistencias se conectan de este modo para hacer un divisor de tensión, que haga que la entrada analógica del arduino esté a un voltaje intermedio entre masa y el positivo. También se podría poner en serie un condensador entre el pin cero analógico y el terminal por el que va a entrar la señal alterna, para separar el arduino de las corrientes continuas.

NOTA IMPORTANTE:

 La entrada analógica solo puede entrar una señal de como mucho 5v, de lo contrario, podríamos romper el arduino. Se podría poner un diodo zener de algo menos de 5v, para cortocircuitar los picos te tensión superiores a 5V, entre el terminal cero analógico y masa.

AUTOR: Mario R.P - mariorp@terra.es - 13-6-2012

*/

long rango=2; // este es el rongo por el que se disparará la salida 2 y pasa a estado lógico 1
long ultimamedicion; // contiene el valor de la última medición que disparó a lógico 1, la salida 2
int ciclo=0; // 1=alto 0=bajo
int cambiodeciclo=0;
int picodetension;
int valledetension=1023;
long contadorvisualizacion;
long contadorciclo;
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;
int led6 = 13;
void setup() {

 Serial.begin(9600);
 pinMode(A0, INPUT); // Se establece el pin analógico 0 como pin de lectura de datos.
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);
 pinMode(led4, OUTPUT);
 pinMode(led5, OUTPUT);
 pinMode(led6, OUTPUT);   
}


void loop() {
 
 long sensorValue = analogRead(A0); // Se vuelca a la varibla sensorValue el valor de la tensión medida por el pin 0 analógico
 
   if (micros()>contadorvisualizacion+1000000) // Muestra por el puerto serie los resultados, transcurrido un segundo
   
   {
     
        // AQUÍ SE IMPRIME EN EL PUERTO SERIE LOS RESULTADOS

        Serial.print(" Hz=");
        Serial.println(contadorciclo);
        
        rango=(2+((picodetension-valledetension)/5)); // SE CALCULA EL GANGO MÁS ADECUADO PARA LA SEÑAL, CON EL FIN, DE REDUCIR ERRORES EN SEÑALES CON RUIDO DE FONDO
        contadorvisualizacion=micros();//SE ASIGNA A LA VARIABLE CONTADORVISUALIZACIÓN EL TIEMPO EN MICROSENGUNDOS QUE LLEVA EL PROGRAMA EN EJECUCIÓN
        picodetension=sensorValue;//SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
        valledetension=sensorValue;//SE ASIGNA A LA VALLEDETENSION EL VALOR DE LA TENSIÒN LEIDA POR EL PUERTO ANALÓGICO CERO
        contadorciclo=0; // SE PONE A CERO LOS CICLOS CONTADOS O HERCIOS.
   }   
   



 if (sensorValue >= ( ultimamedicion+rango) ) // La salida 2 pasa a 1 logico si la tensión medida en la entrada analógica 0 es mayor que la anterior lectura + latensión de RANGO

 {

   ultimamedicion = sensorValue;  // SE ASIGANA A LA VARIABLE ULTIMAMEDICION EL VALOR LEIDO POR LA ENTRADA ANALÓGICA CERO 
   ciclo=1;
   
   if (sensorValue>picodetension) // SI LA TENSIÓN MEDIDA POR LA ENTRADA CERO, ES LA MAYOR DETECTADA, SE ASIGNA A LA VARIABLE PICODETENSIÓN EL VALOR LEYDO POR AL ENTRADA CERO ANALÓGICA
   
   {
   picodetension=sensorValue; // SE ASIGNA EL VALOR LEYDO POR LA ENTRADA CERO ANALÓGICA A LA VARIABLE PICODETENSIÓN.
   }
   
 }
   

 
 if (sensorValue <= ( ultimamedicion-rango))  // La salida 2 pasa a 1 lógico si la tensión medida en la entrada analógica 0 es menor que la anterior lectura - la tensión de RANGO

 {

   ultimamedicion = sensorValue; // SE ASIGNA A LA VARIABLE ULTIMAMEDICIÓN LA LECTURA MEDIDA POR EL PUERTO ANALÓGICO CERO
   ciclo=0; // EL CICLO SE PONE A CERO, ES DECIR, QUE EL VOLTAJE EMPIEZA A BAJAR DESDE EL PICO DE TENSIÓN MÁS ALTA
   
   if (sensorValue<valledetension) // SE CUMPLE LA CONDICIÓN SI LA TENSIÓN DETECTADA POR EL PUERTO ANALÓGICO CERO ES MENOR QUE LA CONTENIDA EN LA VARIABLE VALLEDETENSIÓN
   {
   valledetension=sensorValue; //Se asigna a la variable valledetensión el valor medido por la entrada analógica cero
   }
   
 }
   
 
if (ciclo==1 && cambiodeciclo==0)
   
   {
     cambiodeciclo=1;
     contadorciclo++;
   }
   
if (ciclo==0 && cambiodeciclo==1)
   
   {
     cambiodeciclo=0;
   }

if ((contadorciclo>320)&&(contadorciclo<339)) //PRIMERA      
   {
   digitalWrite(led1, 1);
   }
else
  {
    digitalWrite(led1, 0);
  }

  if ((contadorciclo>238)&&(contadorciclo<254))      //SEGUNDA
   {
   digitalWrite(led2, 1);
   }
else
  {
    digitalWrite(led2, 0);
  }

  if ((contadorciclo>190)&&(contadorciclo<201))       //TERCERA
   {
   digitalWrite(led3, 1);
   }
else
  {
    digitalWrite(led3, 0);
  }

  if ((contadorciclo>142)&&(contadorciclo<151))      //CUARTA
   {
   digitalWrite(led4, 1);
   }
else
  {
    digitalWrite(led4, 0);
  }

  if ((contadorciclo>105)&&(contadorciclo<115))       //QUINTA
   {
   digitalWrite(led5, 1);
   }
else
  {
    digitalWrite(led5, 0);
  }

  
  //if (contadorciclo>75)&&(contadorciclo<85)       
  if ((contadorciclo>75)&&(contadorciclo<85))  //SEXTA
   {
   digitalWrite(led6, 1);
   }
else
  {
    digitalWrite(led6, 0);
  }

  

}


