#define LENGTH 512

byte rawData[LENGTH];
int count;

// Sample Frequency in kHz
const float sample_freq = 9070;//9200;

int ledPinEh = 8;
int ledPinB = 9;
int ledPinG = 10;
int ledPinD = 11;
int ledPinA = 12;
int ledPinEl = 13;
int ledPinRedRight = 2;
int ledPinGreen = 5;
int ledPinRedLeft = 7;
int len = sizeof(rawData);
int i,k;
long sum, sum_old;
int thresh = 0;
float freq_per = 0;
byte pd_state = 0;

void setup(){
 //analogReference(EXTERNAL); // Connect to 3.3V
 analogRead(A0);
 Serial.begin(115200);
 count = 0;
 pinMode(ledPinEh, OUTPUT);
 pinMode(ledPinB, OUTPUT);
 pinMode(ledPinG, OUTPUT);
 pinMode(ledPinD, OUTPUT);
 pinMode(ledPinA, OUTPUT);
 pinMode(ledPinEl, OUTPUT);
 pinMode(ledPinRedRight, OUTPUT);
 pinMode(ledPinRedLeft, OUTPUT);
 pinMode(ledPinGreen, OUTPUT);
}




void loop(){
 
 if (count < LENGTH) {
 count++;
 rawData[count] = analogRead(A0)>>2;
 }
 else {
 sum = 0;
 pd_state = 0;
 int period = 0;
 for(i=0; i < len; i++)
 {
 // Autocorrelation
 sum_old = sum;
 sum = 0;
 for(k=0; k < len-i; k++) sum += (rawData[k]-128)*(rawData[k+i]-128)/256;
 // Serial.println(sum);
 
 // Peak Detect State Machine
 if (pd_state == 2 && (sum-sum_old) <=0) 
 {
 period = i;
 pd_state = 3;
 }
 if (pd_state == 1 && (sum > thresh) && (sum-sum_old) > 0) pd_state = 2;
 if (!i) {
 thresh = sum * 0.5;
 pd_state = 1;
 }
 }
 // for(i=0; i < len; i++) Serial.println(rawData[i]);
 // Frequency identified in Hz
 if (thresh >100) {
 freq_per = sample_freq/period;

if (freq_per<400){
 Serial.println(freq_per);
 
 //Elow Note 83.21Hz
 if ( ( (freq_per >75)&&(freq_per < 85) )|| ( (freq_per>159)&&(freq_per<170) ) ){ // For Elow string
 digitalWrite(ledPinEl, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<80.4||(freq_per<161.91&&freq_per>159)){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if ((freq_per>84.4&&freq_per < 85)||(freq_per>167.91&&freq_per<170)){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=80.4&&freq_per<=84.4)||(freq_per>=161.91&&freq_per<=167.91)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinEl, LOW); 
 }

//A note (110.61Hz)
 if ( (freq_per >105.61)&&(freq_per < 115.61) ){ // For Elow string
 digitalWrite(ledPinA, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<107.61){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if (freq_per>113.61){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=109.2)&&(freq_per<=111.61)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinA, LOW); 
 }

//D note (146.83 Hz)
 if ( (freq_per >142.65)&&(freq_per < 151.2) ){ // For Elow string
 digitalWrite(ledPinD, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<144.72){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if (freq_per>148.97){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=144.72)&&(freq_per<=148.97)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinD, LOW); 
 }


 //G note (196.0 Hz)
 if ( (freq_per >190.42)&&(freq_per < 201.74) ){ // For Elow string
 digitalWrite(ledPinG, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<192.9){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if (freq_per>198.85){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=192.9)&&(freq_per<=198.85)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinG, LOW); 
 }


 //B note (246.94 Hz)
 if ( (freq_per >238.6)&&(freq_per < 254.18) ){ // For Elow string
 digitalWrite(ledPinB, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<243.4){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if (freq_per>246.94){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=243.4)&&(freq_per<=246.94)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinB, LOW); 
 }
 
 float xmes = 323.92;
 float ymax = 323.9289;
 //E high note (329.63 Hz)
 if ( (freq_per >300.25)&&(freq_per < 339.29) ){ // For Elow string
 digitalWrite(ledPinEh, HIGH);
 //delay(1500); // wait for a second
 //digitalWrite(ledPinEl, LOW);
 if (freq_per<xmes){
 digitalWrite(ledPinRedLeft, HIGH); 
 delay(1500); // wait for a second
 digitalWrite(ledPinRedLeft, LOW);
 }
 if (freq_per>ymax){
 digitalWrite(ledPinRedRight, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinRedRight, LOW);
 }
 if ((freq_per>=xmes)&&(freq_per<=ymax)){
 digitalWrite(ledPinGreen, HIGH);
 delay(1500); // wait for a second
 digitalWrite(ledPinGreen, LOW);
 }
 digitalWrite(ledPinEh, LOW); 
 }
 
 }
 }
 count = 0;
 }
}
