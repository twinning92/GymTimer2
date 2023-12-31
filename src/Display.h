#pragma once
#include <FastLED.h>

#define LEDS_PER_DIGIT ((4 * 8) + (3 * 9))
#define NUM_LEDS ((LEDS_PER_DIGIT * 6) + 4)
#define NUM_SEGMENTS 7

#define DATA_PIN 15

class Segment
{
public:
    Segment(CRGB *leds, char designator, uint8_t size, uint16_t start_index, uint8_t segment_led_mask);
    void update_segment(bool on, CRGB colour);
    uint8_t segment_led_mask;

    // TODO: These are only public for serial output in update_segements()
    char segment_designator;
    uint16_t start_index;

private:
    Segment() = default;
    CRGB *leds;
    uint8_t num_leds_per_segment;
};

class Digit
{
public:
    Digit(CRGB *leds, uint16_t start_index);
    void update_digit(uint8_t digit_to_render, CRGB colour);
    void show_digit(bool on);

    uint8_t current_value;

private:
    Segment segments[7];
    uint16_t digit_led_offset;

    const uint8_t digit_segment_mappings[50] = {
        0b01111110, // 0 0
        0b01000010, // 1 1
        0b00110111, // 2 2
        0b01100111, // 3 3
        0b01001011, // 4 4
        0b01101101, // 5 5
        0b01111101, // 6 6
        0b01000110, // 7 7
        0b01111111, // 8 8
        0b01101111, // 9 9
        0b01011111, // A 10
        0b01111001, // b 11
        0b00110001, // c 12
        0b01110011, // d 13
        0b00111101, // E 14
        0b01010001, // n 15
        0b01110001, // o 16
        0b00010001, // r 17
        0b00111001, // t 18
        0b01000010, // l,i 19
        0b00011101, // F 20
        0b01110000, // u 21
        0b00011111, // P 22
        0b01110010, // J 23
        0b01101101, // S 24
        0b00000000, // " " 25
        0b00100000, // "_" 26
        0b00000001, // "-" 27
        0b01101011, // "y" 28
        0b01101111, // "g" 29
        0b01011001, // "h" 30
        0b01011011, // "K" 31
        0b01001111, // "q" 32
        0b01110000, // "v" 33 pretty bad v
        0b01011011, // "x" 34
        0b00110111, // "z" 35
    };
};

class Display
{
public:
    static Display *get_instance();
    void push_to_display();
    void scroll_string(String scroll, uint8_t length, CRGB colour);
    void write_string(String string, uint8_t length, CRGB colour, bool blink = false);

    void update_display(uint8_t position, uint8_t number_to_render, CRGB colour = CRGB::Red);
    void update_display(uint8_t position, uint8_t number_to_render, CRGB colour, bool blink);
    void toggle_colon(CRGB colour);
    void clear_colon();
    void clear_digit(uint8_t position);
    void clear_display();
    void reset_scroll();

    uint8_t get_char_index(char character);

private:
    Display();
    static Display *instance;
    Digit digits[6];

    CRGB leds[NUM_LEDS]{CRGB::Red};

    static uint16_t ticks;
    static uint8_t string_index;
};