#pragma once

#include "ofMain.h"
#include "ofAVQueuePlayer.h"

#define NUM_VIDS 6
#define BUFFER_SIZE 3

class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    class videoLoader{
        public:
            ofAVQueuePlayer video;
            bool loaded;
            bool playing;
    };
    
    videoLoader queue[3];
    
    string filepaths[NUM_VIDS];
    
    int play, load, count;
    
    bool bFirst,bLoaded, bInit;
    ofTexture drawTex;
    
    float timer;
    
    bool bContentLoaded, contentTriggered;
    
    int loopCount;
    
};

