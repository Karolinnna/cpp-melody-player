#pragma once
#include <string>
#include <vector>


using namespace std;

struct OCTAVE {
    string name;
    int    mult;
};

struct DURATION {
    string name;
    int    value;
};

class NOTE {
protected:
    string name;
    DURATION duration;
    OCTAVE octave;
public:
    NOTE(string n, DURATION d, OCTAVE o);
    string getName() const;
    DURATION getDuration() const;
    OCTAVE getOctave() const;
};

class MELODY {
private:
    vector<NOTE> notes;
public:
    friend class SOUNDPLAYER;
    friend class TRACKEDITOR;
    friend void reverseTrack(class TRACKEDITOR& player);

    void addNote(string name, DURATION duration, OCTAVE octave);
    NOTE getNote(int i);
    int  getSize();
    void clear();
};

