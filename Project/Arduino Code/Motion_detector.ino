long unsigned int lowIn;
long unsigned int pause = 100;
int calibrationTime = 15;
boolean lockLow = true;
boolean takeLowTime;
String data;
int Pir = 2;
int Speaker = 10;
int Red = 5;
int Green = 7;

void setup() 
{
    Serial.begin(9600);
    pinMode(Pir,INPUT);
    pinMode(Speaker, OUTPUT);
    pinMode(Red, OUTPUT);
    pinMode(Green, LOW);  

    Serial.print("Calibrating PIR sensor");
    for(int i = 0; i <calibrationTime; i++)
      {
          Serial.print("*");
          delay(100);
      }
    Serial.println("Finished");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}
void playTone(long dur, int freq)
{
    dur *= 10000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < dur)
    {
        digitalWrite(Speaker, HIGH);
        delayMicroseconds(period /2);
        digitalWrite(Speaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

void loop() 
{
    if(Serial.available())
    {
        Serial.read();
        {
          data = "Start";
            if(digitalRead(Pir) == HIGH)
            {
              digitalWrite(Red, HIGH);
              playTone(30, 160);
                if(lockLow)
                {
                  lockLow = false;
                  Serial.println("-- -- --");
                  Serial.println("Someone in your ROOM");
                  Serial.print(millis()/10000);
                  Serial.println(" sec");
                  delay(100);
                }
              takeLowTime = true;
            }
            if(digitalRead(Pir) == LOW)
            {
              digitalWrite(Green, HIGH);
              digitalWrite(Red, LOW);
              playTone(0, 0);
                if(takeLowTime)
                {
                  lowIn = millis();
                  takeLowTime = false;
                }
                if(!lockLow && millis() - lowIn > pause)
                {
                  lockLow = true;
                  Serial.print("Someone get out your Room");
                  Serial.print((millis()-pause)/1000);
                  Serial.println(" sec");
                  delay(300);    
                }
            }
        }
    }  
    else
    Serial.read();
    {
      data = "Stop";
      Serial.end();
    }
}
