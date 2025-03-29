# 🚀 Galactic Dodger 

## 🌌 What is Galactic Dodger?
Galactic Dodger is a thrilling arcade game where you control a rocket navigating through an asteroid field. Your mission is to dodge incoming obstacles and survive as long as possible! The challenge intensifies as the game progresses, making it a fun and addictive experience.

## 🎮 How Does It Work?
- A **10x20 LED Matrix** displays the game interface.
- The player controls the rocket using buttons to move left or right.
- The OLED display shows vital information such as:
  - Current score
  - High score
  - Health bar
  - Game level
- The rocket automatically moves upward, and the player needs to dodge incoming obstacles to stay alive.

---

## 🛠️ Hardware Requirements
- Arduino Uno
- 10x20 NEOPIXEL LED Matrix
- OLED Display (SSD1306)
- Push Buttons (for left and right movement)
- EEPROM for storing high scores
- Power supply 

---

## 📜 Features and Functionalities
1. 🎯 **High Score Persistence**  
   - High scores are stored in EEPROM, ensuring that they are preserved even after powering off the Arduino.
   - The OLED screen displays the highest score achieved.

2. 🔁 **Game Restart on Death**  
   - When the player's rocket collides with an asteroid repeatedly until the health becomes 0, the game restarts automatically.
   - High scores are updated before restarting.

3. ❤️ **Health Bar System**  
   - The rocket has a health bar that decreases upon hitting an obstacle.
   - Losing all health results in game over.

4. 🚀 **Progressive Game Level**  
   - The game becomes progressively harder by increasing the speed and obstacle density after every **5 points**.
   - Level details are displayed on the OLED screen.

5. 💥 **Hit Effect for Collisions**  
   - A cool visual effect is triggered when the rocket collides with obstacles, indicating a loss of health.

---

## 🔧 Circuit Connections
### 1️⃣ **LED Matrix Setup**
- A 10x20 LED matrix used for displaying the visuals of the game.

### 2️⃣ **Button Configuration**
- Left and right buttons connected to Arduino digital pins.
- Debounce logic is used to avoid multiple false triggers.

### 3️⃣ **OLED Display Connection**
- I2C communication protocol used for interfacing with OLED.
- SDA and SCL connected to A4 and A5 of Arduino Uno.

---

## 🕹️ Game Controls
- **Left Button:** Move the rocket left.
- **Right Button:** Move the rocket right.

---


 
