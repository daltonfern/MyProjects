 import processing.serial.*;
 import gifAnimation.*;
 import processing.sound.*;
 SoundFile file;

Serial myPort;

int data;
int data2;
int x = 280;
int herox = 100;
int enemyx = 800;
int enemy2x = 1600;
int enemy3x = 2000;
int enemy4x = 2400;
int enemy5x = 3200;
int enemy6x = 4000;
int enemy7x = 5000;
int enemy8x = 5500;
int enemy9x = 6600;
int enemy10x = 7000;
int req = 400;
int heroy = 380;
int start;
int score = 0;
int time = millis();
float TextFont;
int s;



PImage background;
PImage hero;
PImage enemy;
PImage enemy2;
PImage enemy3;
PImage enemy4;
PImage enemy5;
PImage enemy6;
PImage enemy7;
PImage enemy8;
PImage enemy9;
PImage enemy10;
PImage fire;

void setup() {
  size(900, 500); 
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('\n');
  
  background = loadImage("background.png");
  hero = loadImage("hero.png");
  enemy = loadImage("enemy.png");
  enemy2 = loadImage("enemy.png");
  enemy3 = loadImage("enemy.png");
  enemy4 = loadImage("enemy.png");
  enemy5 = loadImage("enemy.png");
  enemy6 = loadImage("enemy.png");
  enemy7 = loadImage("enemy.png");
  enemy8 = loadImage("enemy.png");
  enemy9 = loadImage("enemy.png");
  enemy10 = loadImage("enemy.png");
  fire = loadImage("fire.gif");

file = new SoundFile(this, "sound.wav");
  file.play();
  file.stop();
  file.loop();
  
    start = millis();
    
}

void serialEvent (Serial myPort){
 data = myPort.read();
  while(data == 0);{
   image(fire,x+2000,390);}
 while(data == 1); {
   image(fire,x,390);
   s = s+1;
   if(x == enemyx){
     enemyx = 900000;
     score = score+1;
   }
      if(x == enemy2x){
     enemy2x = 900000;
     score = score+1;
   }
      if(x == enemy3x){
     enemy3x = 900000;
     score = score+1;
   }
      if(x == enemy4x){
     enemy4x = 900000;
     score = score+1;
   }
      if(x == enemy5x){
     enemy5x = 900000;
     score = score+1;
   }
      if(x == enemy6x){
     enemy6x = 900000;
     score = score+1;
   }
      if(x == enemy7x){
     enemy7x = 900000;
     score = score+1;
   }
      if(x == enemy8x){
     enemy8x = 900000;
     score = score+1;
   }
      if(x == enemy9x){
     enemy9x = 900000;
     score = score+1;
   }
      if(x == enemy10x){
     enemy10x = 900000;
     score = score+1;
   }
 }
 
}

void draw() {
  imageMode(CENTER);
  image(background, width/2, height/2);
  image(hero,herox,heroy);
  image(enemy,enemyx,395);
    image(enemy2,enemy2x,395);
      image(enemy3,enemy3x,395);
        image(enemy4,enemy4x,395);
          image(enemy5,enemy5x,395);
            image(enemy6,enemy6x,395);
              image(enemy7,enemy7x,395);
                image(enemy8,enemy8x,395);
                  image(enemy9,enemy9x,395);
                  image(enemy10,enemy10x,395);
   image(fire,2000,390);
   
   if(s == 200 || s == 400 || s== 600 || s == 800 || s== 1000 || s == 1200 || s== 1400 || s == 1600 || s== 1800 || s == 2000 || s== 2200 || s == 2400 || s== 2600 || s == 3200 || s== 3000 || s == 3200 || s== 3400 || s == 3600 || s== 3800 || s == 4000 || s== 4200       ){
    score = score-1; 
   }
     
  if (herox == enemyx-71){
   herox = 90000000; 
  }
    if (herox == enemy2x-71){
   herox = 90000000; 
  }
    if (herox == enemy3x-71){
   herox = 90000000; 
  }
    if (herox == enemy5x-71){
   herox = 90000000; 
  }
    if (herox == enemy6x-71){
   herox = 90000000; 
  }
    if (herox == enemy4x-71){
   herox = 90000000; 
  }
    if (herox == enemy7x-71){
   herox = 90000000; 
  }
    if (herox == enemy8x-71){
   herox = 90000000; 
  }
    if (herox == enemy9x-71){
   herox = 90000000; 
  }
    if (herox == enemy10x-71){
   herox = 90000000; 
  }
 
  if (req == 400){ 
  enemyx = enemyx-1;
  enemy2x = enemy2x-1;
  enemy3x = enemy3x-1;
  enemy4x = enemy4x-1;
  enemy5x = enemy5x-1;
  enemy6x = enemy6x-1;
  enemy7x = enemy7x-1;
  enemy8x = enemy8x-1;
  enemy9x = enemy9x-1;
  enemy10x = enemy10x-1;
  }
    
  if (mousePressed && (mouseButton == RIGHT)) {
    herox = herox+1;
    x = x+1;
    
  }
    if (mousePressed && (mouseButton == LEFT)) {
    herox = herox-1;
    x = x-1;
  }
  
 int seconds = (millis() - start) / 1000;
 int minutes = seconds / 60;
 fill(255,255,255);
 
 text((minutes) + ":" + (seconds),870,481);
 
 text("Score =  " + score,50,481);
 
 text("Press E To Exit",770,481);
 
 
 
  if (keyPressed) {
    if (key == 'e' || key == 'E') {
      exit();
    }
  }
}