#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "car.h"
#include "police.h"
#include "police1.h"

#define BLACK 0x0000
#define GRAY    0x8410
#define WHITE 0xFFFF
#define GREEN 0x0F00 
#define LIME  0x0FFF
#define RED 0xF800
#define BLUE 0x00FF
#define CYAN 0x07FF
#define ORANGE  0xFBE0
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define TFT_CS 10
#define TFT_RST 9
#define TFT_DC 8

bool start=1,hp=0,reset=1,help=1,DisplayScore=1,pause=1;
int v = 0;
int const JOYSTICK_AXIS_X = A0;
int const JOYSTICK_AXIS_Y = A1;
int const A = 2;
int const B = 3;
int const C = 4;
int const D = 5;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int ox1,oy1,ox2,oy2,cx,cy;
int  g1 = -17,g2 = -17,r_1,r_2;
int x = 57;
int y = 2,highScore,score;
int inputX, inputY;


void setup() {
  Serial.begin(9600);
  tft.initR(INITR_144GREENTAB);  
  load();
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  pinMode(JOYSTICK_AXIS_X, INPUT);
  pinMode(JOYSTICK_AXIS_Y, INPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
}

void loop() {

  options();
  
  inputX = analogRead(JOYSTICK_AXIS_X);
  inputY = analogRead(JOYSTICK_AXIS_Y);

  if (x + map(inputX, 0, 660, -3, 3) >= 10 && x + map(inputX, 0, 660, -3, 3) + 22 <= 120 && y + map(inputY, 0, 660, -3, 3) >= 0 && y + map(inputY, 0, 660, -3, 3) + 35 <= 128) {
    x = x + map(inputX, 0, 660, -3, 3);
    y = y + map(inputY, 0, 660, -3, 3);
  }

  DrawLane();
  
  //grass
  tft.fillRect(0, 1, 128, 10, GREEN);
  tft.fillRect(0, 118, 128, 10, GREEN);

  //police
  obstacle();
  
  //car
  DrawCar();

  //checking collision
  collision();

  score++; 

  if(highScore<score){
    highScore=score;
  }
  delay(50);
}


void DrawLane(){
  int l = -1;
  while (l <= 3) {
    if (v <= -60) {
      v = 350;
    }
    tft.fillRect(42 * l + 0.1 * v, 47, 21, 2, WHITE);
    tft.fillRect(42 * l + 0.1 * v + 21, 47, 21, 2, BLACK);
    tft.fillRect(42 * l + 0.1 * v, 83, 21, 2, WHITE);
    tft.fillRect(42 * l + 0.1 * v + 21, 83, 21, 2, BLACK);
    tft.fillRect(0.1 * v - 21, 47, 21, 2, BLACK);
    tft.fillRect(0.1 * v - 21, 83, 21, 2, BLACK);
    l++;

    v -= 5;
  }
}

void obstacle(){

  if(score>200){
  if (oy1 == oy2 && abs(g1 - g2) <= 12){
    if(g1>=g2){
      g1+=12;
    }
    else{
      g2+=12;
    }
  }
  }

  int p=random(1,4);
  int q=random(1,3);
  int f=p+q;
  if(f>3){
    f=f-3;
  }

    if(g1<=-16){
      switch(p){
      case 1: r_1 = 22;
      break;
      case 2: r_1 = 57;
      break;
      case 3: r_1 = 89;
      break; 
    }
      g1=42;
    }  

  g1--;

    int buffidx1 = 0,r1,c1;
  for(r1 = r_1; r1 < r_1+19; r1++) {
      for (c1 = 0; c1 < 35; c1++) {
        ox1 = c1 + 3*g1;
        oy1 = r1;
        tft.drawPixel(ox1,oy1, pgm_read_word(police + buffidx1));
        buffidx1++;
      }
  }

  if(score>200){
      if(g2<=-16){
      switch(f){
      case 1: r_2 = 22;
      break;
      case 2: r_2 = 57;
      break;
      case 3: r_2 = 89;
      break; 
    }
      g2=50;
    }
  
    g2--;

    int buffidx2 = 0,r2,c2;
    for(r2 = r_2; r2 < r_2+19; r2++) {
      for (c2 = 0; c2 < 35; c2++) {
        ox2 = c2 + 3*g2;
        oy2 = r2;
        tft.drawPixel(ox2,oy2, pgm_read_word(police1 + buffidx2));
        buffidx2++;
      }
  }
  };

}

void DrawCar(){

  int h = 22, w = 35, row = 7, col, buffidx = 0;

  //setting the boundaries
  if (row + x >= 10 && row + x + 22 <= 128 && col + y >= 0 && col + y <= 128) {

    for (row = 0; row < h; row++) {
      for (col = 0; col < w; col++) {
        cx=col + y;
        cy= row + x;
        tft.drawPixel(cx,cy, pgm_read_word(car + buffidx));
        buffidx++;
      }
    }

  }
}

void load(){
  tft.setRotation(0); // Adjust rotation if needed
  tft.setTextSize(2);
  tft.fillScreen(BLACK);
  int color=-0XFFF;
  while(color<0XFFF){
    tft.setTextColor(color);
    tft.setCursor(15,45);
    tft.println("NEED FOR");
    tft.setCursor(40,70);
    tft.println("PACE");
    color+=20;
    Serial.println(color);
    }
  tft.fillScreen(BLACK);
  while(start==true){
    menu();
    tft.setTextColor(YELLOW);
    tft.setCursor(13, 5);
    tft.fillRoundRect(9, 0, 115, 25,10, RED);
    tft.println("MAIN MENU\n");
    tft.setTextColor(CYAN);
    tft.println(" A-start /  pause");
    tft.println(" B-reset");
    tft.println(" C-score");
    tft.println(" D-help");
    delay(1000);
    if(help==false){
      delay(100);
      needHelp();
      tft.fillScreen(BLACK);
    }
    if(DisplayScore==false){
      getScore();
    }
    if(reset==false){
      rst();
    }
  }
  
  tft.fillScreen(BLACK);
  tft.setCursor(0,45);
  tft.setTextSize(2);
  tft.print("Loading...");
  delay(2000);
  float i;
  for( i= 0; i<82; i=i+0.04){
  tft.fillRect(25,80,i,5,RED);

  }
}

void menu(){
  start=digitalRead(A);
  reset=digitalRead(B);
  DisplayScore=digitalRead(C);
  help=digitalRead(D);

}

void needHelp(){
  tft.fillScreen(BLACK);
  while(true){
    int back=digitalRead(D);
    tft.setRotation(0);
    tft.setCursor(45,10);
    tft.setTextSize(2);
    tft.fillRoundRect(36, 5, 60,25,10, RED);
    tft.setTextColor(YELLOW);
    tft.println("HELP");
    tft.setTextSize(1);
    tft.setTextColor(CYAN);
    tft.setCursor(50,50);
    tft.println("\nDon't hit other cars and drive as much as you can");
    tft.println("\n\nD-Back");
    tft.setTextSize(2);
    if(back==false){
      tft.fillScreen(BLACK);
      delay(100);
      break;
      
    }
    tft.println("\n\nD-Back");
  }
  
}

void getScore(){
  tft.fillScreen(BLACK);
  while(true){
    int back=digitalRead(D);
    reset=digitalRead(B);
    tft.setRotation(0);
    tft.setTextSize(2);
    tft.setCursor(0,15);
    tft.println("score:");
    tft.println(score);
    tft.print("max score:");
    tft.println(highScore);
    tft.setTextSize(1);
    tft.println("\n\nB-reset");
    tft.println("D-back");
    tft.setTextSize(2);
    if(back==false){
      tft.fillScreen(BLACK);
      delay(100);
      break;
    }
    if(reset==false){
      rst();
      tft.fillScreen(BLACK);
      delay(100);
      break;
    }
  }
  
}

void pauseGame(){
  tft.setCursor(100,10);
  tft.setTextSize(3);
  tft.setTextColor(RED);
  tft.print(".");
  delay(100);
  tft.setCursor(100,10);
  tft.setTextColor(BLACK);
  tft.print(".");
  delay(100);
  tft.setRotation(0);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(15,40);
  tft.println("A-Resume");
  tft.setCursor(20,70);
  tft.println("B-Reset");
  tft.setCursor(20,100);
  tft.println("C-Score");
  if(reset==false){
    rst();
  }
  if(DisplayScore==false){
    getScore();
  }
}

void options(){
  while(true){

    menu();
    if(start==false){
        if(pause==false){
          tft.fillScreen(BLACK);
        }
        else{
          tft.setRotation(0);
          tft.fillRoundRect(10, 38, 105, 20,10, BLUE);
          tft.fillRoundRect(15, 67, 95, 20,10, BLUE);
          tft.fillRoundRect(15, 97, 95, 20,10, BLUE);
        }
        pause=!pause;
        delay(200);
      }
    
    if(pause==false){
      pauseGame();
    }
    else{
      tft.setRotation(3);
      break;
    }
  }
}

void rst(){
  start=1;
  hp=0;
  reset=1;
  help=1;
  DisplayScore=1;
  pause=1;
  v = 0;
  oy1=42;
  oy2=42;
  g1 = -17;
  g2 = -17;
  x = 57;
  y = 0;
  score=0;
  load();
}


void collision(){
  if(((oy1+2) <= (cy+2) && (cy+2) <= (oy1+17) && (ox1+2) <= (cx+33) && (cx+33) <= (ox1+33)) || 
    ((oy1+5) <= (cy+20) && (cy+20) <= (oy1+17) && (ox1+2) <= (cx+33) && (cx+33) <= (ox1+33)) ||
    ((oy1+2) <= (cy+2) && (cy+2) <= (oy1+20) && (ox1+3) <= (cx+2) && (cx+2) <= (ox1+33)) ||
    ((oy1+5) <= (cy+20) && (cy+20) <= (oy1+17) && (ox1+2) <= (cx+2) && (cx+2) <= (ox1+33)) ||
    ((oy2+2) <= (cy+2) && (cy+2) <= (oy2+17) && (ox2+2) <= (cx+33) && (cx+33) <= (ox2+33)) || 
    ((oy2+5) <= (cy+20) && (cy+20) <= (oy2+17) && (ox2+2) <= (cx+33) && (cx+33) <= (ox2+33)) ||
    ((oy2+2) <= (cy+2) && (cy+2) <= (oy2+20) && (ox2+3) <= (cx+2) && (cx+2) <= (ox2+33)) ||
    ((oy2+5) <= (cy+20) && (cy+20) <= (oy2+17) && (ox2+2) <= (cx+2) && (cx+2) <= (ox2+33))){

    getScore();
    
  }
}