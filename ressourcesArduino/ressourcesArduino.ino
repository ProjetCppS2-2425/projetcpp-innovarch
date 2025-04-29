#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define ECHO_PIN 12
#define TRIG_PIN 13
#define LED_PIN 8

#define PULSE_TIMEOUT 30000 // Timeout for pulseIn
#define SOUND_SPEED 0.034   // Speed of sound in cm/us
#define SERIAL_TIMEOUT 100  // Serial read timeout in ms

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String resourceName = "Waiting..."; // Default resource name
int stock = -1;                    // Stock quantity, initialized to -1
int baselineDistance = 0;          // Initial distance baseline
int lastDistance = 0;              // Last measured distance
const int REMOVAL_THRESHOLD = 8;   // Distance change threshold (cm)
const int REMOVAL_COOLDOWN = 1500; // Cooldown to avoid multiple detections (ms)
const int MIN_VALID_DISTANCE = 2;  // Minimum valid distance (cm)
const int MAX_VALID_DISTANCE = 400;// Maximum valid distance (cm)
bool isConnected = false;          // Tracks Qt connection status
bool displayInitialized = false;   // Tracks OLED initialization
unsigned long lastRemovalTime = 0; // Time of last removal

void updateDisplay(String message = "");
int calcDist();
int averageDistance();

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(SERIAL_TIMEOUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize OLED display
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    displayInitialized = true;
    Serial.println("SSD1306 initialized successfully");
    updateDisplay("Connecting to Qt...");
  } else {
    Serial.println(F("SSD1306 allocation failed."));
  }

  // Initialize sensor
  delay(2000); // Let the sensor stabilize
  baselineDistance = averageDistance();
  lastDistance = baselineDistance;
  Serial.print(F("Baseline Distance: "));
  Serial.println(baselineDistance);

  // Signal Qt that Arduino is ready
  Serial.println("HELLO");
  delay(1000);
  Serial.println("READY");
}

void loop() {
  // Handle incoming serial data from Qt
  while (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) continue;
    Serial.println("Received: " + line);

    if (line.startsWith("SET:")) {
      int firstColon = line.indexOf(':');
      int secondColon = line.lastIndexOf(':');
      if (firstColon != -1 && secondColon != -1 && firstColon != secondColon) {
        resourceName = line.substring(firstColon + 1, secondColon);
        stock = line.substring(secondColon + 1).toInt();
        Serial.println("Parsed: Name=" + resourceName + ", Stock=" + String(stock));
        Serial.println("GOT:" + line);
        isConnected = true;
        updateDisplay();
      } else {
        Serial.println("ERROR: Invalid SET command: " + line);
      }
    }
  }

  // Process sensor data if connected and stock is valid
  if (isConnected && stock >= 0) {
    int currentDistance = averageDistance();
    Serial.print("Current Distance: ");
    Serial.println(currentDistance);

    // Validate distance
    if (currentDistance < MIN_VALID_DISTANCE || currentDistance > MAX_VALID_DISTANCE) {
      Serial.println("Invalid Distance: " + String(currentDistance));
      digitalWrite(LED_PIN, LOW);
      delay(200);
      return;
    }

    unsigned long currentTime = millis();
    int distanceDiff = abs(currentDistance - baselineDistance);

    // Detect removal if distance increases significantly
    if (distanceDiff > REMOVAL_THRESHOLD && stock > 0 &&
        currentTime - lastRemovalTime >= REMOVAL_COOLDOWN) {
      Serial.println("DECREMENT");
      stock--; // Update local stock
      updateDisplay();
      lastRemovalTime = currentTime;
    }

    lastDistance = currentDistance;

    // Update LED based on stock level
    digitalWrite(LED_PIN, stock < 5 ? HIGH : LOW);
  }

  // Update display
  updateDisplay();

  delay(500);
}

void updateDisplay(String message) {
  if (!displayInitialized) {
    Serial.println(F("Display not initialized, skipping update"));
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1); // Smaller text to fit resource name
  display.setCursor(0, 0);

  if (message != "") {
    display.println(message);
  } else {
    display.println("Resource: " + resourceName);
    display.println("Stock: " + String(stock));
    if (stock < 5) {
      display.println("LOW STOCK!");
    }
  }
  display.display();
}

int calcDist() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);
  if (duration == 0) return -1; // Invalid reading
  return duration * SOUND_SPEED / 2;
}

int averageDistance() {
  long sum = 0;
  int validSamples = 0;
  const int SAMPLES = 5;
  for (int i = 0; i < SAMPLES; i++) {
    int dist = calcDist();
    if (dist >= MIN_VALID_DISTANCE && dist <= MAX_VALID_DISTANCE) {
      sum += dist;
      validSamples++;
    }
    delay(50);
  }
  int avg = validSamples > 0 ? sum / validSamples : lastDistance;
  Serial.print(F("Average Distance: "));
  Serial.println(avg);
  return avg;
}