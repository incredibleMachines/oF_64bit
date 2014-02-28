#include "testApp.h"

// High Performance OS X Video Playback Example
//--------------------------------------------------------------
// This example shows how to use the OS X platform specific
// ofQTKitPlayer on its own without the cross platform
// ofVideoPlayer wrapper.  Apps you write in this way won't be
// cross platform, but can be faster for HD videos .
//--------------------------------------------------------------

void testApp::setup(){
	ofBackground(255, 255, 255);
    
    filepaths[0]="LeftWall_UV_0.mov";
    filepaths[1]="LeftWall_UV_1.mov";
    filepaths[2]="LeftWall_UV_2.mov";
    filepaths[3]="LeftWall_UV_3.mov";
    filepaths[4]="LeftWall_UV_4.mov";
    
    play=0;
    load=0;
    vidCount = BUFFER_SIZE; //start at the length of loaded buff
    copied = false;
//    bFirst=true;
    
    drawTex.allocate(2000,720,GL_RGB);
    
    
	for(int i=0;i<BUFFER_SIZE;i++){
        contentBuffer[i].video.setPixelFormat(OF_PIXELS_RGB);
        contentBuffer[i].video.setLoopState(OF_LOOP_NORMAL);
        contentBuffer[i].loaded=false;
        contentBuffer[i].setup=false;
    }
}

//--------------------------------------------------------------
void testApp::update(){

    
    if(contentBuffer[play].video.isLoaded()==true){
        contentBuffer[play].video.update();
        drawTex.loadData(contentBuffer[play].video.getPixels(),2000,720,GL_RGB);
        if(contentBuffer[play].video.isFrameNew()){
//            cout<<contentBuffer[play].video.getCurrentFrame()<<endl;
        }
    }
    
    //if we're at the end of the current buffer video, switch to next in the buffer
    if(contentBuffer[play].video.getCurrentFrame()==contentBuffer[play].video.getTotalNumFrames() &&
       contentBuffer[play].video.getCurrentFrame()!=0){
        play++;
        if(play>BUFFER_SIZE-1){
            play=0;
        }
        
        load=play-1; //which buffer index will we fill next
        if(load<0){
            load=BUFFER_SIZE-1;
        }
        
        contentBuffer[play].video.setFrame(0);
//        bFirst=false;
        bLoaded=false;
        cout<<">>> now playing: "<< contentBuffer[play].video.getMoviePath()<<endl;
    }
    
    //if we're half way through current video, start thread to load up the next in the buffer queue
    if(contentBuffer[play].video.getCurrentFrame()>contentBuffer[play].video.getTotalNumFrames()/2 &&
       bLoaded==false){
        cout<<">>> running buffer thread #: "<< load;
        cout<<" >>> to load video #: "<< vidCount <<endl;
        contentBuffer[load].thread.filepath=filepaths[vidCount];
        contentBuffer[load].thread.bRun=true;
        vidCount++;
        if(vidCount >= NUM_VIDS) vidCount=0;
        bLoaded=true;
        copied=false;
    }
    
    //if thread is finished loading it's video
    if(contentBuffer[load].thread.bFinished==true){
        //if lock() and we have not copied into the buffer
        if(contentBuffer[load].thread.lock() && copied == false){
            contentBuffer[load].video=contentBuffer[load].thread.video;
            contentBuffer[load].thread.unlock();
            contentBuffer[load].video.setLoopState(OF_LOOP_NORMAL);
            contentBuffer[load].video.play();
            contentBuffer[load].thread.bFinished=false;
            copied = true;
            cout<<">>> loaded: "<<contentBuffer[load].video.getMoviePath();
            cout<<" into buffer #: "<<load<<endl;
          //  contentBuffer[load].thread.stop();
            
        }
        //            contentBuffer[load].thread.stop();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255,255,255);
    if(contentBuffer[play].loaded==true){
        drawTex.draw(0,0);
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='0'){
        for(int i=0;i<BUFFER_SIZE;i++){
            if(contentBuffer[i].setup==false){
                contentBuffer[i].thread.start();
                contentBuffer[i].video.loadMovie(filepaths[i]);
                contentBuffer[i].loaded=true;
                contentBuffer[i].video.play();
                contentBuffer[i].setup=true;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void testApp::exit(){
    for(int i=0;i<BUFFER_SIZE;i++){
        contentBuffer[i].thread.stop();
    }
}
