#pragma once

#include "ofMain.h"
#include "ofxPlotter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		
    ofxPlotter plotter;
    
};
