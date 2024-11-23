#include "application.h"

#include <cstdint>

#include <assert.h>
#include <esp_timer.h>

#include "hardware/storage.h"

application *application::s_instance = nullptr;

application::application()
{
    assert(s_instance == nullptr);

    s_instance = this;

    hardware::storage::mount(hardware::storage::type::nvs);
    hardware::storage::mount(hardware::storage::type::internal, "");
}

application::~application()
{
    hardware::storage::unmount(hardware::storage::type::internal);
    hardware::storage::unmount(hardware::storage::type::nvs);
}

application *create_application();

void setup()
{
    create_application();

    application::get().on_create();
}

void loop()
{
    static int64_t previous_timestamp = 0;

    auto now = esp_timer_get_time();
    auto timestep = now - previous_timestamp;

    previous_timestamp = now;

    if (timestep < 0)
        timestep = 0;

    application::get().on_update(timestep / 1000000.0f);
}