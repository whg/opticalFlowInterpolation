//
//  ofxFrameInterpolator.cpp
//  optical_flow_interp
//
//  Created by Will Gallia on 10/08/2015.
//
//

#include "ofxFrameInterpolator.h"

using namespace cv;

ofxFrameInterpolator::ofxFrameInterpolator(int width, int height): size(width, height) {
    
    frames[0] = cv::Mat::zeros(size.y, size.x, CV_8UC3);
    frames[1] = cv::Mat::zeros(size.y, size.x, CV_8UC3);
    
    
    for (int i = 0; i < 3; i++) {
        flowMap.x[i] = cv::Mat::zeros(size.y, size.x, CV_32F);
        flowMap.y[i] = cv::Mat::zeros(size.y, size.x, CV_32F);
    }
        
    interFlowX = cv::Mat::zeros(size.y, size.x, CV_32F);
    interFlowY = cv::Mat::zeros(size.y, size.x, CV_32F);
    
    
    nchannels = -1;
}

ofxFrameInterpolator::FlowMap& ofxFrameInterpolator::calcMap(ofImage &one, ofImage &two) {
    return calcMap(one.getPixels(), two.getPixels());
}

ofxFrameInterpolator::FlowMap& ofxFrameInterpolator::calcMap(ofPixels &one, ofPixels &two) {
    
    int format = one.getNumChannels() == 3 ? CV_8UC3 : CV_8U;
    
    frames[0] = cv::Mat(size.y, size.x, format, one.getData(), 0);
    frames[1] = cv::Mat(size.y, size.x, format, two.getData(), 0);
 
    cv::split(frames[0], channels[0]);
    cv::split(frames[1], channels[1]);
    
    nchannels = channels[0].size();
    newChannels = vector<Mat>(nchannels);

    for (int i = 0; i < nchannels; i++) {
        calcOpticalFlowFarneback(channels[0][i], channels[1][i], flow, 0.1, 5, 20, 15, 7, 10.1, 0);
        
        Mat &fx = flowMap.x[i];
        Mat &fy = flowMap.y[i];
        cv::Point2f p;
        
        for (int i = 0; i < flow.cols; i++) {
            for (int j = 0; j < flow.rows; j++) {
                p = flow.at<cv::Point2f>(j, i);
                fx.at<float>(j, i) = p.x;
                fy.at<float>(j, i) = p.y;
            }
        }
    }
    
    return flowMap;
}

void ofxFrameInterpolator::interploate(float q, ofImage &outputImage) {

    if (nchannels < 0) {
        cout << "ofxFrameInterpolator::interploate(): calcMap not called, returning" << endl;
        return;
    }

    for (int c = 0; c < nchannels; c++) {
        for (int i = 0; i < flow.cols; i++) {
            for (int j = 0; j < flow.rows; j++) {
    //            p = flow.at<cv::Point2f>(j, i);
                interFlowX.at<float>(j, i) = i - flowMap.x[c].at<float>(j, i) * q; //(flowMap.x[0].at<float>(j, i) - i) * q + i; //i - p.x;
                interFlowY.at<float>(j, i) = j - flowMap.y[c].at<float>(j, i) * q; //(flowMap.y[0].at<float>(j, i) - j) * q + j;
    //            flowMap.y[0].at<float>(j, i) = j - p.y;
            }
        }
        
        remap(channels[0][c], newChannels[c], interFlowX, interFlowY, CV_INTER_LINEAR);
        
    }
    
    cv::merge(newChannels, newFrame);
    
    //    remap(frames[1], newFrame, interFlowX, interFlowY, CV_INTER_LINEAR);
    
    outputImage.setFromPixels(newFrame.data, outputImage.getWidth(), outputImage.getHeight(), nchannels == 3 ? OF_IMAGE_COLOR: OF_IMAGE_GRAYSCALE);
    
//    newImage.draw(img1.width+20, img1.height+20);

}