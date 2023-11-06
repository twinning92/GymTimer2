#include "Display.h"

Display *Display::instance = nullptr;

uint16_t Display::ticks = 0;
uint8_t Display::string_index = 0;

Segment::Segment(CRGB *leds, char segment_designator, uint8_t num_leds_per_segment, uint16_t segment_led_offset, uint8_t segment_led_mask)
{
    this->leds = leds;
    this->segment_designator = segment_designator;
    this->num_leds_per_segment = num_leds_per_segment;
    this->start_index = segment_led_offset;
    this->segment_led_mask = segment_led_mask;
}

void Segment::update_segment(bool on, CRGB colour)
{
    for (int led_idx = this->start_index; led_idx < this->start_index + this->num_leds_per_segment; led_idx++)
    {
        if (on)
        {
            leds[led_idx] = colour;
        }
        else
        {
            leds[led_idx] = CRGB::Black;
        }
    }
}

Digit::Digit(CRGB *leds, uint16_t start_index) : segments{
                                                     Segment(leds, 'A', 8, start_index + 0 * 8, 0b01000000),
                                                     Segment(leds, 'B', 9, start_index + 1 * 8, 0b00100000),
                                                     Segment(leds, 'C', 8, start_index + 1 * 8 + 1 * 9, 0b00010000),
                                                     Segment(leds, 'D', 8, start_index + 2 * 8 + 1 * 9, 0b00001000),
                                                     Segment(leds, 'E', 9, start_index + 3 * 8 + 1 * 9, 0b00000100),
                                                     Segment(leds, 'F', 8, start_index + 3 * 8 + 2 * 9, 0b00000010),
                                                     Segment(leds, 'G', 9, start_index + 4 * 8 + 2 * 9, 0b00000001)}
{
}

void Digit::update_digit(uint8_t digit_to_render, CRGB colour)
{
    current_value = digit_to_render;
    uint8_t display_mask = digit_segment_mappings[digit_to_render];
    for (int i = 0; i < 7; i++)
    {
        bool segment_activate = (segments[i].segment_led_mask & display_mask) != 0;
        segments[i].update_segment(segment_activate, colour);
        // //Serial.printf("Segment letter: %c, start index: %d\n", segments[i].segment_designator, segments[i].start_index);
    }
}

Display::Display() : digits{Digit(leds, 0 * LEDS_PER_DIGIT), Digit(leds, 1 * LEDS_PER_DIGIT), Digit(leds, 2 * LEDS_PER_DIGIT), Digit(leds, 3 * LEDS_PER_DIGIT), Digit(leds, 4 * LEDS_PER_DIGIT), Digit(leds, 5 * LEDS_PER_DIGIT)}
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(255);
}

void Display::write_string(String string, uint8_t length, CRGB colour, bool blink)
{
    string.toLowerCase();
    // Serial.printf("Printing: \n");
    for (int i = 0; i < length; i++)
    {
        switch (string.charAt(i))
        {
            // Basically need to reverse the display, string comes in left-right but digit mappings are right-left
        case 'a':
            update_display(5 - i, 10, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'b':
            update_display(5 - i, 11, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'c':
            update_display(5 - i, 12, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'd':
            update_display(5 - i, 13, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'e':
            update_display(5 - i, 14, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'n':
            update_display(5 - i, 15, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'o':
            update_display(5 - i, 16, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'r':
            update_display(5 - i, 17, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 't':
            update_display(5 - i, 18, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'i':
        case 'l':
            update_display(5 - i, 19, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'f':
            update_display(5 - i, 20, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'u':
            update_display(5 - i, 21, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'p':
            update_display(5 - i, 22, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'j':
            update_display(5 - i, 23, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 's':
            update_display(5 - i, 24, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case ' ':
            update_display(5 - i, 25, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case '_':
            update_display(5 - i, 26, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case '-':
            update_display(5 - i, 27, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case 'y':
            update_display(5 - i, 28, colour, blink);
            // Serial.printf("%d: %c\n", i, string.charAt(i));
            break;
        case '5':
            update_display(5 - i, 5, colour, blink);
            break;
        case '7':
            update_display(5 - i, 7, colour, blink);
            break;
        case 'g':
            update_display(5 - i, 29, colour, blink);
            break;
        case 'h':
            update_display(5 - i, 30, colour, blink);
            break;
        case 'k':
            update_display(5 - i, 31, colour, blink);
            break;
        case 'q':
            update_display(5 - i, 32, colour, blink);
            break;
        case 'v':
            update_display(5 - i, 33, colour, blink);
            break;
        case 'x':
            update_display(5 - i, 34, colour, blink);
            break;
        case 'z':
            update_display(5 - i, 35, colour, blink);
            break;
        case '0':
            update_display(5 - i, 0, colour, blink);
            break;
        default:
            clear_digit(5 - i);
            break;
        }
    }
}

void Display::update_display(uint8_t position, uint8_t number_to_render, CRGB colour)
{
    digits[position].update_digit(number_to_render, colour);
}

void Display::update_display(uint8_t position, uint8_t number_to_render, CRGB colour, bool blink)
{
    if (blink)
    {
        static unsigned long previous_time = 0;
        static bool light_on = true;

        unsigned long current_time = millis();

        if (current_time - previous_time >= 500) // 500 ms has passed
        {
            previous_time = current_time; // Save the last toggle time
            light_on = !light_on;         // Toggle the LED state
        }

        if (light_on)
        {
            update_display(position, number_to_render, colour);
        }
        else
        {
            clear_digit(position);
        }
    }
    else
    {
        update_display(position, number_to_render, colour);
    }
}

void Display::toggle_colon(CRGB colour)
{
    leds[NUM_LEDS - 4] = colour;
    leds[NUM_LEDS - 3] = colour;
    leds[NUM_LEDS - 2] = colour;
    leds[NUM_LEDS - 1] = colour;
}

void Display::clear_colon()
{
    leds[NUM_LEDS - 4] = CRGB::Black;
    leds[NUM_LEDS - 3] = CRGB::Black;
    leds[NUM_LEDS - 2] = CRGB::Black;
    leds[NUM_LEDS - 1] = CRGB::Black;
}

void Display::clear_digit(uint8_t position)
{
    digits[position].update_digit(0, CRGB::Black);
}

Display *Display::get_instance()
{
    if (instance == nullptr)
    {
        instance = new Display();
    }
    return instance;
}

void Display::push_to_display()
{
    FastLED.show();
}

void Display::scroll_string(String scroll, uint8_t length, CRGB colour)
{
    // TODO: Start scroll words fully displayed on the screen.
    scroll.toLowerCase();
    ticks++;
    if (ticks == 25)
    {
        ticks = 0;
        digits[5].update_digit(digits[4].current_value, colour);
        digits[4].update_digit(digits[3].current_value, colour);
        digits[3].update_digit(digits[2].current_value, colour);
        digits[2].update_digit(digits[1].current_value, colour);
        digits[1].update_digit(digits[0].current_value, colour);

        digits[0].update_digit(get_char_index(scroll.charAt((string_index++) % length)), colour);
    }
}

void Display::clear_display()
{
    write_string("      ", 6, CRGB::Black);
    push_to_display();
}

void Display::reset_scroll()
{
    this->ticks = 0;
    this->string_index = 0;
}

uint8_t Display::get_char_index(char character)
{
    switch (character)
    {
    // Basically need to reverse the display, string comes in left-right but digit mappings are right-left
    case 'a':
        return 10;
    case 'b':
        return 11;
    case 'c':
        return 12;
    case 'd':
        return 13;
    case 'e':
        return 14;
    case 'n':
        return 15;
    case 'o':
        return 16;
    case 'r':
        return 17;
    case 't':
        return 18;
    case 'i':
    case 'l':
        return 19;
    case 'f':
        return 20;
    case 'u':
        return 21;
    case 'p':
        return 22;
    case 'j':
        return 23;
    case 's':
        return 24;
    case ' ':
        return 25;
    case '_':
        return 26;
    case '-':
        return 27;
    case 'y':
        return 28;
    case '5':
        return 5;
    case '7':
        return 7;
    case 'g':
        return 29;
    case 'h':
        return 30;
    case 'k':
        return 31;
    case 'q':
        return 32;
    case 'v':
        return 33; // pretty bad v
    case 'x':
        return 34;
    case 'z':
        return 35;
    case '0':
        return 0;
    default:
        return 25; // space
    }
}
