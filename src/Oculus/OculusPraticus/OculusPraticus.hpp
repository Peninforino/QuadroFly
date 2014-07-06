/*
 * OculusPraticus.hpp
 *
 *  Created on: Feb 26, 2014
 *      Author: lex
 */

#ifndef OCULUSPRATICUS_HPP_
#define OCULUSPRATICUS_HPP_

#include <queue>
#include "../../Includes/OculusDefinitions.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/thread/thread.hpp"
#include "boost/bind.hpp"
#include "boost/thread/mutex.hpp"

using namespace std;
using namespace cv;


typedef enum
{
	IMAGE_RECIEVE_STATUS_FIRST_FRAME = 0,
	IMAGE_RECIEVE_STATUS_NORMAL,
	IMAGE_RECIEVE_STATUS_NO_DATA,
	IMAGE_RECIEVE_STATUS_ERROR,
	IMAGE_RECIEVE_STATUS_LAST_FRAME
}RecieveStatus;

typedef enum
{
	IMAGE_DELIVER_STATUS_NORMAL = 0,
	IMAGE_DELIVER_STATUS_FULL
}DeliverStatus;

typedef enum
{
	QUEUE_DIRECTION_INPUT = 0,
	QUEUE_DIRECTION_OUPTUT
}PraticusQueueDirection, QDir;


typedef enum
{
	PRATICUS_STATE_IDLE = 0,
	PRATICUS_STATE_RUN,
	PRATICUS_STATE_ABORT
}PraticusState;

typedef unsigned int uint;

typedef boost::shared_ptr<boost::thread> boostThrPtr;

typedef boost::shared_ptr<VideoCapture> VideoCapturePtr;

typedef boost::posix_time::ptime bptTime;

class OculusPraefectus;

/* Imaginis - image handler
 *
 */
class Imaginis
{
public:
	Imaginis(uint _width, uint _height);

	Imaginis();

	virtual ~Imaginis();

	Mat* image;
	uint64 frameNumber;
	uint64 frameEpoch;
	uint64 timeStamp;
	uint width;
	uint height;
	vector <vector <Point> > recognitionResult;
};

/* PraticusQueue - queue between two connected Praticuses
 *
 */

class PraticusQueue
{
private:
	uint m_qLimit;

	uint m_qSize;

	queue<Imaginis*> m_queue;

	boost::mutex queueProtectionMutex;

	OculusPraticus* m_sourcePraticus;

	OculusPraticus* m_targetPraticus;

public:

	PraticusQueue( uint _qLimit );

	static PraticusQueue* CreateQueueBetween( OculusPraticus* first, uint firstOut, OculusPraticus* second, uint secondOut, uint qSize );

	DeliverStatus Deliver( Imaginis* Image );

	RecieveStatus Recieve( Imaginis** Image );

	bool ConnectSource( OculusPraticus* _firstPraticus, uint firstOut );

	bool ConnectDesctination( OculusPraticus* _secondPraticus, uint secondOut );

	OculusPraticus* GetSourcePraticus()
	{
		return m_sourcePraticus;
	}

	OculusPraticus* GetTragetPraticus()
	{
		return m_targetPraticus;
	}

	bool SetSourcePraticus( OculusPraticus* source)
	{
		m_sourcePraticus = source;
		return true;
	}

	bool SetTargetPraticus( OculusPraticus* target)
	{
		m_targetPraticus = target;
		return true;
	}

};


//Interface
class OculusPraticus {
public:

	OculusPraticus();

	OculusPraticus( OculusPraefectus* praefectus, PraticusType _praticusType, string _praticusName );

	virtual ~OculusPraticus();
	//Thread initialization & start
	void Facere();

	//routine for thread where Processus() will be executed
	virtual void PraticusCuram();

	virtual OculusPraticus* CreatePraticus(OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName ) = 0;

	uint64 GetPraticusTimeStamp()
	{
		return m_actualTimeStamp;
	}

	string GetPraticusName()
	{
		return m_praticusName;
	}

	PraticusType GetPraticusType()
	{
		return m_praticusType;
	}

	bool SetPraticusState( PraticusState _newState )
	{
		m_praticusState = _newState;
		return true;
	}

	PraticusState GetPraticusState()
	{
		return m_praticusState;
	}

	PraticusQueue* GetInputQueue( uint inQNum )
	{
		assert (inQNum <= maxPraticusConnectionNum );
		return m_inputQueue[inQNum];
	}

	PraticusQueue* GetOutputQueue( uint outQNum )
	{
		assert (outQNum <= maxPraticusConnectionNum );
		return m_outputQueue[outQNum];
	}

	bool SetInputQueue (PraticusQueue* inQ, uint inNum );

	bool SetOutputQueue (PraticusQueue* outQ, uint outNum );

protected:

	//main cycle of pipeline part
	virtual int Processus( ) = 0;
	//Abort
	virtual int Abortum();
	//Recieve image
	virtual RecieveStatus ImaginisRecieve( uint inQNum, Imaginis** Image );
	//Send image next to pipeline through pointed queue
	virtual DeliverStatus ImaginisSend( uint outQNum , Imaginis* image );
	//Send image next to pipeline through all initialized queues
	//Note that returned value will be actual for the last queue only
	virtual DeliverStatus ImaginisSend( Imaginis* image );

	OculusPraefectus* m_praefectus;

	PraticusQueue* m_inputQueue[maxPraticusConnections];

	PraticusQueue* m_outputQueue[maxPraticusConnections];
	//thread to execute PraticusCuram
	boostThrPtr m_taskExecuter;

	uint64 m_actualTimeStamp;

	string m_praticusName;

	PraticusType m_praticusType;

	PraticusState m_praticusState;
};

//C interface to create Praticus
OculusPraticus* CreatePraticusSource( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusAmplification( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusMittentis( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusQuaero( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusHistoriam( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusHaurire( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );

OculusPraticus* CreatePraticusAufero( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName );


#endif /* OCULUSPRATICUS_HPP_ */
