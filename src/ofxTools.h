// some OF tools by whg

#pragma once

#include "ofMain.h"

#define KEY(k, f) if(key == k) { f; }

#ifndef GLSL120
    #define GLSL120(shader)  "#version 120 \n #extension GL_ARB_texture_rectangle : enable \n" #shader
#endif

inline ofVec2f ofMap(ofVec2f p, ofRectangle fromRect, ofRectangle toRect){
    
    float x = ofMap(p.x, fromRect.position.x, fromRect.width, toRect.position.x, toRect.width);
    float y = ofMap(p.y, fromRect.position.y, fromRect.height, toRect.position.x, toRect.height);
    return ofVec2f(x, y);
}

inline ofVec3f ofMap(ofVec3f p, ofRectangle fromRect, ofRectangle toRect){
    ofVec2f v2 = ofMap(ofVec2f(p.x, p.y), fromRect, toRect);
    return ofVec3f(v2.x, v2.y, 0);
}

inline ofRectangle ofMap(ofRectangle r, ofRectangle fromRect, ofRectangle toRect){
    
    float x = ofMap(r.position.x, fromRect.position.x, fromRect.width, toRect.position.x, toRect.width);
    float y = ofMap(r.position.y, fromRect.position.y, fromRect.height, toRect.position.x, toRect.height);
    float w = ofMap(r.width, fromRect.position.x, fromRect.width, toRect.position.x, toRect.width);
    float h = ofMap(r.height, fromRect.position.y, fromRect.height, toRect.position.x, toRect.height);
    
    return ofRectangle(x, y, w, h);
}

inline ofRectangle vec4f2Rectangle(const ofVec4f &v) {
    return ofRectangle(v.x, v.y, v.z, v.w);
}

inline ofVec4f rectangle2Vec4f(const ofRectangle &r) {
    return ofVec4f(r.position.x, r.position.y, r.width, r.height);
}