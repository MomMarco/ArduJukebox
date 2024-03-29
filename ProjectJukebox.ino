
int const potPin = A0;
long beat;
long bpm;
long l;
long time;

int notes1[] = { 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 330, 294, 294,               //15
                 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 294, 262, 262,               //15
                 294, 294, 330, 262, 294, 330, 349, 330, 262, 294, 330, 349, 330, 294, 262, 294, 296, 0,  //18
                 330, 330, 349, 392, 392, 349, 330, 294, 262, 262, 294, 330, 294, 262, 262 };             //15

long t1[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 0.5, 2,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 0.5, 2,
              1, 1, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 1,
              1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 0.5, 2 };
int N1 = 63;

int notes2[] = { 262, 294, 330, 262, 330, 262, 330, 294, 330, 349, 349, 330, 294, 349, 330, 349, 392, 330,            //18
                 392, 330, 392, 349, 392, 440, 440, 392, 330, 440, 392, 262, 294, 330, 349, 392, 440,                 //17
                 440, 294, 330, 370, 392, 440, 494, 494, 330, 370, 415, 440, 494, 523, 494, 466, 440, 349, 494, 392,  //20
                 523, 392, 330, 262, 262, 294, 330, 349, 392, 440, 494, 523, 523, 392, 523 };                         //15

long t2[] = { 1.5, 0.5, 1.5, 0.5, 1, 1, 2, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 4, 1.5, 0.5, 1.5, 0.5,        //18
              1, 1, 2, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 4, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 4,               //17
              1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 4, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 3, 0.5, 0.5, 1, 1, 1, 1,  //20
              1, 1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 1, 2 };                           //15
int N2 = 70;
//int notes3[] = {131,147,165,175,196,220,246};
//int notes4[] = {262,294,330,349,392,440,494};
//int notes5[] = {523,587,659,698,784,880,989};

int startswitch = 0;  //switch that starts the track
int trackswitch = 0;  //switch that selects the track
int track = 0;        //track seletcted
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (track == 0) Serial.print("TRACK 0: METRONOME SETTING");
  while (track == 0) {
    startswitch = digitalRead(2);
    trackswitch = digitalRead(3);
    beat = analogRead(potPin);          //use te pot pin to control the beat
    bpm = map(beat, 0, 1023, 40, 218);  //convert the beat in beats per minute
    l = 60000 / bpm;                    //lenght of a whole note
    Serial.print(" bpm :");
    Serial.println(bpm);
    Serial.print(" lenght of a whole note:");
    Serial.println(l);
    delay(500);
    if (startswitch == HIGH) {
      for (int i = 0; i < 3; i++) {
        tone(8, 131, 100);

        delay(l);
        noTone(8);
      }
      tone(8, 262, 100);
      delay(l);
      noTone(8);
    }

    if (trackswitch == HIGH) {
      track++;
      delay(200);
    }
  }

  if (track == 1) {
    Serial.println("TRACK 1: ODE TO JOY. PRESS SWITCH TO START");
    Serial.print(" bpm: ");
    Serial.println(bpm);
    Serial.print(" note lenght: ");
    Serial.println(l);
  }
  while (track == 1) {
    startswitch = digitalRead(2);
    trackswitch = digitalRead(3);
    if (startswitch == HIGH) {
      Serial.println("PLAYING");
      startswitch == LOW;
      for (int i = 0; i < 3; i++) {
        tone(8, 131, 100);
        delay(l);
        noTone(8);
      }
      tone(8, 262, 100);
      delay(l);
      noTone(8);
      for (int i = 0; i < N1; i++) {
        time = t1[i] * l;
        startswitch = digitalRead(2);
        if (notes1[i] == 0) {
          noTone(8);
          delay(time);
        } else {
          tone(8, notes1[i], time);
          delay(100);
          noTone(8);
        }
        if (startswitch == HIGH) {
          delay(200);
          Serial.println("TRACK STOPPED");
          break;
        }
      }
      if (trackswitch == HIGH) {
        track++;
        delay(200);
        trackswitch = LOW;
      }
    }
  }

  if (track == 2) {
    Serial.print("TRACK 2: DO RE MI. PRESS SWITCH TO START");
    Serial.print(" bpm: ");
    Serial.println(bpm);
    Serial.print(" note lenght: ");
    Serial.println(l);
  }
  while (track == 2) {
    startswitch = digitalRead(2);
    trackswitch = digitalRead(3);
    if (startswitch == HIGH) {
      for (int i = 0; i < 3; i++) {
        tone(8, 131, 100);
        delay(l);
        noTone(8);
      }
      tone(8, 262, 100);
      delay(l);
      noTone(8);
      for (int i = 0; i < N2; i++) {
        time = t2[i] * l;
        if (notes2[i] == 0) {
          noTone(8);
          delay(time);
        } else tone(8, notes2[i], time);
        delay(100);
        noTone(8);
        if (startswitch == HIGH) {
          delay(200);
          Serial.print("TRACK STOPPED");
          break;
        }
      }
      if (trackswitch == HIGH) {
        track == 0;
        delay(200);
      }
    }
  }
}
