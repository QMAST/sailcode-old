void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    Serial2.begin(9600);
    
    pinMode(28, OUTPUT);
    pinMode(29, OUTPUT);
    digitalWrite(28, LOW);
    digitalWrite(29, LOW);
    Serial2.println("@B6=2*7B");//Set the baud rate to 4800BPS
    Serial2.println("@F28.6=1*58");//Reset the compass.
    
    delay(400);
    while(Serial1.available()>0){
         Serial.print(Serial1.read());   
    }
    Serial.println("End");
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
