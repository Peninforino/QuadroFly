/*
 * PraticusSource.cpp
 *
 *  Created on: May 5, 2014
 *      Author: lex
 */

#include "PraticusSource.hpp"

PraticusSource::PraticusSource( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName),
														frameNum(0)
{
	BaseSourceInitialization();
	return;
}

PraticusSource::~PraticusSource()
{

}

void PraticusSource::BaseSourceInitialization()
{
	//TODO: implement method below
	//cameraDeviceNum = praefectus->OculusGetCurrentCameraDeviceNum();
	// and delete assignment below
	cameraDeviceNum = 0;
	//create camera handler
	cameraHandler = VideoCapturePtr(new VideoCapture(cameraDeviceNum));

	assert ( cameraHandler->isOpened() );

	//TODO: implement method below
	//praefectus->OculusGetFlowDimension( &flowWidth, &flowHeight);
	// and delete assignment below
	flowWidth = 640;
	flowHeight = 480;

	winName = "TestForSource";

	workStartTime = boost::posix_time::microsec_clock::local_time();

	//namedWindow(winName, CV_WINDOW_AUTOSIZE);

	return;
}

OculusPraticus* PraticusSource::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* source = new PraticusSource( _praefectus, _praticusType, _praticusName);

	return source;
}

int PraticusSource::Processus()
{
	Imaginis* workFrame = new Imaginis( flowWidth, flowHeight );

	cameraHandler->grab();
	cameraHandler->retrieve( *(workFrame->image), 3);

	assert( workFrame->image->data );

	workFrame->frameNumber = frameNum;
	frameNum++;

	bptTime currentTime = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration deltaTime = currentTime - workStartTime;
	workFrame->timeStamp = deltaTime.total_microseconds();

	cout << GetPraticusName() <<  (workFrame->image->empty() ? ": empty " : ": succeed ") << workFrame->frameNumber << endl;

	ImaginisSend(0, workFrame);

	return 0;
}

OculusPraticus* CreatePraticusSource( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusSource* source;

	OculusPraticus* praticus = source->PraticusSource::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}


