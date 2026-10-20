//
//  videoFrameTexBridge.h
//  ofxOceanodePlaymodes
//
//  The VideoFrame <-> ofTexture* helper nodes, moved out of
//  ofxOceanodePlaymodes.h unchanged.
//

#ifndef videoFrameTexBridge_h
#define videoFrameTexBridge_h

#include "ofxOceanodeNodeModel.h"
#include "VideoFrame.h"
#include "VideoSource.h"

namespace ofxPm{

class videoFrameToTex : public ofxOceanodeNodeModel{
public:
    videoFrameToTex() : ofxOceanodeNodeModel("VideoFrame To Tex"){}

    void setup(){
        addParameter(input.set("Input", VideoFrame()));
        addOutputParameter(output.set("Output", nullptr));

        listener = input.newListener([this](VideoFrame &frame){
            if(!frame.isNull())
                output = &frame.getTextureRef();
        });
    }

private:
    ofEventListener listener;
    ofParameter<VideoFrame> input;
    ofParameter<ofTexture*> output;
};

class texToVideoFrame : public VideoSource, public ofxOceanodeNodeModel{
public:
    texToVideoFrame() : ofxOceanodeNodeModel("Tex To VideoFrame"){}

    void setup(){
        addParameter(input.set("Input", nullptr));
        addOutputParameter(output.set("Output", VideoFrame()));
        
        listener = input.newListener([this](ofTexture* &tex){
            if(tex != nullptr){
                if(!fbo.isAllocated() || fbo.getWidth() != tex->getWidth() || fbo.getHeight() != tex->getHeight()){
                    fbo.allocate(tex->getWidth(), tex->getHeight(), GL_RGBA);
                }
                fbo.begin();
                tex->draw(0, 0);
                fbo.end();
                frame = VideoFrame::newVideoFrame(fbo.getTexture());
                output = frame;
            }
        });
    }
    
    VideoFrame getNextVideoFrame(){return frame;};
    float getFps(){return 120;};

private:
    VideoFrame frame;
    ofFbo fbo;
    
    ofEventListener listener;
    ofParameter<VideoFrame> output;
    ofParameter<ofTexture*> input;
};
}

#endif /* videoFrameTexBridge_h */
