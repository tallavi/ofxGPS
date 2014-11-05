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
	ofLogVerbose("GPS") << "starting";

	jobject temp = ofGetOFActivityObject();

	ofLogVerbose("GPS") << "got activity: " << temp;

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
	return m_gpsData;
}

//TALTODO: this is being called on a different thread. synchronize.
void ofxGPSImplAndroid::onNewGPSData(ofxGPSData& gpsData)
{
	ofLogVerbose("GPS") << "new data (2)";

	m_gpsData = gpsData;
}

std::shared_ptr<ofxGPS> ofxGPS::create()
{
    return std::shared_ptr<ofxGPS>(new ofxGPSImplAndroid());
}

void ofxGPSImplAndroid::startGPS(){

	jclass OFAndroid = ofGetJavaOFAndroid();

	if(OFAndroid==0){
		ofLogError("ofxAndroidGPS") << "startGPS(): couldn't find OFAndroid java class";
		return;
	}

	jmethodID setupGPS = ofGetJNIEnv()->GetStaticMethodID(OFAndroid,"setupGPS","()V");
	if(!setupGPS){
		ofLogError("ofxAndroidGPS") << "startGPS(): couldn't find OFAndroid.setupGPS method";
		return;
	}
	ofGetJNIEnv()->CallStaticVoidMethod(OFAndroid,setupGPS);
}

void ofxGPSImplAndroid::stopGPS(){
	jclass OFAndroid = ofGetJavaOFAndroid();

	if(OFAndroid==0){
		ofLogError("ofxAndroidGPS") << "stopGPS(): couldn't find OFAndroid java class";
		return;
	}

	jmethodID stopGPS = ofGetJNIEnv()->GetStaticMethodID(OFAndroid,"stopGPS","()V");
	if(!stopGPS){
		ofLogError("ofxAndroidGPS") << "stopGPS(): couldn't find OFAndroid.stopGPS method";
		return;
	}
	ofGetJNIEnv()->CallStaticVoidMethod(OFAndroid,stopGPS);
}

extern "C"{
void
Java_cc_openframeworks_OFAndroidGPS_locationChanged( JNIEnv*  env, jobject  thiz, jdouble altitude, jdouble latitude, jdouble longitude, jfloat speed, jfloat bearing ){

	ofLogVerbose("GPS") << "new data (1)";

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

