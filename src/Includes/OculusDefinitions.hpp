/*
 * OculusDefinitions.hpp
 *
 *  Created on: Apr 7, 2014
 *      Author: lex
 */

#ifndef OCULUSDEFINITIONS_HPP_
#define OCULUSDEFINITIONS_HPP_

//#include "../Oculus/OculusPraticus/OculusPraticus.hpp"
#include <iostream>
#include <list>
#include <assert.h>
#include <boost/filesystem.hpp>
#include "opencv2/opencv.hpp"


using namespace std;

typedef unsigned int uint;

const uint maxPraticusConnections = 2;

const uint maxPraticusConnectionNum = 1;

typedef enum
{
	PRATICUS_FIRST = 0,
	PRATICUS_SOURCE = PRATICUS_FIRST,	// 0 - camera
	PRATICUS_AMPLIFICATION, 			// 1 - IQ
	PRATICUS_MITTENTIS,					// 2 - streaming
	PRATICUS_QUAERO,					// 3 - template recognition
	PRATICUS_HISTORIAM,					// 4 - motion history
	PRATICUS_HAURIRE,					// 5 - display
	PRATICUS_AUFERO,					// 6 - cleanup
	PRATICUS_NULL,						// 7 - for different cases
	PRATICUS_LAST = PRATICUS_NULL,
	PRATICUS_MAX = PRATICUS_LAST + 1
}PraticusType;

typedef enum
{
	IQ_TYPE_DILATE,
	IQ_TYPE_ERODE,
	IQ_TYPE_GAUSSIAN_BLUR,
	IQ_TYPE_MAX
}IQType;

typedef struct GaussianBlurParameter
{
	cv::Size kernSize;
	double sigmaX;
	double sigmaY;
}GaussianBlurParameter;

typedef struct PraticusConfiguration
{
	PraticusType praticusId;
	string praticusName;
	PraticusConfiguration(PraticusType _praticusId, string _praticusName):praticusId(_praticusId), praticusName(_praticusName){};
	PraticusConfiguration():praticusId(PRATICUS_MAX), praticusName(""){};
}PraticusConfiguration;

typedef struct PraticusConnection
{
	PraticusType firstPraticus;
	uint firstPraticusOut;
	PraticusType secondPraticus;
	uint secondPraticusIn;
	uint qSize;
	PraticusConnection(PraticusType _firstPraticus,
					   uint _firstPraticusOut,
					   PraticusType _secondPraticus,
					   uint _secondPraticusIn,
					   uint _qSize):
						   firstPraticus(_firstPraticus),
						   firstPraticusOut( _firstPraticusOut ),
						   secondPraticus(_secondPraticus),
						   secondPraticusIn( _secondPraticusIn ),
						   qSize(_qSize ){};

	PraticusConnection():firstPraticus(PRATICUS_MAX),
						 firstPraticusOut( 0 ),
						 secondPraticus(PRATICUS_MAX),
						 secondPraticusIn( 0 ),
						 qSize( 0 ){};
}PraticusConnection;

typedef enum
{
	OC_PRAEFECTUS_TYPE_DEFAULT =0,
	OC_PRAEFECTUS_TYPE_WITHOUT_DISPLAY =1,
	OC_PRAEFECTUS_TYPE_LAST = OC_PRAEFECTUS_TYPE_WITHOUT_DISPLAY,
	OC_PRAEFECTUS_TYPE_MAX = OC_PRAEFECTUS_TYPE_LAST + 1
}OcPraefectusType;

typedef struct OculusConfiguration
{
	PraticusConfiguration* praticusList;
	PraticusConnection* connectionList;
	OcPraefectusType oculusType;
	OculusConfiguration(PraticusConfiguration* _praticusList, PraticusConnection* _connectionList, OcPraefectusType _oculusType):
																					praticusList(_praticusList),
																					connectionList( _connectionList ),
																					oculusType(_oculusType){};
	OculusConfiguration():praticusList(NULL), connectionList(NULL), oculusType(OC_PRAEFECTUS_TYPE_DEFAULT){};
}OculusConfiguration;

typedef struct VideoParameters
{
	uint deviceNum;
	uint videoWidth;
	uint videoHeight;
	uint desiredFPS;
}VideoParameters;

typedef struct IQParameters
{
	IQType filterType;
	void* filterParams;
}IQParameters;

typedef struct OculusParameters
{
	VideoParameters* videoParam;
	IQParameters* iqParam;
	string templateDir;
}OculusParameters;


class OculusPraticus;

class PraticusQueue;

/*
 * Class singleton
 * Implements initialization, control, destruction
 * of computer vision pipeline *
 */

class OculusPraefectus
{
private:

	static OculusPraefectus* praefectusEx;

	explicit OculusPraefectus();

	explicit OculusPraefectus( const OculusPraefectus &oculus );         //only declaration

	explicit OculusPraefectus( OculusPraefectus &oculus );               //only declaration

	const OculusPraefectus& operator = (OculusPraefectus &oculus);       //only declaration

	list<OculusPraticus*> OculuspraticusList;

	list<PraticusQueue*> OculusConnectionsList;

	OculusPraticus* OculusCreatePraticusById( PraticusType praticusId, string praticusName );

	bool OculusCreatePraticus( );

	bool OculusConnectPraticus( );

	virtual ~OculusPraefectus(){};

public:

	//main method to destroy OculusPraefectus
	static void OculusDestroyPraefectus();

	//main method to create OculusPraefectus
	static OculusPraefectus* OculusGetPraefectus( )
	{
		if ( praefectusEx == NULL )
		{
			static OculusPraefectus selfConstr;
			praefectusEx = &selfConstr;
		}

		return praefectusEx;
	}

	bool OculusInitPraefectus( OcPraefectusType praefectusType );
	// set state to RUN for all Praticuses
	bool OculusPraticusAnimatis();
	// creates a thread for each Praticus
	bool OculusSpawnPraticusesTasks();

	bool OculusFindConfigurationType( OcPraefectusType praefectusType );
	//config Oculus and Praticuses
	bool OculusPraestarePraeviamInstallation( OculusParameters* ocParams );

	void OculusDumpAllPraticuses();

	OculusPraticus* OculusGetPraticusByType( PraticusType praticusType );

	OculusConfiguration* m_currentOculusConfig;

	OculusParameters* m_currentFlowConfig;
};




typedef OculusPraefectus* hOculus;

//interface to create and init OculusPraefectus
bool CreateOculus( OcPraefectusType ocType, hOculus &hPraefectus);

bool ConfigOculus( hOculus hPraefectus, OculusParameters* ocParams );

bool RunOculus( hOculus hPraefectus );


#endif /* OCULUSDEFINITIONS_HPP_ */
