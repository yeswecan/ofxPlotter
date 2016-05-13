#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    plotter.setWindowSize(2000);
    
    plotter.addGuideline("sin1", 0.75);
}

//--------------------------------------------------------------
void ofApp::update(){
    plotter["sin1"] << sin(ofGetElapsedTimef() * 1);
    plotter["sin2"] << sin(ofGetElapsedTimef() * 4);
    plotter["sin3"] << sin(ofGetElapsedTimef() * 8);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(20), ofColor(75));
    
    plotter.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    
}

