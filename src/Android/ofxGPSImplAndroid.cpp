//
//  ofxGPSImplAndroid.cpp
//
//  Created by Tal Lavi on 10/12/14.
//
//

#include "ofxGPSImplAndroid.h"
#include "ofMain.h"
#include "ofxAndroidUtils.h"
#include <jni.h>

ofEvent<ofxGPSData> ofxGPSImplAndroid::newGPSDataEvent;

ofxGPSImplAndroid::ofxGPSImplAndroid()
{
	ofAddListener(ofxGPSImplAndroid::newGPSDataEvent, this, &ofxGPSImplAndroid::onNewGPSData);

    startGPS();
}

ofxGPSImplAndroid::~ofxGPSImplAndroid()
{
	stopGPS();

	ofRemoveListener(ofxGPSImplAndroid::newGPSDataEvent, this, &ofxGPSImplAndroid::onNewGPSData);
}

ofxGPSData ofxGPSImplAndroid::getGPSData()
{
	Poco::Mutex::ScopedLock lock(m_mutex);

	return m_gpsData;
}

void ofxGPSImplAndroid::onNewGPSData(ofxGPSData& gpsData)
{
	Poco::Mutex::ScopedLock lock(m_mutex);

	m_gpsData = gpsData;
}

std::shared_ptr<ofxGPS> ofxGPS::create()
{
    return std::shared_ptr<ofxGPS>(new ofxGPSImplAndroid());
}

void ofxGPSImplAndroid::startGPS(){

	ofCallStaticVoidJavaMethod("cc/openframeworks/OFAndroidGPS$Singleton", "startGPS", "()V");
}

void ofxGPSImplAndroid::stopGPS(){

	ofCallStaticVoidJavaMethod("cc/openframeworks/OFAndroidGPS$Singleton", "stopGPS", "()V");
}

extern "C"{
void
Java_cc_openframeworks_OFAndroidGPS_locationChanged( JNIEnv*  env, jobject  thiz, jdouble altitude, jdouble latitude, jdouble longitude, jfloat speed, jfloat bearing ){

	ofxGPSData gpsData;

	gpsData.time = Poco::Timestamp();

	gpsData.hasLocation = true;
	gpsData.longitude = longitude;
	gpsData.latitude = latitude;

	gpsData.hasAltitude = true;
	gpsData.altitude = altitude;

	gpsData.hasHeading = true;
	gpsData.heading = bearing;

	ofNotifyEvent(ofxGPSImplAndroid::newGPSDataEvent, gpsData);
}
}

