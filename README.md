# Generic Switch Driver

Generic, portable, multi-instance switch driver.

## Overview

This HAL-mediated custom switch driver permits ease of use that is designed to be platform-independent. Debouncing is handled internally provided that the object is polled at a user-defined interval.

## Usage

The switch header and source rely on an external user-defined hardware abstraction layer (HAL) called `hal.h` which defines the necessary calls in the `HAL` namespace. Namely, a GPIO pin object with `pinMode()` and `digitalRead()` methods. The `pinMode()` method should set the GPIO pin to input when given a value `GPIO_INPUT`.

To properly detect switch presses and releases, the `poll()` method must be called at an interval declared at the object's instantiation (5ms if none specified). This may be accomplished simply with a timer callback.

Once triggered by a switch event, the methods `pressed()` and/or `released()` will return true until reset by the `clearState()` method.

### Example

```cpp
#include "switch.h"

...

// Instantiate switch
PeripheralIO::Switch button(PIN_A7);

...

int main()
{

...
    // Init switch and its timer
    button.init();
    someTimer.start();
...

    // Check switch state
    if (button.released())
    {
        button.clearState();
        
        // Do something
    }
...

}

// Should be triggered every 5ms
someTimerISR()
{
    button.poll();
}

...
```

## License

MIT © 2024 John Greenwell