/**
    Bestimmung der Netzfrequenz
    Copyright 2015 by Ralf Th. Pietsch <ratopi@abwesend.de>
    LICENSE: MIT

    SD Card Support: dustinbrun
*/

#include <SPI.h>
#include <SD.h>

#define PROBE_COUNT 50
#define MICROS 1000000.
#define KORREKTUR 1.001341341
//#define KORREKTUR 1.

#define DEBUG 0
#define use_sd 1  // Set to 0 to disable SD
int interval = 50; // Interval to Read the Data

//Pins
const int chipSelect = 10;
const int analog_in = A0;
const int debugled = 2;

int min, max, val, i, j;
float freq;

long start, end;

File data_file;

void setup()
{
  Serial.begin(9600);
  pinMode(debugled, OUTPUT);
  if (use_sd)
  {
    if (!SD.begin(chipSelect))
    {
      Serial.println("SD Card Init failed!");
      digitalWrite(debugled, HIGH);
      while (true);
    }
    else
    {
      Serial.println("SD Card Initialized");
      digitalWrite(debugled, LOW);
    }
  }

  analogReference(INTERNAL);
  Serial.println("Initialisation...");
  for (i = 0; i < 10000; i++)
    analogRead(analog_in);
  period();
  end = micros();
  Serial.println("Starting...");
}

void loop()
{
  start = end;
  min = 1024;
  max = 0;
  for (i = 0; i < PROBE_COUNT; i++)
    period();
  end = micros();
  freq = ((PROBE_COUNT * MICROS * KORREKTUR) / (end - start));
  if (DEBUG)
  {
    Serial.print(min);
    Serial.print(" ");
    Serial.print(max);
    Serial.print(" ");
  }

  if (freq > 45.00 && freq < 55.00)
  {
    if (use_sd)
    {
      data_file = SD.open("data.txt", FILE_WRITE);
      if (data_file)
      {
        digitalWrite(debugled, HIGH);
        data_file.println(freq, 4);
        data_file.close();
        delay(50);
        digitalWrite(debugled, LOW);
      }
      else
        Serial.println("SD Card error!");
    }
    Serial.println(freq,4);
  }
  else
    Serial.println("Ausserhalb der Toleranz");

  delay(interval);
}

void period()
{
  while (analogReadPlus() > 50);
  while (analogReadPlus() < 100);
}

int analogReadPlus()
{
  val = analogRead(analog_in);

  if (val < min)
    min = val;
  if (val > max)
    max = val;

  return val;
}
