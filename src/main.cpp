#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include "aowlyf_logo.h"
#include <math.h>

#define TFT_BL 21

#define I2C_SLAVE_ADDRESS 0x08
#define I2C_SDA 27
#define I2C_SCL 22

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite logoSprite = TFT_eSprite(&tft);

volatile bool newData = false;

float temps[4] = {0, 0, 0, 0};
float receivedTemps[4] = {0, 0, 0, 0};

unsigned long lastUpdate = 0;

void receiveEvent(int bytes);
void showSplashLogo(uint32_t durationMs);
void drawBackground();
void drawHeader();
void drawCards();
void drawCard(int x, int y, int w, int h, String title, float temp);
void drawStatusBar();

void setup()
{
    Serial.begin(115200);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    tft.init();
    tft.setRotation(1);

    showSplashLogo(3000);

    drawBackground();
    drawHeader();
    drawCards();
    drawStatusBar();

    Wire.begin((uint8_t)I2C_SLAVE_ADDRESS, I2C_SDA, I2C_SCL, 100000);
    Wire.onReceive(receiveEvent);

    Serial.println("CYD I2C Slave Ready");
}

void loop()
{
    if (newData)
    {
        noInterrupts();
        memcpy(temps, (const void*)receivedTemps, sizeof(temps));
        newData = false;
        interrupts();

        Serial.println("Temperature data received");
    }

    if (millis() - lastUpdate > 1000)
    {
        lastUpdate = millis();
        drawCards();
        drawStatusBar();
    }
}

void receiveEvent(int bytes)
{
    if (bytes == sizeof(receivedTemps))
    {
        byte buffer[sizeof(receivedTemps)];

        for (int i = 0; i < sizeof(receivedTemps); i++)
        {
            if (Wire.available())
            {
                buffer[i] = Wire.read();
            }
        }

        memcpy((void*)receivedTemps, buffer, sizeof(receivedTemps));
        newData = true;
    }
    else
    {
        while (Wire.available())
        {
            Wire.read();
        }
    }
}

void showSplashLogo(uint32_t durationMs)
{
    unsigned long startTime = millis();

    while (millis() - startTime < durationMs)
    {
        unsigned long elapsed = millis() - startTime;

        tft.fillScreen(TFT_WHITE);

        // Logo size and position
        int logoW = 160;
        int logoH = 120;

        int logoX = (320 - logoW) / 2;
        int logoY = 35;

        // Draw logo
        tft.pushImage(
            logoX,
            logoY,
            logoW,
            logoH,
            aowlyf_logo
        );

        // Loading text
        tft.setTextDatum(MC_DATUM);

        tft.setTextSize(1);

        tft.setTextColor(
            TFT_DARKGREY,
            TFT_WHITE
        );

        tft.drawString(
            "Starting System...",
            160,
            195
        );

        // Loading bar dimensions
        int barX = 60;
        int barY = 215;
        int barW = 200;
        int barH = 14;

        // Draw loading bar border
        tft.drawRoundRect(
            barX,
            barY,
            barW,
            barH,
            7,
            TFT_LIGHTGREY
        );

        // Calculate progress width
        int progress = map(
            elapsed,
            0,
            durationMs,
            0,
            barW - 4
        );

        // Fill loading bar
        tft.fillRoundRect(
            barX + 2,
            barY + 2,
            progress,
            barH - 4,
            5,
            tft.color565(0, 120, 255)
        );

        // Calculate percentage
        int percentage = map(
            elapsed,
            0,
            durationMs,
            0,
            100
        );

        if (percentage > 100)
            percentage = 100;

        // Display percentage text
        tft.setTextSize(1);

        tft.setTextColor(
            TFT_BLACK,
            TFT_WHITE
        );

        String percentText =
            String(percentage) + "%";

        tft.drawString(
            percentText,
            160,
            233
        );

        delay(30);
    }

    tft.fillScreen(TFT_BLACK);

    delay(150);
}

void drawBackground()
{
    for (int y = 0; y < 240; y++)
    {
        uint16_t color = tft.color565(5, y / 3, 80 + y / 4);
        tft.drawFastHLine(0, y, 320, color);
    }

    tft.fillCircle(270, 30, 55, tft.color565(0, 100, 160));
    tft.fillCircle(45, 215, 65, tft.color565(20, 70, 120));
}

void drawHeader()
{
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE);

    tft.setTextSize(2);
    tft.drawString("Temperature Monitor", 160, 18);

    tft.setTextSize(1);
    tft.drawString("CYD ESP32 I2C SLAVE", 160, 40);
}

void drawCards()
{
    drawCard(15, 60, 135, 60, "Sensor 1", temps[0]);
    drawCard(170, 60, 135, 60, "Sensor 2", temps[1]);

    drawCard(15, 130, 135, 60, "Sensor 3", temps[2]);
    drawCard(170, 130, 135, 60, "Sensor 4", temps[3]);
}

void drawCard(int x, int y, int w, int h, String title, float temp)
{
    uint16_t cardBg = tft.color565(15, 35, 65);

    tft.fillRoundRect(x, y, w, h, 12, cardBg);
    tft.drawRoundRect(x, y, w, h, 12, tft.color565(80, 180, 255));

    tft.setTextDatum(TL_DATUM);

    tft.setTextSize(1);
    tft.setTextColor(tft.color565(160, 220, 255), cardBg);
    tft.drawString(title, x + 12, y + 8);

    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, cardBg);

    tft.drawFloat(temp, 1, x + 20, y + 30);
    tft.drawString(" C", x + 85, y + 30);
}

void drawStatusBar()
{
    int x = 70;
    int y = 205;
    int w = 180;
    int h = 22;

    uint16_t bg = tft.color565(45, 95, 160);

    tft.fillRoundRect(x, y, w, h, 8, bg);

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, bg);

    tft.drawString("I2C SLAVE ACTIVE 0x08", x + w / 2, y + h / 2);
}