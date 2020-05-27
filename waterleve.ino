void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);//trig
  pinMode(6,INPUT);//echo
  pinMode(12,OUTPUT);//relay
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9,LOW);
  delayMicroseconds(2);
  digitalWrite(9,HIGH);
  delayMicroseconds(10);
  digitalWrite(9,LOW);
  int dur;
  dur=pulseIn(6,HIGH);
  float distance=(0.034*dur)/2; 
  float per=(distance/12); 
  Serial.print(per*100);
  Serial.println("% filled");
  delay(1000);
  if (per*100>90)
  {
    digitalWrite(12,HIGH);
    Serial.println("tank is empty");
  }
  if (per*100<10)
  {
    digitalWrite(12,LOW);
    Serial.println("tank if full");
  }

}
