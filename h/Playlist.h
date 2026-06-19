#pragma once
#include <string>
#include <vector>
#include "Soundplayer.h"

using namespace std;

class PLAYLIST {
private:
    vector<TRACKEDITOR> tracks; 
public:
    void addTrack(TRACKEDITOR t);
    void removeTrack(int index);
    void showAll();
    TRACKEDITOR& getTrack(int index);
    int getCount();
};