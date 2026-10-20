//
//  ofxOceanodePlaymodes.h
//
//
//  Created by Eduard Frigola Bagué on 14/01/2022.
//

#ifndef ofxOceanodePlaymodes_h
#define ofxOceanodePlaymodes_h

// Declarations only: the node headers and the bodies live in ofxOceanodePlaymodes.cpp, so
// including this header does not compile every node of the addon again.

class ofxOceanode;

namespace ofxOceanodePlaymodes{

void registerModels(ofxOceanode &o);
void registerType(ofxOceanode &o);
void registerScope(ofxOceanode &o);
void registerCollection(ofxOceanode &o);

}

#endif /* ofxOceanodePlaymodes_h */
