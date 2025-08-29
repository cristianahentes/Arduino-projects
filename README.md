This Arduino project is an interactive reaction game designed to test and improve the player's reflexes. The game uses two LEDs with associated relays, a push button, a buzzer, and a 16x2 LCD display to provide feedback.

Features:

-Random LED Activation: One of the two LEDs lights up at random intervals, signaling the player to react.

-Score System: Pressing the button while the LED is ON increases the score by 1. Pressing when LEDs are OFF decreases the score by 1 (but the score never goes below 0).

-Debounced Button Input: The button input is debounced to prevent multiple score increments for a single press.

-LCD Feedback: The 16x2 LCD displays the current score and feedback messages like "Correct!" or "Wrong!" after each button press.

-Final Stage: When the player reaches a score of 10:

-Both LEDs and relays are activated.

-The buzzer sounds for 3 seconds.

-LEDs remain on for 1 minute.

-The game then resets automatically.

Components:

-Arduino UNO (or compatible board)

-2x16 LCD display with I2C interface

-2 LEDs

-2 Relays

-Push button

-Buzzer

-Resistors, jumper wires, and breadboard

How It Works:

-The game randomly selects one LED to turn on for a fixed duration (1 second).

-The player must press the button while the LED is lit to score a point.

-Pressing the button when no LED is active results in a penalty.

-The LCD displays the current score and whether the last action was correct or incorrect.

-Upon reaching 10 points, the game enters the final stage and then restarts automatically after a short delay.

Installation see the picture attached:

-Connect the components according to the wiring diagram (LEDs, relays, button, buzzer, LCD).

-Install the LiquidCrystal_I2C library in Arduino IDE.

-Upload the provided Arduino sketch.

-Open the Serial Monitor to see additional debugging output if needed.

Usage:

-Press the button as quickly as possible when the LED lights up.

-Avoid pressing the button when LEDs are off to prevent losing points.

-Reach a score of 10 to trigger the final stage and watch the game reset for a new round.
