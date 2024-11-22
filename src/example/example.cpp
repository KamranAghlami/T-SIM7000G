#include "core/application.h"

#include <iostream>
#include <fstream>
#include <string>

#include <Arduino.h>
#include <esp_log.h>

constexpr const char *TAG = "example";

class example : public application
{
public:
    example()
    {
        Serial.begin(115200);

        std::ifstream file("/test.txt");

        if (!file.is_open())
        {
            ESP_LOGE(TAG, "couldn't open \"/test.txt\", forgot to build and upload filesystem image?");

            return;
        }

        std::string line;

        while (std::getline(file, line))
            ESP_LOGI(TAG, "%s", line.c_str());

        file.close();
    }

    ~example()
    {
    }

private:
    void on_update(float timestep) override
    {
    }
};

application *create_application()
{
    return new example();
}
