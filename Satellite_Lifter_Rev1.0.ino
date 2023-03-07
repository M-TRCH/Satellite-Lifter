
#define sw1_pin 2 
#define sw2_pin 3 
#define pot_pin A0 
#define in1_pin 9
#define in2_pin 10
#define en1_pin 11
#define en2_pin 12
#define cmd_pin 13
#define sw1 digitalRead(sw1_pin)
#define sw2 digitalRead(sw2_pin)
#define pot analogRead(pot_pin)
#define LED_ON LOW
#define LED_OFF HIGH
 
void setup() 
{
  Serial.begin(9600);
  
  pinMode(sw1_pin, INPUT_PULLUP);
  pinMode(sw2_pin, INPUT_PULLUP);
  pinMode(pot_pin, INPUT);
  
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  pinMode(en1_pin, OUTPUT);
  pinMode(en2_pin, OUTPUT);
  pinMode(cmd_pin, OUTPUT);
  
}

void drive(int spd)
{
  if (spd == 0)
  {
    digitalWrite(en1_pin, LOW);
    digitalWrite(en2_pin, LOW);  
  }
  else
  {
    digitalWrite(en1_pin, HIGH);
    digitalWrite(en2_pin, HIGH);  

    if (spd > 0)
    {
      analogWrite(in1_pin, spd);
      digitalWrite(in2_pin, LOW);
    }
    else
    {
      analogWrite(in2_pin, abs(spd));
      digitalWrite(in1_pin, LOW);
    }
  }
}

void loop() 
{
  int dir1 = sw1;
  int dir2 = sw2;
  int spd = map(pot, 0, 1023, 0, 255);

  if (dir1 && dir2)
  {
    digitalWrite(cmd_pin, LED_OFF);
    drive(0);
  }
  else if (dir1 && !dir2)
  {
    digitalWrite(cmd_pin, LED_ON);
    drive(spd);  
  }
  else if (!dir1 && dir2)
  {
    digitalWrite(cmd_pin, LED_ON);
    drive(-spd);  
  }
  else
  {
    digitalWrite(cmd_pin, LED_OFF);
    drive(0);
  }

  Serial.println(spd);
}


  
