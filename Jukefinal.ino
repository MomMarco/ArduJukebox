int potPin = A1;
long beat;
long bpm;
long l;
long time;

int const MAX= 100;
int notes[MAX]={0};
float t[MAX]={0};

int N1;
int notes1[]={};
float t1[]={};

int N2;
int notes2[]={};
float t2[]={};

int N3;
int notes3[]={};
float t3[]={};

int n=0;

int sswitch;

void setup(){

  Serial.begin(9600);

}


void loop(){

  sswitch = analogRead(A0);

  if(sswitch == 1023){
    beat = analogRead(potPin);
    bpm = map(beat,0,1023,40,218);
    l = 60000 / bpm;
    Serial.print("BPM: ");
    Serial.println(bpm);
    Serial.print("LENGHT OF A NOTE: ");
    Serial.println(l);
    delay(500);
  }

  else if(sswitch >= 990 && sswitch<=1010){

    n++;
    if(n==1){
      Serial.print("TRACK 1 ");
      for(int i = 0; i<MAX;i++){

        if(i<N1){
          notes[i]= notes1[i];
          t[i]= t1[i];
        }
        else{
          notes[i]=0;
          t[i]=0;
        }
      }
      Serial.println("READY");
    }
    else if(n==2){
      Serial.print("TRACK 2 ");
      for(int i = 0; i<MAX;i++){

        if(i<N2){
          notes[i]= notes2[i];
          t[i]= t2[i];
        }
        else{
          notes[i]=0;
          t[i]=0;
        }
      }
      Serial.println("READY");
    }
    else if(n==3){
      Serial.print("TRACK 3 ");
      for(int i = 0; i<MAX;i++){

        if(i<N3){
          notes[i]= notes3[i];
          t[i]= t3[i];
        }
        else{
          notes[i]=0;
          t[i]=0;
        }
      }
      Serial.println("READY");
    }
    else if(n > 3){
      n=0;
      Serial.println("NO TRACK SELECTED");
    }

  }
  
  else if(sswitch >= 505 && sswitch<=515){
    
    Serial.print("PLAYING TRACK ");
    Serial.println(n);
    int i = 0;
    while(true){
      
      time = t[i]*l;
      tone(8,notes[i]);
      delay(time);
      noTone(8);
      i++;
      sswitch =analogRead(A0);
      if(sswitch >= 505 && sswitch<=515){

        delay(300);
        Serial.println("TRACK STOPPED");
        break;

      }
      if(t[i]==0){
        Serial.println("TRACK OVER");
        break;
      }

    }

  }

}