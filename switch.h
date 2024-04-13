//--------------------------------------------------------------------------------------------------------------------
// Name        : switch.h
// Purpose     : Switch Driver Class
// Description : 
//               This class intended for control of generic switch.
//
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
// Requires    : External : N/A
//               Custom   : hal.h - Custom implementation-defined Hardware Abstraction Layer
//--------------------------------------------------------------------------------------------------------------------
#ifndef _SWITCH_H
#define _SWITCH_H

#include "hal.h"

namespace PeripheralIO
{

class Switch
{
    public:
        /**
         * @brief Constructor for Switch object
         * @param pin Pin identifier to which switch is attached
         * @param press_logic Logic level of a pressed switch
         * @param debounce_ms Time in milliseconds to debounce switch, greater than update_interval_ms
         * @param release_timeout_ms Optional timeout after which a release is ignored, use 0 for no timeout
         * @param update_interval_ms Interval in milliseconds between timed calls to switch_state_update()
        */
        Switch(uint8_t pin, bool press_logic=false, uint16_t debounce_ms=20, 
                    uint16_t update_interval_ms=5, uint16_t release_timeout_ms=0);

        /**
         * @brief Initialize switch; should not be necessary if constructor init of pin is reliable
        */
        void init() const;

        /**
         * @brief Check whether switch has been pressed; requires clearState() to reset
         * @return True if button has been pressed, false otherwise
        */
        bool pressed() const;

        /**
         * @brief Check whether switch has been released; requires clearState() to reset
         * @return True if button has been released at interval shorter than timeout, false otherwise
        */
        bool released() const;

        /**
         * @brief Clear state of switch, returning to unpressed/unreleased status
        */
        void clearState();

        /**
         * @brief Get the current raw logical press state of the button
         * @return True for a logic level matching press_logic, false otherwise
        */
        bool getState() const;

        /**
         * @brief Poll the state of the switch at fixed intervals update_interval_ms; facilitates switch
         *        debouncing and press/release detection.
        */
        void poll();

    private:
        HAL::GPIO _pin;
        bool _press_logic;
        bool _timeout_enabled;
        bool _is_held;
        bool _is_pressed;
        bool _is_released;
        uint16_t _debounce_ms;
        uint16_t _update_interval_ms;
        uint16_t _release_timeout_ms;
        uint32_t _counter_min;
        uint32_t _counter_max;
        uint32_t _count;
};

}

#endif // _SWITCH_H

// EOF
