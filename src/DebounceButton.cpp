#include "DebounceButton.h"

DebounceButton::DebounceButton(PinName pin, int threshold)
    : _pin(pin), _state(false), _lastRaw(_pin.read()), _count(0), _threshold(threshold) {
    _pin.mode(PullUp);  
}

void DebounceButton::sample() {
    bool raw = _pin.read();
    if (raw == _lastRaw) {
        if (_count < _threshold) {
            _count++;
            if (_count >= _threshold) {
                _state = (raw == 0);  
            }
        }
    } else {
        _lastRaw = raw;
        _count = 0;
    }
}

bool DebounceButton::read() const {
    return _state;
}
