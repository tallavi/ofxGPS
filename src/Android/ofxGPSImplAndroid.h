//
//  ofxGPSImplAndroid.h
//
//  Created by Tal Lavi on 10/12/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGPS.h"
#include "ofEvents.h"

class ofxGPSImplAndroid : public ofxGPS
{

private:

	ofxGPSData m_gpsData;

private:

    void startGPS();
    void stopGPS();

public:

    ofxGPSImplAndroid();
    
    virtual ~ofxGPSImplAndroid();

    virtual ofxGPSData getGPSData();
    
    void onNewGPSData(ofxGPSData& gpsData);

public:

    static std::shared_ptr<ofxGPS> create();

    static ofEvent<ofxGPSData> newGPSDataEvent;

    template<class Listener>
    static void registerGPSEvent(Listener * listener){
    	ofAddListener(ofxGPSImplAndroid::newGPSDataEvent, listener, &Listener::newGPSData);
    }

    template<class Listener>
    static void unregisterGPSEvent(Listener * listener){
    	ofRemoveListener(ofxGPSImplAndroid::newGPSDataEvent, listener, &Listener::newGPSData);
    }
};


