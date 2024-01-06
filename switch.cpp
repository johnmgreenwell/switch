//--------------------------------------------------------------------------------------------------------------------
// Name        : switch.cpp
// Purpose     : Switch Driver Class
// Description : This source file accompanies header file switch.h.
// Language    : C++
// Platform    : Portable
// Framework   : Portable
// Copyright   : MIT License 2024, John Greenwell
//--------------------------------------------------------------------------------------------------------------------

#include "switch.h"

namespace PeripheralIO
{

Switch::Switch(uint8_t pin, bool press_logic, uint16_t debounce_ms, 
                    uint16_t update_interval_ms, uint16_t release_timeout_ms)
: _pin(pin)
, _press_logic(press_logic)
, _timeout_enabled(false)
, _is_held(false)
, _is_pressed(false)
, _is_released(false)
, _debounce_ms(debounce_ms)
, _update_interval_ms(update_interval_ms)
, _release_timeout_ms(release_timeout_ms)
, _counter_min(0)
, _counter_max(0)
, _count(0)
{
    if (0 == _update_interval_ms)
        _update_interval_ms = 1;

    _counter_min = _debounce_ms / _update_interval_ms;

    if (0 != _release_timeout_ms)
    {
        _timeout_enabled = true;
        _counter_max = _release_timeout_ms / _update_interval_ms;
    }

    _pin.pinMode(GPIO_INPUT);
}

void Switch::init()
{
    _pin.pinMode(GPIO_INPUT);
}

bool Switch::pressed()
{
    return _is_pressed;
}

bool Switch::released()
{
    return _is_released;
}

void Switch::clearState()
{
    _is_pressed = false;
    _is_released = false;
}

void Switch::poll()
{
    if (_pin.digitalRead() == _press_logic)
    {
        ++_count;

        if ((_count > _counter_min) && (!_is_held))
        {
            _is_pressed = true;
            _is_held    = true;
        }
    }
    else if (_is_held)
    {
        if ((_count < _counter_max) || !_timeout_enabled)
        {
            _is_released = true;
        }

        _count = 0;
        _is_held = false;
    }
    else
    {
        _count = 0;
    }
}

}

// EOF
