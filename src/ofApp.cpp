#include "ofApp.h"
#include "ofxTools.h"

ofImage img1, img2;

ofImage result;
cv::Mat flowMapX, flowMapY;
cv::Mat tflowMapX, tflowMapY;
cv::Mat one, two;

cv::Mat newFrame;
ofImage newImage;
cv::Mat flow;

#include "ofxFrameInterpolator.h"

ofxFrameInterpolator fi;
ofVideoPlayer player;

ofImage diff;

void ofApp::setup(){

    ofBackground(10);
    
//    player.load("/Users/whg/Code/of_v0.8.0_osx_release/examples/gl/multiTextureShaderExample/bin/data/fingers.mov");
//    
//    player.nextFrame();
    
    
    int d = 2;

    img1.load("/Users/whg/Library/Containers/com.apple.PhotoBooth/Data/Pictures/Photo Booth Library/Pictures/Photo on 23-07-2015 at 19.53.jpg");
//    img1.load("/Users/whg/Pictures/Photo Booth Library/Pictures/Photo on 03-02-2016 at 21.50 #3.jpg");
//    img1.loadImage("/Users/whg/Downloads/pigeon_exploding/frames/pigeon_explode clip 0054.png");
    img1.resize(img1.getWidth()/d, img1.getHeight()/d);
    img1.setImageType(OF_IMAGE_GRAYSCALE);
    
    img2.load("/Users/whg/Library/Containers/com.apple.PhotoBooth/Data/Pictures/Photo Booth Library/Pictures/Photo on 23-07-2015 at 19.53 #2.jpg");
//    img2.load("/Users/whg/Pictures/Photo Booth Library/Pictures/Photo on 03-02-2016 at 21.50 #2.jpg");

//    img2.loadImage("/Users/whg/Downloads/pigeon_exploding/frames/pigeon_explode clip 0055.png");
    img2.resize(img2.getWidth()/d, img2.getHeight()/d);
    img2.setImageType(OF_IMAGE_GRAYSCALE);

    result.allocate(one.cols, one.rows, OF_IMAGE_COLOR);


    fi = ofxFrameInterpolator(img1.getWidth(), img1.getHeight());
    
//    fi.calcMap(img1, img2);
//    ofPixels o = player.getPixels();
//    o.setImageType(OF_IMAGE_GRAYSCALE);
//    player.nextFrame();
//    ofPixels t = player.getPixels();
//    t.setImageType(OF_IMAGE_GRAYSCALE);
    
    
//    fi.calcMap(o, t);
    fi.calcMap(img1, img2);

    float start = ofGetElapsedTimef();


    newImage.allocate(img1.getWidth(), img1.getHeight(), OF_IMAGE_COLOR);
    
    diff.allocate(img1.getWidth(), img1.getHeight(), OF_IMAGE_GRAYSCALE);

    ofSetWindowShape(img1.getWidth()*2 + 30, img1.getHeight()*2+30);
    
    position = 0;
    steps = 0;
}



void ofApp::update(){

    int d = 20;
    float q = ofMap(mouseX, 0, ofGetWidth(), 0, 1);

//    cout << q << endl;

    fi.interploate(position,   newImage);
    
    position+= 0.01;
    
    if (position >= 0.1) {
        position = 0;
        steps++;
        fi.calcMap(newImage, img2);
    }
    
//    unsigned char *i1 = img2.getPixels().getData();
//    unsigned char *ni = newImage.getPixels().getData();
//    unsigned char *dp = diff.getPixels().getData();
//    for (int i = 0; i < img1.getWidth() * img1.getHeight(); i++) {
//        dp[i] = abs(i1[i] - ni[i]);
//    }
//    
//    diff.setFromPixels(dp, diff.getWidth(), diff.getHeight(), OF_IMAGE_GRAYSCALE);

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}



void ofApp::draw(){

    img1.draw(10, 10);
    img2.draw(img1.getWidth()+20, 10);
    
//    diff.draw(10, 20+img1.getHeight());

    ofDrawBitmapString(ofToString(position), 10, 20+img1.getHeight());
    ofDrawBitmapString(ofToString(steps), 10, 30+img1.getHeight());
    
//    if (ofGetKeyPressed()) {
//        img2.draw(img1.getWidth()+20, img1.getHeight()+20);
//    }
//    else {
        newImage.draw(img1.getWidth()+20, img1.getHeight()+20);
//    }
    
    
}


void ofApp::keyPressed(int key){

    
    //    fi.calcMap(img1, img2);
//    ofPixels o = player.getPixels();
//    o.setImageType(OF_IMAGE_GRAYSCALE);
//    player.nextFrame();
//    ofPixels t = player.getPixels();
//    t.setImageType(OF_IMAGE_GRAYSCALE);
    
//    fi = ofxFrameInterpolator(img1.getWidth(), img1.getHeight());

    
    //    fi.calcMap(o, t);
    
    KEY('n', fi.calcMap(newImage, img2));
    KEY('r', fi.calcMap(img1, img2));


}


void ofApp::keyReleased(int key){

}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
