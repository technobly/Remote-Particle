#include "Particle.h"

// SerialLogHandler logHandler(LOG_LEVEL_ALL);

#define ON  (1)
#define OFF (0)

int startState = 0;
int trunkState = 0;
int lockState = 0;
int engineTemp = 0;
int STARTPIN = D7;
int TRUNKPIN = D6;
int LOCKPIN = D5;
int UNLOCKPIN = D4;

uint32_t UPDATE_INTERVAL = 10; // in milliseconds
uint32_t FIFTEEN_MINUTES = 60 * 15 * 1000; // in milliseconds

uint32_t lastTime = 0; // in milliseconds
uint32_t startTime = 0; // in milliseconds

int startFunction(String args) {
    if (startState == OFF) {
        startState = ON; // engine started
        startTime = millis();
        digitalWrite(STARTPIN, HIGH); // Double press the start button to start
        delay(500);
        digitalWrite(STARTPIN, LOW);
        delay(1000);
        digitalWrite(STARTPIN, HIGH);
        delay(500);
        digitalWrite(STARTPIN, LOW);
        return 200; // This is checked in the web app controller for validation
    }
    else {
        startState = OFF; // engine stopped
        digitalWrite(STARTPIN, HIGH); // Single press the start button to stop
        delay(500);
        digitalWrite(STARTPIN, LOW);
        return 200; // This is checked in the web app controller for validation
    }
}

int trunkFunction(String args) {
    if (trunkState == OFF) {
        trunkState = ON; // trunk popped
        digitalWrite(TRUNKPIN, HIGH); // Single press the trunk pop button
        delay(500);
        digitalWrite(TRUNKPIN, LOW);
    }
    else {
        trunkState = OFF; // trunk closed
    }
    return 200; // This is checked in the web app controller for validation
}

int lockFunction(String args) {
    if (lockState == OFF) {
        lockState = ON; // locks locked
        digitalWrite(LOCKPIN, HIGH); // Single press the lock button
        delay(500);
        digitalWrite(LOCKPIN, LOW);
    }
    return 200; // This is checked in the web app controller for validation
}

int unlockFunction(String args) {
    if (lockState == ON) {
        lockState = OFF; // locks unlocked
        digitalWrite(UNLOCKPIN, HIGH); // Single press the unlock button
        delay(500);
        digitalWrite(UNLOCKPIN, LOW);
    }
    return 200; // This is checked in the web app controller for validation
}

void setup() {
    pinMode(STARTPIN, OUTPUT);
    pinMode(TRUNKPIN, OUTPUT);
    pinMode(LOCKPIN, OUTPUT);
    pinMode(UNLOCKPIN, OUTPUT);

    digitalWrite(STARTPIN, LOW);
    digitalWrite(TRUNKPIN, LOW);
    digitalWrite(LOCKPIN, LOW);
    digitalWrite(UNLOCKPIN, LOW);

    Particle.function("start", startFunction);
    Particle.function("trunk", trunkFunction);
    Particle.function("lock", lockFunction);
    Particle.function("unlock", unlockFunction);

    Particle.variable("startstate", &startState, INT);
    Particle.variable("trunkstate", &trunkState, INT);
    Particle.variable("lockstate", &lockState, INT);
    Particle.variable("enginetemp", &engineTemp, INT);
}

void loop() {
    // Update every 10ms (default)
    if (millis() - lastTime > UPDATE_INTERVAL) {
        // Set a new last time
        lastTime = millis();

        engineTemp += 1;    // increase our ficticious temp
        engineTemp %= 2047; // if > 2047, set back to 0;

        if (startState == ON) {
            if (millis() - startTime > FIFTEEN_MINUTES) {
                startState = OFF;
            }
        }
    }
}
