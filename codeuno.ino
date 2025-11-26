int out1 = 3;   // fermeture 2s
int out2 = 5;   // œil gauche fermé + iris gauche
int out3 = 7;   // œil gauche fermé + iris droite

void setup() {
  Serial.begin(9600);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);

  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
}

void loop() {
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n');
    s.trim();

    // format : a,b,c
    int idx1 = s.indexOf(',');
    int idx2 = s.lastIndexOf(',');

    if (idx1>0 && idx2>idx1) {
      int a = s.substring(0, idx1).toInt();
      int b = s.substring(idx1+1, idx2).toInt();
      int c = s.substring(idx2+1).toInt();

      digitalWrite(out1, a);
      digitalWrite(out2, b);
      digitalWrite(out3, c);
    }
  }
}
