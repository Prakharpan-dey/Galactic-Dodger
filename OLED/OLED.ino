#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ======================
// Hardware Configuration
// ======================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =================
// Game Constants
// =================
#define MAX_HEALTH 10
#define HEALTH_BAR_WIDTH 100
#define HEALTH_BAR_HEIGHT 10
#define HEALTH_BAR_X 14
#define HEALTH_BAR_Y 16
#define LEVELS_PER_SCORE 5
#define MAX_LEVEL 5

// =================
// Player Variables
// =================
long playerScore = 0;
int playerHealth = 0;
int playerLevel = 1;
int storedHighScore = 0;
bool showHighScore = false;  

// =================
// Display Functions
// =================
void drawPlayerStatus(bool showHigh = false) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Display high score (only when needed)
  if (showHigh) {
    display.setCursor(0, 0);
    display.print("High Score: ");
    display.print(storedHighScore);
  } else {
    // Draw game stats
    display.setCursor(0, 0);
    display.print("Lvl:");
    display.print(playerLevel);
    display.print(" Score:");
    display.print(playerScore);

    // Draw health bar
    display.drawRect(HEALTH_BAR_X, HEALTH_BAR_Y, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, WHITE);
    int fillWidth = map(playerHealth, 0, MAX_HEALTH, 0, HEALTH_BAR_WIDTH);
    display.fillRect(HEALTH_BAR_X, HEALTH_BAR_Y, fillWidth, HEALTH_BAR_HEIGHT, WHITE);
  }

  display.display();
}

// =================
// Setup
// =================
void setup() {
  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (1);
  }

  // Show startup message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Status Display Ready");
  display.display();
  delay(2000);

  // Show stored high score (if any)
  if (storedHighScore > 0) {
    drawPlayerStatus(true);
    delay(2000);
  }

  // Initial game status display
  drawPlayerStatus();
}

// =================
// Main Loop
// =================
void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Remove timestamps (everything before "-> ")
    int arrowPos = input.indexOf("-> ");
    if (arrowPos != -1) {
      input = input.substring(arrowPos + 3);
    }

    // Handle "High Score: X"
    if (input.startsWith("High Score: ")) {
      storedHighScore = input.substring(11).toInt();
      drawPlayerStatus(true);
      delay(2000);
      drawPlayerStatus();  // Refresh after high score disappears
      return;
    }

    // Handle "score : X health : Y"
    if (input.startsWith("score : ") && input.indexOf(" health :") != -1) {
      int healthPos = input.indexOf(" health :");
      playerScore = input.substring(8, healthPos).toInt();
      playerHealth = constrain(input.substring(healthPos + 9).toInt(), 0, MAX_HEALTH);

      // Calculate level
      playerLevel = min((playerScore / LEVELS_PER_SCORE) + 1, MAX_LEVEL);

      drawPlayerStatus();

      // Send confirmation to Serial Monitor
      Serial.print("Updated! Lvl:");
      Serial.print(playerLevel);
      Serial.print(" Score:");
      Serial.print(playerScore);
      Serial.print(" Health:");
      Serial.println(playerHealth);
    }
  }
}
