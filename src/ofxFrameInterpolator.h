//
//  ofxFrameInterpolator.h
//  Created by Will Gallia on 10/08/2015.

#pragma once

#include "ofMain.h"
#include "opencv.hpp"




class ofxFrameInterpolator {

public:
    struct FlowMap {
        cv::Mat x[3], y[3];
    };
    
    cv::Mat frames[2], newFrame;
    vector<cv::Mat> channels[2], newChannels;
    int nchannels;

    cv::Mat flow;
    FlowMap flowMap;
    
    cv::Mat interFlowX, interFlowY;
    
    ofVec2f size;
    
public:
    ofxFrameInterpolator() {}
    ofxFrameInterpolator(int width, int height);
    
    
    FlowMap& calcMap(ofPixels &one, ofPixels &two);
    FlowMap& calcMap(ofImage &one, ofImage &two);
    
    void interploate(float q, ofImage &outputImage);
};