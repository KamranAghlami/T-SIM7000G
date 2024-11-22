#include "core/application.h"

#include <iostream>
#include <fstream>
#include <string>

#include <Arduino.h>
#include <esp_log.h>

constexpr const char *LOG_TAG = "example";
constexpr const uint8_t PIN_LED = 12;

class example : public application
{
public:
    example()
    {
        Serial.begin(115200);

        pinMode(PIN_LED, OUTPUT);
        digitalWrite(PIN_LED, HIGH);
    }

    ~example()
    {
    }

private:
    void on_create() override
    {
        std::ifstream file("/test.txt");

        if (!file.is_open())
        {
            ESP_LOGE(LOG_TAG, "couldn't open \"/test.txt\", forgot to build and upload filesystem image?");

            return;
        }

        std::string line;

        while (std::getline(file, line))
            ESP_LOGI(LOG_TAG, "%s", line.c_str());

        file.close();
    }

    void on_update(float timestep) override
    {
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));

        delay(500);
    }
};

application *create_application()
{
    return new example();
}
