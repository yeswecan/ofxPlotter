#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    plotter.setWindowSize(2000);
}

//--------------------------------------------------------------
void ofApp::update(){
    plotter["sin1"] << sin(ofGetElapsedTimef() * 1);
    plotter["sin2"] << sin(ofGetElapsedTimef() * 4);
    plotter["sin3"] << sin(ofGetElapsedTimef() * 8);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    plotter.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    
}

