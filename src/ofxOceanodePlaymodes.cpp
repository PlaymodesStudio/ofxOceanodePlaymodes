//
//  ofxOceanodePlaymodes.cpp
//
//
//  Created by Eduard Frigola Bagué on 14/01/2022.
//

#include "ofxOceanodePlaymodes.h"
#include "ofxOceanode.h"
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
#include "videoFrameTexBridge.h"


namespace ofxOceanodePlaymodes{
void registerModels(ofxOceanode &o){
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
void registerType(ofxOceanode &o){
    o.registerType<ofxPm::VideoFrame>("VideoFrame");
    o.registerType<ofxPm::VideoBufferNodeBased*>("VideoBuffer");
}
void registerScope(ofxOceanode &o){
    o.registerScope<ofxPm::VideoFrame>([](ofxOceanodeAbstractParameter *p, ImVec2 size){
        auto vFrame = p->cast<ofxPm::VideoFrame>().getParameter().get();
        auto size2 = ImGui::GetContentRegionAvail();

        if(!vFrame.isNull()){
            ImTextureID textureID = (ImTextureID)(uintptr_t)vFrame.getTextureRef().texData.textureID;
            ImGui::Image(textureID, size2);
        }
    });
}
void registerCollection(ofxOceanode &o){
    registerModels(o);
    registerType(o);
    registerScope(o);
}
}
