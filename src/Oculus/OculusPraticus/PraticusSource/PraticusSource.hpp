/*
 * PraticusSource.hpp
 *
 *  Created on: May 4, 2014
 *      Author: lex
 */

#ifndef PRATICUSSOURCE_HPP_
#define PRATICUSSOURCE_HPP_

#include "../OculusPraticus.hpp"

class PraticusSource: protected OculusPraticus
{
public:
	OculusPraticus* CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );
	PraticusSource();

	PraticusSource( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~PraticusSource();

protected:

	VideoCapturePtr cameraHandler;

	uint cameraDeviceNum;

	uint flowWidth;

	uint flowHeight;

	string winName;

	uint64 frameNum;

	bptTime workStartTime;

	void BaseSourceInitialization();

	virtual int Processus( );
};


#endif /* PRATICUSSOURCE_HPP_ */
