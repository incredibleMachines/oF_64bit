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
    
    filepaths[0]="LeftWall_UV_2.mov";
    filepaths[1]="two.mov";
    filepaths[2]="LeftWall_UV_2.mov";
    filepaths[3]="four.mov";
    filepaths[4]="five.mov";
//    filepaths[4]="LeftWall_UV_6.mov";
    
    play=0;
    load=0;
    bFirst=true;
    count=BUFFER_SIZE-1;
    bContentLoaded=false;
    contentTriggered=false;
    bInit=false;
    
    queue.loaded=false;
    
    drawTex.allocate(1920,1080,GL_RGB);
    loopCount=0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    queue.video.update();
    if(queue.video.getLoadedState()==true){ //.isAsyncLoaded() !!
        if(queue.video.isFrameNew()){
            drawTex.loadData(queue.video.getPixels(),1920,1080,GL_RGB);
            if(queue.loaded==false){
                cout<<"set play"<<endl;
                queue.video.play();
                queue.loaded=true;
            }
        }
    }

    

    if(queue.video.getCurrentFrame()>=queue.video.getTotalNumFrames()-1&&queue.video.getCurrentFrame()>0){
        
        queue.video.nextVideo();
        queue.loaded=false;
        cout<<"playing slot:"<<play<<endl;
        bFirst=false;
        bLoaded=false;
    }
    
    if(bFirst==false){
        if(queue.video.getCurrentFrame()>queue.video.getTotalNumFrames()/2&&bLoaded==false){

            count++;
            if (count>NUM_VIDS-1){
                count=0;
            }
            bLoaded=true;
            
            queue.video.addVideo(filepaths[count]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    if(queue.video.getLoadedState()==true){
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
        for(int i=0;i<BUFFER_SIZE;i++){
            initArray[i]=filepaths[i];
        }
        cout<<"testApp init";
        queue.video.initPlayer(initArray);
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

