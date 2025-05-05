#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

struct Student {
  String uid;
  String studentID;
  String name;
  int balance;
};

Student students[] = {
  {"8B 52 85 3B", "S001", "Sam Pray", 1500},
  {"BA 11 2B 43", "S002", "Cynthia", 2000},
  {"03 56 F4 96", "S003", "Ngenzi w'Ingenzi", 25000}
};

const int studentCount = sizeof(students) / sizeof(students[0]);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Scan a card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Convert UID to string
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uidStr += " ";
  }
  uidStr.toUpperCase();
  Serial.print("Scanned UID: ");
  Serial.println(uidStr);

  // Search for matching student
  bool found = false;
  for (int i = 0; i < studentCount; i++) {
   if (students[i].uid == uidStr) {
      found = true;

      // Simulated time
      unsigned long t = millis() / 1000;
      int hr = (t / 3600) % 24;
      int min = (t / 60) % 60;
      int sec = t % 60;
      String timeStr = String(hr) + ":" +
                       (min < 10 ? "0" : "") + String(min) + ":" +
                       (sec < 10 ? "0" : "") + String(sec);

      Serial.println("---- TRANSACTION ----");
      Serial.println("Time: " + timeStr);
      Serial.println("Student: " + students[i].name);
      Serial.println("ID: " + students[i].studentID);

      if (students[i].balance > 1000) {
        students[i].balance= students[i].balance - 1000;
        Serial.println("Status: ✅ Meal paid");
      } else {
        Serial.println("Status: ❌ Insufficient balance");
      }

      Serial.print("New Balance: ");
      Serial.println(students[i].balance);
      Serial.println("----------------------");
      break;
    }
  }
  if (!found) {
    Serial.println("Unknown card.");
  }

  delay(1000);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
