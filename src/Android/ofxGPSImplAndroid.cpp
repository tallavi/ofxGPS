//
//  ofxGPSImplAndroid.cpp
//
//  Created by Tal Lavi on 10/12/14.
//
//

#include "ofxGPSImplAndroid.h"
#include "ofMain.h"
#include "ofxAndroidGPS.h"


ofxGPSImplAndroid::ofxGPSImplAndroid()
{
    ofxAndroidGPS::startGPS();

    ofAddListener(ofxAndroidGPS::locationChangedE, this, &ofxGPSImplAndroid::onLocationChanged);
}

void ofxGPSImplAndroid::onLocationChanged(ofxLocation& newLocation)
{
	m_gpsData.time = Poco::Timestamp();
    
	m_gpsData.hasLocation = true;

	m_gpsData.longitude = newLocation.longitude;
	m_gpsData.latitude = newLocation.latitude;
	m_gpsData.altitude = newLocation.altitude;

	m_gpsData.hasHeading = false;

	//m_gpsData.hasHeading = true;
	//m_gpsData.heading = 0;
}

ofxGPSData ofxGPSImplAndroid::getGPSData()
{
	return m_gpsData;
}

std::shared_ptr<ofxGPS> ofxGPS::create()
{
    return std::shared_ptr<ofxGPS>(new ofxGPSImplAndroid());
}

