

struct timer {
  void (*callback)();       // callback for the timer
  unsigned long  interval;  // interval between callbacks, in ms
  unsigned long timeStamp;  // last time callback was called

  // set the callback and interval all at once. Should this be begin()?
  void set(void (*callback)(), long int interval) {
    this->callback = callback;
    this->interval = interval;
  }


  // check the timer, call the callback if the interval has passed:
  boolean check() {
    boolean result = false;
    if (millis() - this->timeStamp > this->interval) {
      this->callback();
      this->timeStamp = millis();
      result = true;
    }
    return result;
  }
};

typedef struct timer Timer;

