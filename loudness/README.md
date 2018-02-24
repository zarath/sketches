# loudness

Toggles a LED if level of loudness exceed given threshold.

Loudness level is captured with the [Groove Loudness Sensor][1].

The values are squared to represent the energy of the input
Signal and low pass filtered via a small ring buffer.

Timing is implemented using the Timer library
from [Jack Christensen][2].


[1]: http://wiki.seeed.cc/Grove-Loudness_Sensor/
[2]: https://github.com/JChristensen/Timer
