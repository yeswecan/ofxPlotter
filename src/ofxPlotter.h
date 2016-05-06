//
//  ofxPlotter.h
//  Plotter example
//
//  Created by zebra on 06/05/16.
//
//

#ifndef ofxPlotter_h
#define ofxPlotter_h

#include <map>
#include <string>
#include <vector>

#include "ofMain.h"

class ofxPlotter {
    
    class Value {
    public:
        float inner_value;
        float inner_value_filtered;
        
        Value() { }
        
        // Float righthand
        void operator<<(float righthand) {
            inner_value = righthand;
        }

        // Int righthand
        void operator<<(int righthand) {
            inner_value = righthand;
        }
        
        
        int getI() {
            return inner_value;
        }

        float getF() {
            return (float)inner_value;
        }
        
        float getFiltered(float filter_amount = 0.2) {
            inner_value_filtered = inner_value_filtered * filter_amount + inner_value * filter_amount;
            return inner_value_filtered;
        }
        
    };

    
    static int windowSize;
    static float windowLength;
    
public:
    ofxPlotter() {
        windowSize = 300;
    }
    
    void updateHistory() {
        for (std::map<std::string, ofxPlotter::Value>::iterator i = values.begin(); i != values.end(); i++) {
            history[i->first].push_back(i->second);
            if (history[i->first].size() > windowSize) {
                history[i->first].erase(history[i->first].begin());
            }
//            ofLog() << i->first << " : " << i->second.getF();
        }
    }
    
    Value& operator[](std::string righthand) {
        updateHistory();
        return (Value&)values[righthand];
        
    }
    
    void draw(float x, float y, float width, float height, int verticalLines = 16) {
        int graphCounts = values.size();
        int yspace = (float)height / graphCounts;
        int index = 0;
        for (std::map<std::string, ofxPlotter::Value>::iterator i = values.begin(); i != values.end(); i++) {
            std::vector<ofxPlotter::Value>* historyValues = &history[i->first];
            
            // Measuring the function scale
            float sum;
            float max = -999999999;
            float min = 999999999;
            for (int i = 0; i < historyValues->size(); i++) {
                float value = (*historyValues).operator[](i).getF();
                sum += value;
                if (value > max) max = value;
                if (value < min) min = value;
            }
            float median = sum / historyValues->size();
            
            float multiplier = 1 / (max - min);
            
            float stepWidth = width / historyValues->size();
            ofPushMatrix();
            ofTranslate(0, yspace * index);
            ofSetColor(ofColor::fromHsb((index * 75), 255, 50, 20));
            ofDrawRectangle(0, 0, width, yspace);
            
            ofSetColor(ofColor::fromHsb((index * 75), 255, 50, 25));
            ofSetLineWidth(2);
            if (verticalLines > 0 ) {
                float verticalLineW = width / verticalLines;
                for (int j = 0; j < verticalLines; j++) {
                    ofLine(j * verticalLineW, 0, j * verticalLineW, height);
                }
            }
            
            
            ofSetColor(ofColor::fromHsb((index * 75), 255, 200, 255));
            ofPoint p, p2;
            for (int i = 0; i < (*historyValues).size(); i++) {
                p = ofPoint(i * stepWidth, yspace / 2 + (*historyValues)[i].getF() * yspace * multiplier);
                ofSetLineWidth(3);
                ofLine(p2, p);
                p2 = p;
            }
            ofDrawBitmapStringHighlight(i->first + " ; current: " + ofToString(values[i->first].getFiltered(0.5)) + " ; min: " + ofToString(min) + " ; max: " + ofToString(max), 25, 25);
            ofPopMatrix();
            
            index++;
        }
    }
    
    std::map<std::string, ofxPlotter::Value> values;
    std::map<std::string, std::vector<ofxPlotter::Value>> history;
    
    
    // Parameters
    
    void setWindowSize(int size) {
        windowSize = size;
    }
    
    int getWindowSize() {
        return windowSize;
    }
};

#endif /* ofxPlotter_h */
