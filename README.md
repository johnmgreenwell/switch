# Generic Switch Driver

Generic, portable, multi-instance switch driver.

## Overview

This HAL-mediated custom switch driver permits ease of use portable across many platforms.

## Usage

The switch header and source rely on an external user-defined hardware abstraction layer (HAL) called `hal.h` in which defines the necessary calls in the `HAL` namespace. Namely, a GPIO pin object which can be read as necessary.

```cpp
#include <switch.h>

...

// Instantiate switch
PeripheralIO::Switch    button(PIN_A7);

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

// Should trigger every 5ms (switch default refresh)
someTimerISR()
{
    button.poll();
}

...
```

## License

MIT © 2023 John Greenwell