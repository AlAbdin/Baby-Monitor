
//******************************************************************************************
//File: baby_monitor.ino
//Programmer: Alaa Abdin
//Date: 4/20/2019
//Description: Arduino uno code to run the functionality of the intended device
//******************************************************************************************

#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs=12,en=11,d4=10,d5=9,d6=8,d7=7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int interruptPin= 2;
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypa
//keymapdefines the key pressed according to the row and columns just as it appears on the keypad
char keymap[numRows][numCols]= 
{
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 //Code that shows the keypad connections to the Arduino pins
  byte rowPins[numRows] = {A5,A4,A3,A2}; //Rows 0 to 3
  byte colPins[numCols]= {6,5,4,3}; //Columns 0 to 
  
 // initializes an instance of the Keypad class
  Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


// set up the variables.
float Temp=0; 
float AV = 0;
float CT = 0;
float degree = 0;
float faren = 0;
float key = 0;
float count = 0;
// Defining the notes
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
// Set up the melody
int melody[] = {
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4,NOTE_E4, 0, NOTE_D4, NOTE_D4, NOTE_D4, 0 , NOTE_E4, NOTE_E4, NOTE_E4
};
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
};


void setup() {
  
  //pinMode(interruptPin, INPUT); 
  attachInterrupt(0, fall, RISING);
  
  pinMode(1,INPUT);
  pinMode(A2,OUTPUT);
  digitalWrite(A2, HIGH);
  pinMode(A3,OUTPUT);
  digitalWrite(A3, HIGH);
  pinMode(A4,OUTPUT);
  digitalWrite(A4, HIGH);
  pinMode(A5,OUTPUT);
  digitalWrite(A5, HIGH);
  Serial.begin(9600);
  lcd.begin(16,2);
 


}

void loop() {
   // this checks for the temperature
  
 Temp = analogRead(1);
 delay(1000);
 AV=(Temp*5000)/1024;
 CT=((AV-500)/10);
 Serial.println(CT);
 faren = (CT*9/5)+32;
 lcd.setCursor(0,0);
  
 
  
   
   
 
   
 
  // this section play the music
  for (int thisNote = 0; thisNote < 15; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(13, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(15);
    // To  display the tempreture.
    if (count == 1){
    lcd.setCursor(0,0);
    lcd.print (CT);
      lcd.print("  C");
  }
  if (count ==0){
    lcd.setCursor(0,0);
    lcd.print (faren);
    lcd.print("  F");
  }
    
    char keypressed= myKeypad.getKey();
    
 if (keypressed == NO_KEY) {
   Serial.println(keypressed);
  
       
     }
  if (keypressed == '1'|| keypressed == '2'){ 
   
    if (keypressed == '1'){
     count = 1;
    }
    
   
    if (keypressed == '2'){
     count = 0;
    }
      
   
   
   
   
  if (count == 1){
    lcd.setCursor(0,0);
    lcd.print (CT );
    lcd.print("  C");
  }
  if (count ==0){
    lcd.setCursor(0,0);
    lcd.print (faren);
    lcd.print("  F");
  }
 }
 // To display fever when temprature is 100 or above.
 if (faren>= 100) {
    
    lcd.setCursor(0,1);
  lcd.print("Fever");
  }
  else {
   lcd.setCursor(0,1);
   lcd.print("      ");
    
  }
  
   
 }
    delay(1000);
}
// If motion detected music is going to stop and display Falling
void fall() { 
  noTone(13);
  lcd.clear();
  lcd.print("Falling"); 
  delay(100000);
}
