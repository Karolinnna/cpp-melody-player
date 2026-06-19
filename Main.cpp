#include <iostream>
#include <string>
#include <vector>
#include "h/Soundplayer.h"
#include "h/Playlist.h"

using namespace std;

int main() {
    PLAYLIST myPlaylist;
    string filename = "baby_shark.txt";

    TRACKEDITOR shark(60, "Baby_Shark");
    fillBabyShark(shark);
    shark.saveToFile(filename);

    TRACKEDITOR loader(120, "Loaded_Shark");
    loader.loadFromFile(filename);

    TRACKEDITOR rnd(90, "Vypadkovyy");
    fillRandom(rnd, 16);

    myPlaylist.addTrack(loader);
    myPlaylist.addTrack(rnd);

    int vybir = -1;
    while (vybir != 0) {
        cout << "\n1-show 2-listen 3-status 4-tonalnist 5-revers 6-zlyyty 7-vydalyty 0-vyhid: ";
        cin >> vybir;

        int idx, a, b, zsuv;

        if (vybir == 1) {
            myPlaylist.showAll();
        } 
        else if (vybir == 2) {
            myPlaylist.showAll();
            cout << "Number: "; cin >> idx;
            if (idx >= 0 && idx < myPlaylist.getCount()) {
                myPlaylist.getTrack(idx).play();
            }
        } 
        else if (vybir == 3) {
            myPlaylist.showAll();
            cout << "Number: "; cin >> idx;
            if (idx >= 0 && idx < myPlaylist.getCount()) {
                myPlaylist.getTrack(idx).printStatus();
            }
        } 
        else if (vybir == 4) {
            myPlaylist.showAll();
            cout << "Number: "; cin >> idx;
            cout << "Zsuv (-6..+6): "; cin >> zsuv;
            if (idx >= 0 && idx < myPlaylist.getCount()) {
                myPlaylist.getTrack(idx).shiftTone(zsuv);
                myPlaylist.getTrack(idx).play();
            }
        } 
        else if (vybir == 5) {
            myPlaylist.showAll();
            cout << "Number: "; cin >> idx;
            if (idx >= 0 && idx < myPlaylist.getCount()) {
                reverseTrack(myPlaylist.getTrack(idx));
                myPlaylist.getTrack(idx).play();
            }
        } 
        else if (vybir == 6) {
            myPlaylist.showAll();
            cout << "First: "; cin >> a;
            cout << "Second: "; cin >> b;
            if (a >= 0 && a < myPlaylist.getCount() && b >= 0 && b 
            < myPlaylist.getCount()) {
                TRACKEDITOR merged = mergeTrack(myPlaylist.getTrack(a), 
                myPlaylist.getTrack(b));
                myPlaylist.addTrack(merged);
            }
        } 
        else if (vybir == 7) {
            myPlaylist.showAll();
            cout << "Number: "; cin >> idx;
            myPlaylist.removeTrack(idx);
        }
    }

    return 0;
}