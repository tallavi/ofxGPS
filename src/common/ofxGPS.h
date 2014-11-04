//
//  ofxGPS.h
//
//  Created by Tal Lavi on 10/2/14.
//
//

#pragma once

#include "ofMain.h"
#include "ILocationProvider.h"

struct ofxGPSData
{
    bool hasLocation;
    double longitude;
    double latitude;
    
    bool hasAltitude;
    double altitude;
    
    bool hasHeading;
    double heading;
    
    Poco::Timestamp time;
}

class ofxGPS
{
    
public:
    
    virtual ofxGPS() { }
    
    virtual ofxGPSData getGPSData() = 0;
};

class ofxGPSFactory
{
    
public:
    static std::shared_ptr<ofxGPS> create();
    
};



