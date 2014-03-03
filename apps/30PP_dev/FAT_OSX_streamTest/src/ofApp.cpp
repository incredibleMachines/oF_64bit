#include "ofApp.h"

// High Performance OS X Video Playback Example
//--------------------------------------------------------------
// This example shows how to use the OS X platform specific
// ofQTKitPlayer on its own without the cross platform
// ofVideoPlayer wrapper.  Apps you write in this way won't be
// cross platform, but can be faster for HD videos .
//--------------------------------------------------------------

void ofApp::setup(){
	ofBackground(255, 255, 255);
    ofSetFrameRate(30);
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    
    filepaths[0]="output.mov";
    filepaths[1]="two.mov";
    filepaths[2]="three.mov";
    
    play=0;
    load=1;
    bFirst=true;
    count=BUFFER_SIZE-1;
    bContentLoaded=false;
    contentTriggered=false;
    bInit=false;
    
    queue[0].loaded=false;
    queue[1].loaded=false;
    
    drawTex.allocate(1920,1080,GL_RGB);
    loopCount=0;
    bLoaded=false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    queue[0].video.update();
    
    if(queue[0].video.getLoadedState()==true){ //.isAsyncLoaded() !!
        queue[0].loaded=true;
        if(queue[0].video.isFrameNew()){
            drawTex.loadData(queue[0].video.getPixels(),1920,1080,GL_RGB);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    
    if(queue[0].loaded==true){
        drawTex.draw(0,0);
    }
    
    ofSetColor(0,0,0);
    ofDrawBitmapString("number loads: "+ofToString(loopCount)+"  seconds :"+ofToString(ofGetElapsedTimeMillis()/1000),200,800);
    ofDrawBitmapString("Frame rate: "+ofToString(ofGetFrameRate()),200,820);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='0'){
        string initArray[3];
        int arrayCount=0;
        for(int i=0;i<3;i++){
            cout<<i<<endl;
            initArray[arrayCount]=filepaths[i];
            arrayCount++;
        }
        queue[0].video.initPlayer(initArray);
        queue[0].loaded=false;
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

