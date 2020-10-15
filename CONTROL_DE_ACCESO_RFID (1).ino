/*
***********************************************
DISEÑO: INGENIERO JORGE CADAVID MEKATRONIK 2018
***********************************************
  PINES PARA ARDUINO UNO Y MEGA
//--------------------------------
MODULO RC522    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
//--------------------------------
*******************************************
*/

// Incluimos la libreria de comunicación SPI
#include <SPI.h>
// Incluimos la libreria para el control del sistema RFID
#include <MFRC522.h>

//Definimos para el RFID,DIO usado para el SDA (D9) y RST (D8). 
#define SDA_DIO 9
#define RESET_DIO 8

//Creamos una instanca de la libreria RFID
//RFID RC522(SDA_DIO, RESET_DIO); 

//Declaración de Variables para uso en el programa
int conteo_visitas=0;//

void setup()
{ 
  //inicializamos la comunicación Serial
  Serial.begin(9600);
    
  //inicializamos la comunicación SPI
  SPI.begin(); 
  //inicializamos la comunicación RFID
  RC522.init();
  
  //Declaramos los pines de Salida para el TIP122 Y el Led
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
}

void loop()
{ 
  //Definimos que acciones realizar si la tarjeta es detectada
  if (RC522.isCard())
  {   
    RC522.readCardSerial();
            
    //Variable que incrementa con cada paso de la tarjeta RFID             
    conteo_visitas++;
    
    //Envío los datos recibidos por la tarjeta RFID
    Serial.print("Visita Numero= ");
    Serial.println(conteo_visitas); 
    Serial.println("Codigo de Identificacion Correcto= ");
        
    //Envía el codigo de la tarjeta RFID   
    for(int i=0;i<5;i++)
    {
     
     //Formato decimal
      Serial.print(RC522.serNum[i],DEC);
     
    //Formato Hexadecimal
    //Serial.print(RC522.serNum[i],HEX);
     }
       Serial.println();
       Serial.println("Apertura de Puerta....... ");
         
    //Secuencia de activación de la puerta
      digitalWrite(2,HIGH);//Activo el MOTOR DC
      digitalWrite(3,HIGH);//Enciendo el Led
      delay(3000);//Tiempo de Apertura
      digitalWrite(2,LOW);//Desactivo el MOTOR DC
      digitalWrite(3,LOW);//Apago el Led
       
     //imprime 2 renglones en blanco para mejor visualización en pantalla
      Serial.println();
      Serial.println();
          
}          
    //Retardo para estabilización del sistema
    delay(300);
        
}
