 
int FSRanalogpin = A0;  // FSR is connected to analog 0
int buzzer = 5;

int FSRvalue = 0;

int fsrReading;        // the analog reading from the first FSR resistor divider


int VIBintensity; 
int VIBpin = 6;   

void setup(void) {
  Serial.begin(115200);   // We'll send debugging information via the Serial monitor
  pinMode(VIBpin, OUTPUT);


//code for buzzer
pinMode(FSRanalogpin,INPUT); //sets the FSR as the input
pinMode(buzzer,OUTPUT);   //sets the buzzer as the output
}
 
void loop(void) {
  fsrReading = analogRead(FSRanalogpin);
 
  Serial.print("Analog reading = ");
  
  Serial.println(fsrReading);
 
  // we'll need to change the range from the analog reading (0-1023) down to the range
  // used by analogWrite (0-255) with map!
  VIBintensity = map(fsrReading, 0, 1023, 0, 255);
  VIBintensity*=10;
  if (VIBintensity>255) {
    VIBintensity=255;

//code for buzzer
FSRvalue = analogRead(FSRanalogpin); //reads the FSR and store it in integer
analogWrite(buzzer,FSRvalue/4); //sets the buzzer duty ratio

  }
  
  // Vibrations increase the harder you press
  analogWrite(VIBpin, VIBintensity*7);
  
  delay(100);
}
