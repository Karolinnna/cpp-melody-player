#include <fstream>
#include <windows.h>
#include <iostream>
#include "h/Soundplayer.h"
#include "h/Playlist.h"

using namespace std;

const string note_name[7] = {"C", "D", "E", "F", "G", "A", "B"};
const int    note_freq[7] = {65, 73, 82, 87, 98, 110, 123};



OCTAVE octaves[5] = {
    {"Great_octave", 1},
    {"Small_octave", 2},
    {"First_octave", 4},
    {"Second_octave", 8},
    {"Third_octave", 16}
};



const DURATION DURATIONS[5] = {
    {"1/1",  1},
    {"1/2",  2},
    {"1/4",  4},
    {"1/8",  8},
    {"1/16", 16}
};


NOTE::NOTE(string n, DURATION d, OCTAVE o) {
    name = n; duration = d; octave = o;
}
string NOTE::getName() const { return name; }
DURATION NOTE::getDuration() const { return duration; }
OCTAVE NOTE::getOctave() const { return octave; }



void MELODY::addNote(string name, DURATION duration, OCTAVE octave) {
    notes.push_back(NOTE(name, duration, octave));
}
NOTE MELODY::getNote(int i) { return notes[i]; }
int MELODY::getSize() { return notes.size(); }
void MELODY::clear() { notes.clear(); }



SOUNDPLAYER::SOUNDPLAYER(int bpm, string name) {
    tempo = 60000 / bpm;
    nazva = name;
}
void SOUNDPLAYER::addNote(string name, DURATION duration, OCTAVE octave) {
    melody.addNote(name, duration, octave);
}
MELODY& SOUNDPLAYER::getMelody() { return melody; }
string SOUNDPLAYER::getNazva() { return nazva; }

void SOUNDPLAYER::saveToFile(string file) {
    ofstream outf(file);
    if (!outf) return;
    outf << tempo << "\n" << melody.getSize() << "\n";
    for (int i = 0; i < melody.notes.size(); i++) {
        NOTE& n = melody.notes[i];
        outf << n.getName() << " " << n.getDuration().name << " " << n.getDuration().value << " " 
             << n.getOctave().name << " " << n.getOctave().mult << "\n";
    }
    outf.close();
}

void SOUNDPLAYER::loadFromFile(string file) {
    ifstream inf(file);
    if (!inf) return;
    int size;
    inf >> tempo >> size;
    melody.clear();
    for (int i = 0; i < size; i++) {
        string nN, dN, oN;
        int dV, oM;
        inf >> nN >> dN >> dV >> oN >> oM;
        melody.addNote(nN, {dN, dV}, {oN, oM});
    }
    inf.close();
}

TRACKEDITOR::TRACKEDITOR(int bpm, string name) : SOUNDPLAYER(bpm, name) {
}

TRACKEDITOR mergeTrack(TRACKEDITOR& a, TRACKEDITOR& b) {
    TRACKEDITOR result(60, a.getNazva() + "_" + b.getNazva()); // Створюємо новий об'єкт
    // Копіюємо ноти з першого треку
    for (int i = 0; i < a.getMelody().getSize(); i++) {
        NOTE n = a.getMelody().getNote(i);
        result.addNote(n.getName(), n.getDuration(), n.getOctave());
    }
    // Копіюємо ноти з другого треку
    for (int i = 0; i < b.getMelody().getSize(); i++) {
        NOTE n = b.getMelody().getNote(i);
        result.addNote(n.getName(), n.getDuration(), n.getOctave());
    }
    return result;
}

void TRACKEDITOR::play() {
    for(int i = 0; i < melody.notes.size(); i++) {
        NOTE& note = melody.notes[i];
        int freq = 0;
        for (int j = 0; j < 7; j++) {
            if (note.getName() == note_name[j]) {
                freq = note_freq[j] * note.getOctave().mult;
                break;
            }
        }
        int dur = tempo / note.getDuration().value;
        int sound_dur = dur * 0.9;
        int pause_dur = dur * 0.1;
        
        cout << note.getName() << "[" << note.getOctave().name[0] << "] ";
        if (freq > 0) Beep(freq, sound_dur);
        Sleep(pause_dur);
    }
    cout << endl;
}

void TRACKEDITOR::printStatus() {
    cout << "\nTrek: " << nazva << " BPM: " << 60000/tempo << endl;
    if (melody.getSize() > 0)
        cout << "Tonalnist: " << melody.getNote(0).getName() << ", Not: " << melody.getSize() << endl;
}

void TRACKEDITOR::shiftTone(int shiftchng) {
    MELODY nova;
    for (int i = 0; i < melody.getSize(); i++) {
        NOTE n = melody.getNote(i);
        int idx = -1;
        for (int j = 0; j < 7; j++)
            if (n.getName() == note_name[j]) { idx = j; break; }
        
        if (idx == -1) continue;

        int novi = idx + shiftchng;
        OCTAVE current_oct = n.getOctave();

        if (novi > 6) {
            novi = novi % 7;
            for (int k = 0; k < 4; k++)
                if (current_oct.name == octaves[k].name) {
                    current_oct = octaves[k+1]; break;
                }
        } else if (novi < 0) {
            novi = (novi + 7) % 7;
            for (int k = 1; k < 5; k++)
                if (current_oct.name == octaves[k].name) {
                    current_oct = octaves[k-1]; break;
                }
        }
        nova.addNote(note_name[novi], n.getDuration(), current_oct);
    }
    melody = nova;
}

void reverseTrack(TRACKEDITOR& player) {
    int n = player.melody.notes.size();
    for (int i = 0; i < n / 2; i++) {
        NOTE temp = player.melody.notes[i];
        player.melody.notes[i] = player.melody.notes[n - 1 - i];
        player.melody.notes[n - 1 - i] = temp;
    }
}

void fillRandom(TRACKEDITOR& player, int kilkist) {
    for (int i = 0; i < kilkist; i++)
        player.addNote(note_name[rand()%7], DURATIONS[rand()%5], octaves[rand()%5]);
}

void fillBabyShark(TRACKEDITOR& player) {
    string n[] = {
        "D", "E", "G", "G", "G", "G", "G", "G",
        "D", "E", "G", "G", "G", "G", "G", "G",
        "D", "E", "G", "G", "G", "G", "G", "G",
        "G", "G", "F", "D", "E", "G", "G", "G",
        "G", "G", "G", "D", "E", "G", "G", "G",
        "G", "G", "G", "D", "E", "G", "G", "G",
        "G", "G", "G", "G", "G", "F"
    };
    int d_idx[] = {
        2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3,


        2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3,
        3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3,
        3, 3, 3, 2, 2, 2
    };
    int o_idx[] = {
        2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
        2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
        2,2,2,2,2,2
    };
    int count = sizeof(n) / sizeof(n[0]);
    for (int i = 0; i < count; i++)
        player.addNote(n[i], (DURATION&)DURATIONS[d_idx[i]], (OCTAVE&)octaves[o_idx[i]]);
}

void PLAYLIST::addTrack(TRACKEDITOR t) {
    tracks.push_back(t);
}

void PLAYLIST::removeTrack(int index) {
    if (index >= 0 && index < tracks.size()) {
        tracks.erase(tracks.begin() + index);
    }
}

void PLAYLIST::showAll() {
    for (int i = 0; i < tracks.size(); i++) {
        cout << "[" << i << "] " << tracks[i].getNazva() 
             << " (" << tracks[i].getMelody().getSize() << " not)" << endl;
    }
}

TRACKEDITOR& PLAYLIST::getTrack(int index) {
    return tracks[index];
}

int PLAYLIST::getCount() {
    return tracks.size();
}
