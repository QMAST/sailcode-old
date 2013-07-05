
char msg[255];
char buf;
void setup() {
    Serial.begin(115200);
    Serial1.begin(4800); 
    pinMode(13, OUTPUT);
}

void loop() {
    
    
    //readLine();
    if(Serial1.available()>0) {
        digitalWrite(13, HIGH);
        buf = Serial1.read();
        Serial.print(buf);
    } else {
        digitalWrite(13, LOW);
        Serial.print('.'); 
      delay(500);  
    }
}

/*
void readLine(){ 
 //Reads a single line from the serial1 port.Puts it into msg.
    unsigned long startTime = millis();
    int i=0;
    char buf = '\0';
    while( (millis()-startTime) < 1000) {
         if(Serial1.available()>0) {
              buf = Serial1.read();
              Serial.print(buf)
              if(buf=='\r' || buf=='\n'){ 
                   break;   
              }
              
              msg[i] = buf;
              i++;
         }   
    }
    
    msg[i] = '\0';
    return;    
}
*/
