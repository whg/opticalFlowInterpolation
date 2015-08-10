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


void ofApp::setup(){

    ofBackground(10);
    
    int d = 2;

    img1.load("/Users/whg/Library/Containers/com.apple.PhotoBooth/Data/Pictures/Photo Booth Library/Pictures/Photo on 23-07-2015 at 19.53.jpg");
    img1.resize(img1.width/d, img1.height/d);
    img1.setImageType(OF_IMAGE_GRAYSCALE);
    ofxCvGrayscaleImage cvimg1;
    cvimg1.setFromPixels(img1.getPixels());
    
//    IplImage *iplimg1 = cvimg1.getCvImage();
    one = cv::Mat(cvimg1.getCvImage(), true);
    
    img2.load("/Users/whg/Library/Containers/com.apple.PhotoBooth/Data/Pictures/Photo Booth Library/Pictures/Photo on 23-07-2015 at 19.53 #2.jpg");
    img2.resize(img2.width/d, img2.height/d);
    img2.setImageType(OF_IMAGE_GRAYSCALE);
    ofxCvGrayscaleImage cvimg2;
    cvimg2.setFromPixels(img2.getPixels());
    
    two = cv::Mat(cvimg2.getCvImage(), true);
//    IplImage *iplimg2 = cvimg2.getCvImage();
    

//    CvMat *flow = cvCreateMat(img1.height, img1.width, CV_32FC2);
//    cv::OutputArray

//    cv::Mat one = cv::imread(ofToDataPath("FOOTBALL_UNGRADED_WALL 01.png", true));
//    cv::Mat two = cv::imread(ofToDataPath("FOOTBALL_UNGRADED_WALL 02.png", true));
//    cv::Mat out;

    result.allocate(one.cols, one.rows, OF_IMAGE_COLOR);


    

//    flowMapX = one.clone(); //cv::Mat::zeros(flow.cols, flow.rows, CV_32F); // cv::Mat(flow.size(), CV_32F);
//    flowMapY = one.clone(); //cv::Mat::zeros(flow.cols, flow.rows, CV_32F); //(flow.size(), CV_32F);
    flowMapX.create(one.rows, one.cols, CV_32F);
    flowMapY.create(one.rows, one.cols, CV_32F);
    tflowMapX.create(one.rows, one.cols, CV_32F);
    tflowMapY.create(one.rows, one.cols, CV_32F);
    
//    tflowMapX = one.clone();// flowMapX.clone();
//    tflowMapY = one.clone();//flowMapY.clone();

    getMap(one, two);
    
    

    newImage.allocate(img1.width, img1.height, OF_IMAGE_GRAYSCALE);
  
//    newFrame = two.clone();
//    newFrame = cv::Mat::zeros(one.size(), CV_32F);

//
//    result.setFromPixels(flow., <#int w#>, <#int h#>, OF_PIXELS_GRAY)
//    result.setFromPixels(flow.data, flow.cols, flow.rows, OF_IMAGE_);

    ofSetWindowShape(img1.width*2 + 30, img1.height*2+30);
    
    position = 0;
}

void ofApp::getMap(cv::Mat &one, cv::Mat &two) {
    cv::calcOpticalFlowFarneback(one, two, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

//    cout << flow.type() << endl;
//    cout << CV_32FC2 << endl;


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
    
    int q = 1;
    
    for (int i = 0; i < flowMapX.cols; i++) {
        for (int j = 0; j < flowMapX.rows; j++) {
            tflowMapX.at<float>(j, i) = i + flowMapX.at<float>(j, i) * q;
            tflowMapY.at<float>(j, i) = j
            + flowMapY.at<float>(j, i) * q;
        }
    }
}

void ofApp::update(){

    int d = 20;
    float q = ofMap(mouseX, 0, ofGetWidth(), -d, d);
//    float q = ofMap(mouseX, 0, ofGetWidth(), position, position+1);
    
//    for (int i = 0; flowMapY.rows * flowMapY.cols; i++) {
//        tflowMapX
//    }

    cout << q << endl;
//    q = 1;
//
    for (int i = 0; i < flowMapX.cols; i++) {
        for (int j = 0; j < flowMapX.rows; j++) {
            tflowMapX.at<float>(j, i) = i - flowMapX.at<float>(j, i) * q;
            tflowMapY.at<float>(j, i) = j - flowMapY.at<float>(j, i) * q;
        }
    }
    
//    tflowMapX = flowMapX * q;
//    tflowMapY = flowMapY * q;
}


void ofApp::draw(){

    img1.draw(10, 10);
    img2.draw(img1.width+20, 10);
    
    result.draw(10, 20+img1.height);
    
//    newFrame = cv::Mat::zeros(one.size(), CV_32F);
    cv::remap(one, newFrame, tflowMapX, tflowMapY, CV_INTER_LINEAR);
    
    newImage.setFromPixels(newFrame.data, newImage.width, newImage.height, OF_IMAGE_GRAYSCALE);
    
    newImage.draw(img1.width+20, img1.height+20);
    
    
}


void ofApp::keyPressed(int key){

    KEY(OF_KEY_UP, position++);
    KEY(OF_KEY_DOWN, position--);
    
    for (int i = 0; i < flowMapX.cols; i++) {
        for (int j = 0; j < flowMapX.rows; j++) {
            tflowMapX.at<float>(j, i) = i - flowMapX.at<float>(j, i);
            tflowMapY.at<float>(j, i) = j - flowMapY.at<float>(j, i);
        }
    }
    
    cv::remap(one, newFrame, tflowMapX, tflowMapY, CV_INTER_LINEAR);
    
    one = newFrame.clone();

    
    getMap(one, two);
    
    

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
