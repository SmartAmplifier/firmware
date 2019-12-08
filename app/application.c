#include <application.h>

// LED instance
bc_led_t led;

// Button instance
bc_button_t button;

int write = 0;
char str[6];

void mute_set(uint64_t *id, const char *topic, void *value, void *param);
void volume_set(uint64_t *id, const char *topic, void *value, void *param);

static const bc_radio_sub_t subs[] = {
    {"led-strip/-/mute/set", BC_RADIO_SUB_PT_STRING, mute_set, NULL},
    {"led-strip/-/volume/set", BC_RADIO_SUB_PT_STRING, volume_set, NULL}
};

void button_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_PRESS)
    {
        bc_led_set_mode(&led, BC_LED_MODE_TOGGLE);
    }

    // Logging in action
    bc_log_info("Button event handler - event: %i", event);
}

void mute_set(uint64_t *id, const char *topic, void *value, void *param)
{
    bc_log_debug("mute");
    strncpy(str,value,6);
    uint8_t data = atoi( str );
    if(data == 1)
    {
        bc_log_debug("true");
        write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x06, 0x00);
        bc_log_info("i2c %i",write);
    }
    else if (data == 0)
    {
        bc_log_debug("false");
        write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x06, 0x80);
        bc_log_info("i2c %i",write);
    }
    else
    {
        bc_log_debug("error");
    }
}

void volume_set(uint64_t *id, const char *topic, void *value, void *param)
{
    
    bc_log_debug("volume");
    strncpy(str,value,3);
    uint8_t data = atoi( str );
    data = ((data * (-1)) + 213);
    bc_log_debug("data : %i", data);

    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x20, data);
    bc_log_info("volume set %i",write);
}

void application_init(void)
{
    // Initialize logging
    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);
    bc_i2c_init(BC_I2C_I2C0, BC_I2C_SPEED_400_KHZ);

    // Initialize LED
    bc_led_init(&led, BC_GPIO_LED, false, false);
    bc_led_set_mode(&led, BC_LED_MODE_ON);

    // Initialize button
    bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);
    bc_button_set_event_handler(&button, button_event_handler, NULL);

    bc_radio_init(BC_RADIO_MODE_NODE_LISTENING);
    bc_radio_set_subs((bc_radio_sub_t *) subs, sizeof(subs)/sizeof(bc_radio_sub_t));

    bc_radio_pairing_request("Smart-Amplifier", VERSION);
    bc_led_set_mode(&led, BC_LED_MODE_OFF);
}

void application_task(void)
{
    // Logging in action
    bc_log_debug("application_task run");
    bc_log_info("12c write");
   
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x01, 0xA4);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x02, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x03, 0x02);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x05, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x06, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x20, 0x80); //volume +15dB 0x71 0dB 0x80
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x28, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x29, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x2A, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x2B, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x2C, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x30, 0x80);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x41, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x44, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x47, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x51, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x54, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x57, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;
    write = bc_i2c_memory_write_8b(BC_I2C_I2C0, 0x40, 0x75, 0x00);
    bc_log_info("i2c %i",write);
    write = 0;

    // Plan next run this function after 1000 ms
    //bc_scheduler_plan_current_from_now(2000);
}
