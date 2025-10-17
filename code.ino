#define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Health Monitor"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"

#include <Wire.h>
#include "MAX30102.h"
#include "spo2_algorithm.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

MAX30102 particleSensor;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// --- Pin Mapping ---
#define LED_ALERT 19
#define BUZZER 23
#define BUTTON 13

// --- WiFi & Blynk ---
char ssid[] = "Your_WiFi_Name";
char pass[] = "Your_WiFi_Password";

// --- Variables ---
long lastBeat = 0;
float beatsPerMinute;
int beatAvg = 0;
int SPO2;
bool alertActive = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  // --- WiFi + Blynk ---
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // --- OLED ---
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while(1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // --- MAX30102 ---
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found!");
    while (1);
  }

  particleSensor.setup(); // default: 69 sample rate, 18 LED pulse width
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);
}

void loop() {
  Blynk.run();

  long irValue = particleSensor.getIR();

  if (irValue < 50000) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("No finger detected");
    display.display();
    digitalWrite(LED_ALERT, LOW);
    digitalWrite(BUZZER, LOW);
    return;
  }

  static long lastTime = 0;
  long delta = millis() - lastTime;
  lastTime = millis();

  static int beatCount = 0;
  if (checkForBeat(irValue)) {
    long beatDuration = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (beatDuration / 1000.0);
    beatAvg = (beatAvg * 3 + beatsPerMinute) / 4;

    Serial.print("BPM=");
    Serial.println(beatAvg);
  }

  // Giả lập SPO2
  SPO2 = 98 - random(0, 3);

  // Hiển thị OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("BPM: ");
  display.println(beatAvg);
  display.print("SPO2: ");
  display.print(SPO2);
  display.println("%");
  display.display();

  // Gửi lên Blynk
  Blynk.virtualWrite(V0, beatAvg);
  Blynk.virtualWrite(V1, SPO2);

  // Kiểm tra ngưỡng cảnh báo
  if (beatAvg > 120 || beatAvg < 50) {
    alertActive = true;
  }

  if (alertActive) {
    digitalWrite(LED_ALERT, HIGH);
    tone(BUZZER, 1000);
  } else {
    digitalWrite(LED_ALERT, LOW);
    noTone(BUZZER);
  }

  // Nút nhấn tắt cảnh báo
  if (digitalRead(BUTTON) == LOW) {
    alertActive = false;
    noTone(BUZZER);
    digitalWrite(LED_ALERT, LOW);
  }

  delay(200);
}
