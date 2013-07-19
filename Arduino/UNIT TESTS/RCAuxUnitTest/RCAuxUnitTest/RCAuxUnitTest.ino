// Testing RC auxilary values

#include <Arduino.h>
#include <rc.h>

RC* control;

void setup() {
   Serial.begin(115200);
  
   
  
}

void loop() {
  
  int aux = control->getValueAux();
  Serial.print("Aux is: ");
  Serial.println(aux);
  
}
