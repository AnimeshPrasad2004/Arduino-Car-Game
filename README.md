
## Description 
The project is a car game where the player must avoid touching or crashing into obstacle cars. It's an infinite time game where the score is calculated based on the user's total time survived. The longer the user survives, the higher the score points.
## Controls
The motion of the player car is controlled by the joystick:
- Joystick Y Axis: Controls the forward and backward motion of the player car.
* Joystick Horizontal Axis: Controls the left and right movement of the player car.
* A: start the game/ pause the game while playing
* B: Restart
* C: View Score
* D: Help/Back

## Components
- Arduino Uno board
- TFT SPI ST7735 display
- Joystick Funduino shield
## Libraries
- <SPI.h>
- <Adafruit_GFX.h>
- Adafruit_ST7735.h>
## How To Play
- Use the joystick controls to move the player car and avoid crashing into obstacle cars.
- Survive as long as possible to achieve a high score.
## Code Insights
- getScore(): it shows the score interface of the user.
- DrawLane(): this draws the Lane markings on the road and moves it in a loop.
- obstacle(): this generates the obstacle cars, one at a time when your score is less than 200 and after that two obstacle cars at a time.
- DrawCar(): it uploads the image of car and run it throughout the screen by taking the input from the joystick.
- load(): it bring ups the start game screen.
- menu(): this function helps to bring up the main menu screen.
- needHelp(): it takes us to the help screen page.
- pauseGame(): this void function pause the game in between ans shows us various option to continue: resume, restart and score.
- rst(): it restarts the game and starts with a new game and zero score.
- collision(): this function checks if our player car has collided with the obstacles.
    
