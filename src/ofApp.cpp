#include "ofApp.h"

#include "ofxOpenCv.h"
#include "opencv.hpp"

ofImage img1, img2;

ofImage result;
cv::Mat flowMapX, flowMapY;
cv::Mat tflowMapX, tflowMapY;
cv::Mat one, two;

cv::Mat newFrame;
ofImage newImage;

void ofApp::setup(){

    ofBackground(10);

    img1.load("FOOTBALL_UNGRADED_WALL 01.png");
    img1.resize(img1.width/4, img1.height/4);
    img1.setImageType(OF_IMAGE_GRAYSCALE);
    ofxCvGrayscaleImage cvimg1;
    cvimg1.setFromPixels(img1.getPixels());
    
//    IplImage *iplimg1 = cvimg1.getCvImage();
    one = cv::Mat(cvimg1.getCvImage());
    
    img2.load("FOOTBALL_UNGRADED_WALL 02.png");
    img2.resize(img2.width/4, img2.height/4);
    img2.setImageType(OF_IMAGE_GRAYSCALE);
    ofxCvGrayscaleImage cvimg2;
    cvimg2.setFromPixels(img2.getPixels());
    
    two = cv::Mat(cvimg2.getCvImage());
//    IplImage *iplimg2 = cvimg2.getCvImage();
    

//    CvMat *flow = cvCreateMat(img1.height, img1.width, CV_32FC2);
    cv::Mat flow;
//    cv::OutputArray

//    cv::Mat one = cv::imread(ofToDataPath("FOOTBALL_UNGRADED_WALL 01.png", true));
//    cv::Mat two = cv::imread(ofToDataPath("FOOTBALL_UNGRADED_WALL 02.png", true));
//    cv::Mat out;

    cv::calcOpticalFlowFarneback(one, two, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

    cout << flow.type() << endl;
    cout << CV_32FC2 << endl;
    
    result.allocate(flow.cols, flow.rows, OF_IMAGE_COLOR);
    
    ofVec2f min(1000), max(-1000);
    
    for (int i = 0; i < flow.cols; i++) {
        for (int j = 0; j < flow.rows; j++) {
            
            const cv::Point2f& p = flow.at<cv::Point2f>(j, i);
            min.x = MIN(p.x, min.x);
            min.y = MIN(p.y, min.y);
            max.x = MAX(p.x, max.x);
            max.y = MAX(p.y, max.y);
        }
    }
    cout << min << endl;
    cout << max << endl;

    flowMapX = cv::Mat(flow.size(), CV_32F);
    flowMapY = cv::Mat(flow.size(), CV_32F);
    
    for (int i = 0; i < flow.cols; i++) {
        for (int j = 0; j < flow.rows; j++) {
            
            const cv::Point2f& p = flow.at<cv::Point2f>(j, i);
            
            ofColor col(ofMap(p.x, min.x, max.x, 0, 255), ofMap(p.y, min.y, max.y, 0, 255), 255);
            result.setColor(i, j, col);
            
            flowMapX.at<float>(j, i) = p.x;
            flowMapY.at<float>(j, i) = p.y;
            
//            result.setColor(i, j, ofColor(p.x*, p.y, 0));
            
//            cout << p.x << ", " << p.y << endl;
//            cout << col << endl;
        }
    }
    
    result.update();
    
    tflowMapX = flowMapX.clone();
    tflowMapY = flowMapY.clone();

    newImage.allocate(img1.width, img1.height, OF_IMAGE_GRAYSCALE);
  
    newFrame = two.clone();
//
//    result.setFromPixels(flow., <#int w#>, <#int h#>, OF_PIXELS_GRAY)
//    result.setFromPixels(flow.data, flow.cols, flow.rows, OF_IMAGE_);

    ofSetWindowShape(img1.width*2 + 30, img1.height*2+30);
}


void ofApp::update(){

    float q = ofMap(mouseX, 0, ofGetWidth(), 0, 1, true);
    
//    for (int i = 0; flowMapY.rows * flowMapY.cols; i++) {
//        tflowMapX
//    }

    cout << q << endl;

    for (int i = 0; i < flowMapX.cols; i++) {
        for (int j = 0; j < flowMapX.rows; j++) {
            tflowMapX.at<float>(j, i) = i + flowMapX.at<float>(j, i) * q;
            tflowMapY.at<float>(j, i) = j + flowMapY.at<float>(j, i) * q;
        }
    }
    
//    tflowMapX = flowMapX * q;
//    tflowMapY = flowMapY * q;
}


void ofApp::draw(){

    img1.draw(10, 10);
    img2.draw(img1.width+20, 10);
    
    result.draw(10, 20+img1.height);
    
    newFrame = cv::Mat::zeros(one.size(), CV_32F);
    cv::remap(two, newFrame, tflowMapX, tflowMapY, CV_INTER_LINEAR);
    
    newImage.setFromPixels(newFrame.data, newImage.width, newImage.height, OF_IMAGE_GRAYSCALE);
    
    newImage.draw(img1.width+20, img1.height+20);
    
}


void ofApp::keyPressed(int key){

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
