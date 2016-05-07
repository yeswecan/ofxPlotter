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
        ofAddListener(ofEvents().update, this, &::ofxPlotter::update);
    }
    
    void updateHistory() {
        for (std::map<std::string, ofxPlotter::Value>::iterator i = values.begin(); i != values.end(); i++) {
            history[i->first].push_back(i->second);
            if (history[i->first].size() > windowSize) {
                history[i->first].erase(history[i->first].begin());
            }
            if (accents[i->first].size() > windowSize) {
                accents[i->first].erase(accents[i->first].begin());
            }
            accents[i->first].push_back(0);
        }
    }
    
    void addAccent(std::string index) {
        accents[index][accents[index].size() - 1] = 5;
    }
    
    void update(ofEventArgs & args) {
        updateHistory();
    }
    
    Value& operator[](std::string righthand) {
        return (Value&)values[righthand];
        
    }
    
    
    void drawOverlay(float x, float y, float width, float height) {
        int graphCount = values.size();
        if (!ofRectangle(x, y, width, height).inside(ofGetMouseX(), ofGetMouseY())) return;
        float mx = (ofGetMouseX() - x) / width;
        float my = (ofGetMouseY() - y) / height;
        int yspace = (float)height / graphCount;
        
        int index = (my / (1 / (float)graphCount));
        
        ofSetColor(255);
        
        int counter = 0;
        for (std::map<std::string, ofxPlotter::Value>::iterator i = values.begin(); i != values.end(); i++) {
            if (index == counter) {
                float position = (mx * history[i->first].size());
                ofDrawBitmapStringHighlight(ofToString(history[i->first][position].getF()), x + mx * width, y + my * height);
            }
            counter++;
        }
    }
    
    void draw(float x, float y, float width, float height, int verticalLines = 16) {
        int graphCount = values.size();
        int yspace = (float)height / graphCount;
        int index = 0;
        float colorspaceWidth = 255. / (float)graphCount;
        for (std::map<std::string, ofxPlotter::Value>::iterator i = values.begin(); i != values.end(); i++) {
            std::vector<ofxPlotter::Value>* historyValues = &history[i->first];
            
            // Measuring the function scale
            float sum = 0;
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
                ofTranslate(x, y + yspace * index);
                
                ofPoint p, p2;
                for (int j = 0; j < (*historyValues).size(); j++) {
                    
                    float mappedPoint = 1 - ofMap((*historyValues)[j].getF(), min, max, 0, 1);
                    
                    p = ofPoint(j * stepWidth,
                                mappedPoint * yspace);
                    ofSetLineWidth(2);
                    ofSetColor(ofColor::fromHsb((index * colorspaceWidth), 255, 200, 255));
                    if (j != 0) ofLine(p2, p);
                    p2 = p;
                    
                }
            
                int lastx = -200;
                for (int j = 0; j < (*historyValues).size(); j++) {
                    if (accents[i->first][j] != 0) {
                        ofSetColor(255);
                        ofSetLineWidth(2);
                        ofLine(j * stepWidth, index * yspace,
                               j * stepWidth, (index - 1) * yspace);
                        ofCircle(j * stepWidth, index * yspace, 3);
                        float mid = 0;
                        if (j > 5) {
                            for (int k = j - 5; k < j + 5; k++) {
                                mid += (*historyValues)[k].getF();
                            }
                            mid /= 10;
                        }
                        if ((j * stepWidth - lastx) > 200) {
                            ofDrawBitmapStringHighlight(ofToString(mid), j * stepWidth, index * yspace - 15);
                            lastx = j * stepWidth;
                        }
                    }
                }
            
                ofSetColor(255, 50);
                ofDrawBitmapStringHighlight(i->first + " ; current: " + ofToString(values[i->first].getFiltered(0.5), 4) + " ; min: " + ofToString(min, 4) + " ; max: " + ofToString(max, 4), 25, 25);
            ofPopMatrix();
            
            index++;
        }
        
        if (drawMouseOverlay) drawOverlay(x, y, width, height);
    }
    
    std::map<std::string, ofxPlotter::Value> values;
    std::map<std::string, std::vector<ofxPlotter::Value>> history;
    std::map<std::string, std::vector<int>> accents;
    
    
    // Parameters
    
    void setWindowSize(int size) {
        windowSize = size;
    }
    
    int getWindowSize() {
        return windowSize;
    }
    
    bool drawMouseOverlay = true;
};

#endif /* ofxPlotter_h */
