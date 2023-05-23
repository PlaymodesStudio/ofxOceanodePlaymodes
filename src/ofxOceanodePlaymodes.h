//
//  ofxOceanodePlaymodes.h
//
//
//  Created by Eduard Frigola Bagué on 14/01/2022.
//

#ifndef ofxOceanodePlaymodes_h
#define ofxOceanodePlaymodes_h

#include "VideoGrabberNodeBased.h"
#include "VideoRendererNodeBased.h"
#include "VideoRendererWindowNodeBased.h"
#include "LumaFilterNodeBased.h"
#include "VideoBufferNodeBased.h"
#include "VideoHeaderNodeBased.h"
#include "FeedbackFilterNodeBased.h"
#include "MultixFilter.h"
#include "VideoGrabberPS3EyeNodeBased.h"
#include "LooperFilter.h"
#include "FrameInspector.h"
#include "VideoTrioRendererNodeBased.h"
#include "EdgeBlendNodeBased.h"
#include "kaleidoscopeNodeBased.h"
#include "RepeaterFilter.h"
#include "GatorFilter.h"
#include "VideoPsLayer.h"
#include "VideoMixer2Ch.h"
#include "VideoFileGrabber.h"
#include "ColorCorrectFilter.h"
#include "GammaFilter.h"
#include "VideoSpliter.h"
#include "VideoSwitcher.h"
#include "BeatControl.h"
#include "Multix3DFilter.h"
//#include "ISFFilter.h"
#include "HalfToneFilter.h"
#include "inputProcessingFilter.h"
#include "MirrorRenderer.h"
#include "ImageFileGrabber.h"

#include "ofxOceanode.h"

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

namespace ofxOceanodePlaymodes{
static void registerModels(ofxOceanode &o){
    o.registerModel<ofxPm::VideoGrabberNodeBased>("Video/Grabber");
    o.registerModel<ofxPm::VideoRendererNodeBased>("Video/Renderer");
    o.registerModel<ofxPm::VideoRendererWindowNodeBased>("Video/Renderer");
    o.registerModel<ofxPm::LumaFilterNodeBased>("Video/Filter");
    o.registerModel<ofxPm::VideoBufferNodeBased>("Video/Basic");
    o.registerModel<ofxPm::VideoHeaderNodeBased>("Video/Basic");
    o.registerModel<ofxPm::FeedbackFilterNodeBased>("Video/Filter");
    //o.registerModel<ofxPm::VideoGrabberPS3EyeNodeBased>("Video/Grabber");
    o.registerModel<ofxPm::RepeaterFilter>("Video/Filter");
    o.registerModel<ofxPm::LooperFilter>("Video/Filter");
    o.registerModel<ofxPm::VideoTrioRendererNodeBased>("Video/Renderer");
    o.registerModel<ofxPm::FrameInspector>("Video/Basic");
    o.registerModel<ofxPm::MultixFilter>("Video/Filter");
    o.registerModel<ofxPm::EdgeBlendNodeBased>("Video/Filter");
    o.registerModel<ofxPm::kaleidoscopeNodeBased>("Video/Filter");
    o.registerModel<ofxPm::GatorFilter>("Video/Filter");
    o.registerModel<ofxPm::VideoPsLayer>("Video/Mixer");
    o.registerModel<ofxPm::VideoMixer2Ch>("Video/Mixer");
    o.registerModel<ofxPm::VideoFileGrabber>("Video/Grabber");
    o.registerModel<ofxPm::ColorCorrectFilter>("Video/Filter");
    o.registerModel<ofxPm::GammaFilter>("Video/Filter");
    o.registerModel<ofxPm::VideoSpliter>("Video/Mixer");
    o.registerModel<ofxPm::VideoSwitcher>("Video/Mixer");
    o.registerModel<ofxPm::BeatControl>("Video/Basic");
    o.registerModel<ofxPm::Multix3DFilter>("Video/Filter");
    //    o.registerModel<ISFFilter>("Video/Filter");
    o.registerModel<ofxPm::HalfToneFilter>("Video/Filter");
    o.registerModel<ofxPm::inputProcessingFilter>("Video/Filter");
    o.registerModel<ofxPm::MirrorRenderer>("Video/Filter");
    o.registerModel<ofxPm::ImageFileGrabber>("Video/Grabber");
    o.registerModel<ofxPm::videoFrameToTex>("Video/Helpers");
    o.registerModel<ofxPm::texToVideoFrame>("Video/Helpers");
}
static void registerType(ofxOceanode &o){
    o.registerType<ofxPm::VideoFrame>("VideoFrame");
    o.registerType<ofxPm::VideoBufferNodeBased*>("VideoBuffer");
}
static void registerScope(ofxOceanode &o){
    o.registerScope<ofxPm::VideoFrame>([](ofxOceanodeAbstractParameter *p, ImVec2 size){
        auto vFrame = p->cast<ofxPm::VideoFrame>().getParameter().get();
        auto size2 = ImGui::GetContentRegionAvail();

        if(!vFrame.isNull()){
            ImTextureID textureID = (ImTextureID)(uintptr_t)vFrame.getTextureRef().texData.textureID;
            ImGui::Image(textureID, size2);
        }
    });
}
static void registerCollection(ofxOceanode &o){
    registerModels(o);
    registerType(o);
    registerScope(o);
}
}

#endif /* ofxOceanodePlaymodes_h */
