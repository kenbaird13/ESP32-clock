/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid     = "CC-Guest";
const char *password = "SlowRust46";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
}

void loop() {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);

  int hour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(hour);

  int minute = timeClient.getMinutes();
  Serial.print("Minutes: ");
  Serial.println(minute);

  int second = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(second);

  String weekDay = weekDays[timeClient.getDay()];
  Serial.print("Week Day: ");
  Serial.println(weekDay);

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  Serial.print("Month day: ");
  Serial.println(monthDay);

  int month = ptm->tm_mon + 1;
  Serial.print("Month: ");
  Serial.println(month);

  String monthName = months[month - 1];
  Serial.print("Month name: ");
  Serial.println(monthName);

  int year = ptm->tm_year + 1900;
  Serial.print("Year: ");
  Serial.println(year);

  //Print complete date:
  String date = String(year) + "-" + String(month) + "-" + String(monthDay);
  Serial.print(" date: ");
  Serial.println(date);

  Serial.println("");
  delay(2000);
  if (((month >= 3 && monthDay >= 14) || (month > 3)) && ((month <= 11 && monthDay <= 7) || (month < 11)) && (hour >= 2)) {
    timeClient.setTimeOffset(-25200);
    Serial.println("daylight savings time");
  } else {
    timeClient.setTimeOffset(-28800);
  }
}