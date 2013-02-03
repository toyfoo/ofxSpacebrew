#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    string host = Spacebrew::SPACEBREW_CLOUD; // "localhost";
    string name = "of-button-example";
    string description = "It's amazing";
    
    spacebrew.addPublish("button", "boolean", "false");
    spacebrew.connect( host, name, description );
    
    // circle stuff
    bButtonPressed  = false;
    radius          = 200;
    
    // layout stuff
    ofBackground(0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableSmoothing();
    ofSetCircleResolution(30);
}

//--------------------------------------------------------------
void testApp::update(){}

//--------------------------------------------------------------
void testApp::draw(){
    string textToDraw = "PRESS ME";
    if ( bButtonPressed ){
        ofSetColor( 150, 0, 0 );
        textToDraw = "THANKS";
    } else {
        ofSetColor(150);
    }
    ofCircle(ofGetWidth() / 2.0f, ofGetHeight()/2.0f, radius);
    ofSetColor(255);
    ofDrawBitmapString(textToDraw, ofGetWidth() / 2.0f - 30, ofGetHeight()/2.0f);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if ( checkInsideCircle( ofPoint(x,y), ofPoint(ofGetWidth() / 2.0f, ofGetHeight()/2.0f), radius) ){
        bButtonPressed = true;
        spacebrew.send("button", true);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (bButtonPressed){
        spacebrew.send("button", false);
    }
    bButtonPressed = false;
}

//--------------------------------------------------------------
bool testApp::checkInsideCircle( ofPoint point, ofPoint position, int radius ){
    return ( point.x < position.x + radius
            && point.x > position.x - radius
            && point.y < position.y + radius
            && point.y > position.y - radius );
}