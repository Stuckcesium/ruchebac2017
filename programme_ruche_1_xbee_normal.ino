#include <SoftwareSerial.h>
SoftwareSerial XBEE(2,3);

// Affectation des broches du micro-contrôleur



// Définition des variables

String message;  // chaîne de caractère transmise ( reçue ou émise )
int id;
long temperature;           //Valeurs
long humidity;
long masse;
boolean etat_mesure;


void setup()
{
  XBEE.begin(9600);
  Serial.begin(9600);
  Serial.flush();          
}

void loop()
{
  lire_message();
  decode_message();
  Serial.println(etat_mesure);
  if  (etat_mesure==1)
  {
    lire_mesures();
    //code_message();
    ecrire_message();
    etat_mesure = 0;
  }
  delay (5000);
}


void lire_message()                         
{
  message = "";    
  while (XBEE.available() != 0)          
    {
     message = String(message+char(XBEE.read()));               
    }
}


void decode_message()                                 
{
  if(message.startsWith("?"))                     
  {
    etat_mesure = 1;
  }
}

void lire_mesures()
{
  id = 1;
  masse = random(10,70);
  temperature = random(0,50);
  humidity = random(0,100);
}


void ecrire_message()
{
   delay(id * 3000);
  XBEE.println(protocol());
}

String protocol() {
  return "D" + String(id) + ";"  + String(masse) + ";" + String(temperature) + ";" + String(humidity) + "#";
}
  