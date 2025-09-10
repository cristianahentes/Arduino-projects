#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//coloana, linie
int secretNumar;
char userinput;

void setup(){
  Serial.begin(9600);
  //sa se genereze un numar aleator
  randomSeed(analogRead(A0));
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("JOC GHICESTE NR");
  delay(1000);
  lcd.clear();
  lcd.print("Introdu un nr");
  lcd.setCursor(0, 1);
  lcd.print("intre 1 si 9");
  delay(1000);
  lcd.clear();
  delay(5000);

secretNumar=random(1,10);
}

void loop(){
if (Serial.available()>0){
  userinput=Serial.read();
  lcd.setCursor(0, 0);
  lcd.print("Ai introdus nr:");
  lcd.setCursor(0, 1);
  lcd.print(userinput);
  delay(5000);
  lcd.clear();
  if(userinput>='1' && userinput<='9'){
    lcd.setCursor(0, 0);
    lcd.print("Nr ok");
    delay(3000);
    lcd.clear();
    int guess =userinput - '0';
    if(guess == secretNumar){
      lcd.setCursor(0, 0);
      lcd.print("Corect! Ai ghicit");
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print("Nu ai ghicit");
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nr ales era:");
      lcd.setCursor(0, 1);
      lcd.print(secretNumar);
    }

  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("Nr introdus>9");
  }

}
}
// void setup() {
//   // put your setup code here, to run once:
// lcd.init();
// lcd.backlight();
// lcd.clear();
// lcd.setCursor(0, 0);
// lcd.print("eu eu tu tu el el voi voi noi noi");
// //lcd.setCursor(0,1);
// //lcd.print("EU am scris");
// }

// void loop() {
//   // put your main code here, to run repeatedly:

// lcd.scrollDisplayLeft();
// delay(1000);
// }

