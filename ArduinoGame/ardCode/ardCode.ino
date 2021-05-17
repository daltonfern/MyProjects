int FA = A0;
int FD = 8;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(FA, INPUT);
pinMode(FD, INPUT);
digitalWrite(FD, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
int fireState = digitalRead(FD);
if ( fireState == HIGH) {
  Serial.println("Fire is on");
}
}
