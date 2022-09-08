#include <SPI.h>  
#include <MFRC522.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 6 
#define LED_R 7 
#define BUZZER 8
MFRC522 mfrc522(SS_PIN, RST_PIN);   
Servo s1;
  
void setup()   
 {  
  Serial.begin(9600);  
  SPI.begin();    
  lcd.init();             
  lcd.backlight();  
  mfrc522.PCD_Init();  
  s1.attach(3); //servo pin   
  pinMode(LED_G, OUTPUT);  
  pinMode(LED_R, OUTPUT);  
  pinMode(BUZZER, OUTPUT);  
  noTone(BUZZER);  
  
  Serial.println("Put your card to the reader...");  
  Serial.println();  
  lcd.setCursor(0,0);  
  lcd.print("Please put your ");
  lcd.setCursor(0,1);  
  lcd.print("card here...");  
 }


void loop()   
 {  
  if ( ! mfrc522.PICC_IsNewCardPresent())  // new cards   
  {  
   return;  
  }      
  if ( ! mfrc522.PICC_ReadCardSerial()) // Select the cards  
  {  
   return;  
  }  
  
  Serial.print("UID tag :");  //Show UID on serial monitor
  String content= "";  
  byte letter;  
  for (byte i = 0; i < mfrc522.uid.size; i++)   
  {  
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
    Serial.print(mfrc522.uid.uidByte[i], HEX);  
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  
  }  
  Serial.println();  
  Serial.print("Message : ");  
  content.toUpperCase();  
  if (content.substring(1) == "CA CB E9 81") 
    
  {
      
     Serial.println("Authorized access");  
     Serial.println();  
     lcd.setCursor(0,0);  
     lcd.print(" CARD IS VALID      ");  
     lcd.setCursor(0,1);  
     lcd.print("Opening the Door   ");  
     digitalWrite(LED_G, HIGH); //Green LED ON  
     s1.write(0);  
     delay(3000);  
     s1.write(90);  
     lcd.setCursor(0,1);  
     lcd.print("closing the Door   ");  
     lcd.clear();
     digitalWrite(LED_G, LOW);
     delay(2000);  
     lcd.setCursor(0,0);  
     lcd.print("Please put your");
     lcd.setCursor(0,1);
     lcd.print("card here...");  
  }  
  
  else   
  { 
    lcd.clear(); 
    Serial.println("CARD IS INVALID");  
    lcd.print("   Warning!");
    lcd.setCursor(0,1); 
    lcd.print("Card is invalid..");  
    digitalWrite(LED_R, HIGH);   
    tone(BUZZER, 300);      
    delay(2000);  
    digitalWrite(LED_R, LOW);  
    noTone(BUZZER);  
    lcd.setCursor(0,1); 
    lcd.clear();
    lcd.print("Please put your");
    lcd.setCursor(0,1);
    lcd.print("card here..."); 
     
  }  
 }  
