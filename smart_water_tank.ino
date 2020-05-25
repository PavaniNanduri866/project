
void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(6,INPUT);
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
  int distance=(0.034*dur)/2;
  Serial.println(distance);
  delay(1000);
  if (distance<=10)
  {
    
    Serial.println("tank is full");
  }
  if (distance>=49)
  {
    Serial.println("tank is empty");
  }
}
