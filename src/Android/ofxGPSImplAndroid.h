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
#include "Poco/Mutex.h"
#include <jni.h>

class ofxGPSImplAndroid : public ofxGPS
{

private:

	jobject m_OFAndroidGPS;

	ofxGPSData m_gpsData;

	Poco::Mutex m_mutex;

public:

    ofxGPSImplAndroid();
    virtual ~ofxGPSImplAndroid();
    
    void startGPS();
    void stopGPS();

    virtual ofxGPSData getGPSData();

private:
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


