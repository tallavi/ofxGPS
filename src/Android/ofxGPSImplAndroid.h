//
//  ofxGPSImplAndroid.h
//
//  Created by Tal Lavi on 10/12/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGPS.h"
#include "ofxGPS_old.h"

class ofxGPSImplAndroid : public ofxGPS
{

private:

    ofxGPSData m_gpsData;

private:

    void onLocationChanged(ofxLocation& newLocation);

public:

    ofxGPSImplAndroid();
    
    virtual ~ofxGPSImplAndroid(){};

    virtual ofxGPSData getGPSData();
    
    static std::shared_ptr<ofxGPS> create();

};

