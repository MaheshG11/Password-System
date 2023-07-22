// there is no servo library here
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Keypad.h>
#include <ESP8266Webhook.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define _SSID "GlobusinternationalSchool"
#define KEY "bC2r4Sanh0VDD0VVo-UM1h"
#define EVENT "Pass"
#define  _PASSWORD "air45316"
Webhook pass(KEY,EVENT);

const byte ROWS=4;
const byte COLS=4;
char keys[ROWS][COLS]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS]={16,0,2,14};                /////////////////////This line is different in code.ino
byte colPins [COLS] = {12,13,15,03};           /////////////////////This line is different in code.ino

Keypad epad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

 
String GenPass(){//generating password and sending them to mail
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Generating");
    lcd.setCursor(0,1);
    lcd.print("Password");
    String Num;
   int i =0;
  while(i<5){
    Num=String(random(0,10))+Num;
    i++;}
pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
  // Trigger with 1 value.
  int response = pass.trigger(Num);
  if(response == 200)
    {Serial.println("OK");
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Password");
   lcd.setCursor(0,1);
   lcd.print("Generated");
   delay(2000);
   lcd.clear();}
  else
    {Serial.println("Failed");}
   
   return Num;}
 
 
 void setup() {
  Serial.begin(115200);
    lcd.begin();
    lcd.clear();
  
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("A-Enter Key ");
  lcd.setCursor(0,1);
  lcd.print("B-Generate Key");
  char customKey = epad.getKey();
  Serial.println(customKey);
  static String a="00000";
if (customKey=='B'){//generating password sending mail
  lcd.clear();
   a=""+GenPass();}
else if (customKey=='A'){//taking input and checking if it matches generated password
  String checkNum="";
  int j=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter key ");
  lcd.cursor();
  lcd.blink();
  while(j<5){
    ESP.wdtDisable();
    char customKey=epad.getKey();
   if (customKey){
    lcd.print(customKey);
     checkNum=checkNum+customKey;
    Serial.println(checkNum);
    j++;}
    else{continue;}
    }
    
    if (checkNum==a){
      lcd.noCursor();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CORRECT");
      delay(2000);
      }
      else {
        lcd.noCursor();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("   INCORRECT");
        lcd.noCursor();
        lcd.noBlink();
        delay(2000);
        }
  }
}
