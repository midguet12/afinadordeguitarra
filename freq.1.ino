
void setup() {
  // put your setup code here, to run once:
  analogRead(A0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int freq = analogRead(A0);
  Serial.println(freq);
}
