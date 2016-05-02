#include "ofApp.h"

ofNode base;
ofNode secondNode;
ofNode thirdNode;
ofPolyline line;
ofEasyCam cam;
ofSerial serial;

float a;
float maxX = 0.5;
float maxY = 0.5;
float soundSpeed = 0.1;
float interval;
int dist1 = 50;
int dist2 = 50;
int caseState;
unsigned long pTime;


//--------------------------------------------------------------
void ofApp::setup(){
    
    //serial.listDevices();
    //vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // int baud = 57600;
    //serial.setup(0, 57600); //open the first device and talk to it at 57600 baud
    
    sound.loadSound("city.wav");
    sound.play();
    ofSetLineWidth(3);
    ofEnableDepthTest();
    ofSetBackgroundColor(255);
    base.setPosition(10, 0, 10);
    secondNode.setParent(base);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    switch(caseState){
        case 0: //starting stage
            interval = 50;
            sound.setVolume(soundSpeed);
            //ref: http://openframeworks.cc/ofBook/chapters/lines.html
            
            secondNode.setPosition(0, 0,dist1);
            thirdNode.setParent(secondNode);
            thirdNode.setPosition(dist2,0,0);
            
            base.pan(1);
            secondNode.tilt(1);
            
            line.addVertex(thirdNode.getGlobalPosition());
            if (line.size() > 50){
                line.getVertices().erase(line.getVertices().begin());
            }
            
            for (auto &vert : line.getVertices()){
                vert.x += ofRandom(-0.5,0.5);
                vert.y += ofRandom(-0.5,0.5);
            }
            
            if(ofGetElapsedTimeMillis()-pTime >= interval){ //debouncing
                dist1++;
                dist2++;
                pTime = ofGetElapsedTimeMillis();
            }
            
            
            if(dist1 > 300){
                caseState++; //swtich to case 1
            }
            
            break;
            
        case 1:
            interval = 900; //longer duration
            secondNode.setPosition(0, 0,ofRandom(10,50));
            thirdNode.setParent(secondNode);
            thirdNode.setPosition(0,0,ofRandom(50,200));
            
            base.pan(1);
            secondNode.tilt(ofRandom(2,10));
            
            line.addVertex(thirdNode.getGlobalPosition());
            if (line.size() > 200){
                line.getVertices().erase(line.getVertices().begin());
            }
            
            for (auto &vert : line.getVertices()){
                vert.x += ofRandom(-0.5,maxX);
                vert.y += ofRandom(-0.5,maxY);
            }
            
            //fading alpha value back and forth from 20 to 255 (duration = 0.9 second)
            a = 143 + 127 * cos (0.25 * PI / interval * (interval - ofGetElapsedTimeMillis()));
            
            sound.setVolume(soundSpeed);
            
            break;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    if(caseState == 1){
        ofSetColor(0,0,255); //set color to blue
        ofFill(); //fill blue
        float timeTracker = ofGetElapsedTimeMillis()/ 1000;
        ofDrawBitmapString(timeTracker -14, 400, -300);
        ofDrawBitmapString("seconds", 400, -320);
        ofSetColor(0); //set color to black
        ofFill(); //fill black
        //draw eyes
        ofDrawCircle(mouseX-600, mouseY-200, ofRandom(10,200));
        ofDrawCircle(mouseX-300, mouseY-200, ofRandom(10,200));
        ofSetBackgroundColor(255);
        ofSetColor(0,a); //set color to black and set the alpha value for the random line
        maxX+= 0.01;
        maxY+= 0.01;
        soundSpeed += 0.1;
    }else{
        ofDrawBitmapString("How Long Can You Stare At The Screen?", -150, 200);
        ofSetBackgroundColor(0);
        ofSetColor(255);
        
    }
    
    line.draw();
    cam.end();
    
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
