#pragma once
#include <string>
#include <vector>
#include "Melody.h"

using namespace std;

class SOUNDPLAYER {
protected:
    MELODY melody;
    int tempo;
    string nazva;
public:
    SOUNDPLAYER(int bpm, string name);
    void addNote(string name, DURATION duration, OCTAVE octave);
    void saveToFile(string file);
    void loadFromFile(string file);
    MELODY& getMelody();
    string getNazva();
    void setNazva(string name) { nazva = name; }
};

class TRACKEDITOR : public SOUNDPLAYER {
public:
    TRACKEDITOR(int bpm, string name); 

    void play();
    void shiftTone(int shiftchng);
    void printStatus();

    friend void reverseTrack(TRACKEDITOR& player);
};

void fillBabyShark(TRACKEDITOR& player);
void fillRandom(TRACKEDITOR& player, int kilkist);
void reverseTrack(TRACKEDITOR& player);
TRACKEDITOR mergeTrack(TRACKEDITOR& t1, TRACKEDITOR& t2);