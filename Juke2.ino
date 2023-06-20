int const potPin = A0;
long beat;
long bpm;
long l;
long time;
int n = 0;

int notes1[] = { 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 330, 294, 294,               //15
                 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 294, 262, 262,               //15
                 294, 294, 330, 262, 294, 330, 349, 330, 262, 294, 330, 349, 330, 294, 262, 294, 196, 0,  //18
                 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 294, 262, 262 };             //15

long t1[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 3, 1, 4,
              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4,
              2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2,2,2,
              2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4 };
int N1 = 63;

int notes2[] = { 262, 294, 330, 262, 330, 262, 330, 294, 330, 349, 349, 330, 294, 349, 330, 349, 392, 330,            //18
                 392, 330, 392, 349, 392, 440, 440, 392, 349, 440, 392, 262, 294, 330, 349, 392, 440,                 //17
                 440, 294, 330, 370, 392, 440, 494, 494, 330, 370, 415, 440, 494, 523, 494, 466, 440, 349, 494, 392,  //20
                 523, 392, 330, 262, 262, 294, 330, 349, 392, 440, 494, 523, 523, 392, 523 };                         //15

long t2[] = { 3, 1, 3, 1, 2, 2, 4, 3, 1, 1, 1, 1, 1, 4, 3, 1, 3, 1,        //18
              2, 2, 4, 3, 1, 1, 1, 1, 1, 4, 3, 1, 1, 1, 1, 1, 4,           //17
              3, 1, 1, 1, 1, 1, 4, 3, 1, 1, 1, 1, 1, 3, 1, 1, 2, 2, 2, 2,  //20
              2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2 };               //15
int N2 = 70;

int notes3[] = { 659, 587, 370, 392, 523, 494, 294, 330, 440, 392, 262,330, 440};
long t3[] = {1,1,2,2,1,1,2,2,1,1,2,2,8};
int N3=13;
//int notes3[] = {131,147,165,175,196,220,246};
//int notes4[] = {262,294,330,349,392,440,494};
//int notes5[] = {523,587,659,698,784,880,989};

int startswitch;
int setswitch;
int selectswitch;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  startswitch = digitalRead(2);
  setswitch = digitalRead(3);
  selectswitch = digitalRead(4);
  if (setswitch == HIGH) {
    beat = analogRead(potPin);
    bpm = map(beat, 0, 1023, 40, 218);
    l = 60000 / bpm;
    Serial.print("bpm: ");
    Serial.println(bpm);
    Serial.print("lenght of a whole note: ");
    Serial.println(l);
    delay(1000);
  }

  if (selectswitch == HIGH) {
    n++;
    Serial.println(n);
    delay(200);
  }

  
  if (startswitch == HIGH && n == 1) {
    Serial.print("TRACK 1 SELECTED: ODE TO JOY. BPM: ");
    Serial.println(bpm);
    delay(1000);
    for (int i = 0; i < N1; i++) {
      time = (t1[i] * l)/2;
      Serial.println (time);
      startswitch = digitalRead(2);
      if(startswitch == HIGH){
        delay(500);
        break;
      }
      if (notes1[i] == 0) {
        noTone(8);
        delay(time);
      } else {
        tone(8, notes1[i]);
        delay(time);
        noTone(8);  
      }
    
    }
    Serial.print("TRACK 1 OVER ");
  }
  else if (startswitch == HIGH && n == 2){
    delay(1000);
    Serial.print("TRACK 2 SELECTED: DO RE MI. BPM: ");
    Serial.println(bpm);
    for (int i = 0; i < N2; i++) {
      time = t2[i]*l/2;
      startswitch = digitalRead(2);
      if(startswitch == HIGH){
        delay(500);
        break;
      }
      if (notes2[i] == 0) {
        noTone(8);
        delay(time);
      } else {
        tone(8, notes2[i]);
        delay(time);
        noTone(8);
      }
    }
    Serial.println("TRACK 2 OVER ");
  }
  else if (startswitch == HIGH && n == 3){
    delay(1000);
    Serial.print("TRACK 3 SELECTED: NOKIA. BPM: ");
    Serial.println(bpm);
    for (int i = 0; i < N3; i++) {
      time = t3[i]*l/2;
      startswitch = digitalRead(2);
      if(startswitch == HIGH){
        delay(500);
        break;
      }
      if (notes3[i] == 0) {
        noTone(8);
        delay(time);
      } else {
        tone(8, notes3[i]*2);
        delay(time);
        noTone(8);
      }
    }
    Serial.println("TRACK 3 OVER ");
  }
  else if (n > 3){
    n=0;
    Serial.println(n);
  }
}