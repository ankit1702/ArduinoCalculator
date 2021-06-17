#include <LiquidCrystal.h>
#include <Keypad.h>

//LiquidCrystal lcd_name(rs, en, d4, d5, d6, d7);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

long first = 0;
long second = 0;
double total = 0;
int posit = 0 ;
char customKey;
const byte ROWS = 4;
const byte COLS = 4;

//define keypad structure
char keys[ROWS][COLS] = {
{'1','2','3','/'},
{'4','5','6','*'},
{'7','8','9','-'},
{'C','0','=','+'} };

//defining the pins where rows and cols are connected
byte rowPins[ROWS] = {7 ,6 ,5 ,4};
byte colPins[COLS] = {3, 2, 1, 0};

//Initialize the instance of the Keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 


void setup()
{
    lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.clear();
}

void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey) {
    
    case '0' ... '9':
    lcd.setCursor(0,0); 
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    posit++;
    break;
    
    case '+':
  first = (total != 0 ? total : first);
  lcd.setCursor(posit,0);
  lcd.print("+");
  posit++;
  second = SecondNumber();
  total = first + second;
  lcd.setCursor(1,1);
  lcd.print(total);
  first = 0,
  second = 0;
  posit=0;
  break;
    
    case '-':
  first = (total != 0 ? total : first);
  lcd.setCursor(posit,0);
  lcd.print("-");
  posit++;
  second = SecondNumber();
  total = first - second;
  lcd.setCursor(1,1);
  lcd.print(total);
  first = 0,
  second = 0;
  posit=0;
  break;
    
    case '*':
  first = (total != 0 ? total : first);
  lcd.setCursor(posit,0);
  lcd.print("*");
  posit++;
  second = SecondNumber();
  total = first * second;
  lcd.setCursor(1,1); 
  lcd.print(total);
  first = 0,
  second = 0;
  posit=0;
  break;
    
    case '/':
  first = (total != 0 ? total : first);
  lcd.setCursor(posit,0);
  lcd.print("/");
  posit++;
  second = SecondNumber(); lcd.setCursor(1,1);
  second == 0 ? lcd.print("Error") : total = (float)first / (float)second;  
  lcd.print(total);
  first = 0,
  second = 0;
  posit=0;
  break;
    
    case 'C':
    total = 0;
  first = 0;
  second = 0;
  posit = 0;
  lcd.clear();
  break;
  }
}

long SecondNumber()
  {
    while( 1 ) 
    {
    customKey = customKeypad.getKey();
      if(customKey >= '0' && customKey <= '9') 
      {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(posit,0);
      lcd.print(second);
      }
  
      if(customKey == 'C')
      {
      total = 0;
      first = 0;
      second = 0;
      posit = 0;
        lcd.clear();
      break;
      }
      
      if(customKey == '=')
      {
        lcd.setCursor(0,1);
        lcd.print("=");
        posit = total;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("=");
        break;
      }
    }
    return second;
  }
