#include <Arduino.h>
#include <ashcon.h>

ashcon* Console;

void setup() {
    Serial.begin(115200);
    Console = new ashcon(&Serial);
    Console->user_function_register("test", &testFcn);    
}

void loop() {
       Console->command_prompt();
}


int testFcn(int argc, char* argv[]) {
     Serial.println("This is still working.");
      
  return 0;   
}
