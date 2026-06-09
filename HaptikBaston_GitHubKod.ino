#include <SoftwareSerial.h>

#define TRIG 9
#define ECHO 10
#define VIBE 6
#define BUZZER 5

SoftwareSerial BTserial(2, 3);

int mesafe;

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(VIBE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  digitalWrite(BUZZER, LOW);
  
  Serial.println("Baston Hazir - Telefondan mesaj gonderin, baston otsun.");
  BTserial.println("Baston Hazir. Mesaj gonderin, baston otsun.");
}

void loop() {
  // Mesafe ölçümü ve Titreşim
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long sure = pulseIn(ECHO, HIGH);
  mesafe = sure * 0.034 / 2;

  if (mesafe > 20 && mesafe <= 200) {
    int siddet = map(mesafe, 20, 200, 255, 50);
    analogWrite(VIBE, siddet);
  } else {
    analogWrite(VIBE, 0);
  }

  // Telefondan mesaj gelince Buzzer çal (3 kısa bip)
  if (BTserial.available()) {
    String gelen = BTserial.readString();
    gelen.trim();
    if (gelen.length() > 0) {
      // 3 kez bip
      for (int i = 0; i < 3; i++) {
        digitalWrite(BUZZER, HIGH);
        delay(500);
        digitalWrite(BUZZER, LOW);
        delay(500);
      }
      
      // Telefona geri bildirim mesajı (istediğin gibi değiştirebilirsin)
      BTserial.println("Baston bulundu!");   // <--- İstediğin metni yaz
      Serial.print("Telefondan mesaj alindi: ");
      Serial.println(gelen);
    }
  }

  delay(50);
}

