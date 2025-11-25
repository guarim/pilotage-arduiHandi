// Définition des broches
const int PIN_SORTIE_1 = 2; // Programme lancé
const int PIN_SORTIE_2 = 3; // Iris Gauche
const int PIN_SORTIE_3 = 4; // Iris Droite

String inputString = "";      
bool stringComplete = false;  

void setup() {
  Serial.begin(9600); // Doit correspondre au débit dans le JS
  
  pinMode(PIN_SORTIE_1, OUTPUT);
  pinMode(PIN_SORTIE_2, OUTPUT);
  pinMode(PIN_SORTIE_3, OUTPUT);
  
  // Tout éteindre au démarrage
  stopAll();
}

void loop() {
  // Traitement de la commande reçue
  if (stringComplete) {
    inputString.trim(); // Enlever les espaces et sauts de ligne
    
    if (inputString == "CMD_START") {
      digitalWrite(PIN_SORTIE_1, HIGH); // Activer sortie 1
    } 
    else if (inputString == "CMD_STOP_ALL") {
      stopAll(); // Tout désactiver
    }
    else if (inputString == "CMD_OUT2_ON") {
      // Sécurité : on active 2 seulement si 1 est actif
      if(digitalRead(PIN_SORTIE_1) == HIGH) {
        digitalWrite(PIN_SORTIE_2, HIGH);
        digitalWrite(PIN_SORTIE_3, LOW); // Exclusif (optionnel)
      }
    }
    else if (inputString == "CMD_OUT3_ON") {
      if(digitalRead(PIN_SORTIE_1) == HIGH) {
        digitalWrite(PIN_SORTIE_3, HIGH);
        digitalWrite(PIN_SORTIE_2, LOW); // Exclusif (optionnel)
      }
    }
    else if (inputString == "CMD_OUT23_OFF") {
      digitalWrite(PIN_SORTIE_2, LOW);
      digitalWrite(PIN_SORTIE_3, LOW);
    }
    
    // Reset
    inputString = "";
    stringComplete = false;
  }
}

// Lecture du port série
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}

void stopAll() {
  digitalWrite(PIN_SORTIE_1, LOW);
  digitalWrite(PIN_SORTIE_2, LOW);
  digitalWrite(PIN_SORTIE_3, LOW);
}