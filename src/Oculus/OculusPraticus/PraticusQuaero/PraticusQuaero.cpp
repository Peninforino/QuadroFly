/*
 * PraticusQuaero.cpp
 *
 *  Created on: May 25, 2014
 *      Author: lex
 */


#include "PraticusQuaero.hpp"

PraticusQuaero::PraticusQuaero( OculusPraefectus* _praefectus,
								PraticusType _praticusType,
								string _praticusName ):OculusPraticus(_praefectus, _praticusType, _praticusName)
{
	m_minContourArea = 35;
	m_minContourLength = 55;
	m_huMatchCriteria = 0.082f;
	m_allowChildlessContours = false;

	return;
}

PraticusQuaero::~PraticusQuaero()
{

}


OculusPraticus* PraticusQuaero::CreatePraticus( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	OculusPraticus* quaero = new PraticusQuaero( _praefectus, _praticusType, _praticusName);

	return quaero;
}

int PraticusQuaero::Processus()
{
	Imaginis* workFrame;
	RecieveStatus result = ImaginisRecieve(0, &workFrame);

	if ( ( result == IMAGE_RECIEVE_STATUS_NO_DATA ) ||
		 ( result == IMAGE_RECIEVE_STATUS_ERROR ) )
	{
		return 0;
	}
	cout << GetPraticusName() << ": image received" << workFrame->frameNumber << endl;

	ImaginisSend(0, workFrame);

	return 0;
}

void PraticusQuaero::PrimordialisQuaero( std::string dirName )
{
	boost::filesystem::path jpgDirectory(dirName);

	if (boost::filesystem::exists(jpgDirectory))
	{
		cout << __FUNCTION__ << " directory " << jpgDirectory.string() << " found" << endl;
	}
	else
	{
		cout << __FUNCTION__ << " directory " << dirName << " doesn't exist!!" << endl;
		return;
	}

	boost::filesystem::directory_iterator startIt(jpgDirectory), endIt;

	for ( ; startIt != endIt; ++startIt )
	{
		if ( (startIt->path().filename().extension().string() == ".jpg") ||
			 (startIt->path().extension().string() == ".jpeg") ||
			 (startIt->path().extension().string() == ".JPG") ||
			 (startIt->path().extension().string() == ".JPEG") )
		{
			cout << __FUNCTION__ << " found jpg file, going to process " << startIt->path().filename().string() << endl;
		}
	}
}

bool PraticusQuaero::ExtractQuaeroFromImage( string filePath )
{
	Mat loadedImage;
	loadedImage = imread( filePath );

	assert(!loadedImage.empty());

	vector<vector <Point> > foundContours;
	vector<Vec4i> frameContoursHierarchy;
	Mat grayCanny = Mat(loadedImage.rows, loadedImage.cols, loadedImage.type());

	cvtColor(loadedImage, grayCanny, CV_RGB2GRAY);
	Canny(grayCanny, grayCanny, 80, 240, 5);

	findContours(grayCanny,
				 foundContours,
			     frameContoursHierarchy,
			     CV_RETR_TREE,
			     CV_CHAIN_APPROX_SIMPLE,
			     Point(0, 0));

	if ( foundContours.size() == 0 )
	{
		cout << __FUNCTION__ << ": failed to recognize contours in image " << filePath << endl;
		assert( 0 );
	}

	//search for the top contour
	int outContourIdx = FindOutContourFromTemplateImage( frameContoursHierarchy, foundContours.size() );

	if ( outContourIdx < 0 )
	{
		cout << __FUNCTION__ << ": failed to find out contour index" << endl;
		assert( 0 );
	}

	vector<Point> parentContour = foundContours[outContourIdx];

	//now search for children
	vector<vector<Point> > childrenContours;
	uint childrenContoursCounts = 0;

	for ( int i = 0; i < foundContours.size(); i++ )
	{
		if ( frameContoursHierarchy[i][3] == outContourIdx )
		{
			childrenContours.push_back(foundContours[i]);
			childrenContoursCounts++;
		}
	}

	if ( ( childrenContoursCounts == 0 ) && ( m_allowChildlessContours == false ) )
	{
		cout << __FUNCTION__ << ": detected childless contour, but childless is illegal" << endl;
		assert( 0 );
	}

	//all OK, create a cotour handlers
	SubQuaero* parent = new SubQuaero();
	parent->m_contour = parentContour;
	//parent->



	return true;
}

int PraticusQuaero::FindOutContourFromTemplateImage( vector<Vec4i> &frameContoursHierarchy, uint contourSize )
{
	int result = -1;

	if ( ( frameContoursHierarchy.size() != 0 ) || ( contourSize == 0 ) )
	{
		cout << __FUNCTION__ << " receives empty vector or zero size!" << endl;
		return result;
	}
	/*
	 * hierarchy[idx][{0,1,2,3}]=
	 * {next contour (same level),
	 * previous contour (same level),
	 * child contour,
	 * parent contour}
	 * */
	for ( int i = 0; i < contourSize; i++ )
	{
		if ( ( frameContoursHierarchy[i][0] < 0 ) ||
			 ( frameContoursHierarchy[i][1] < 0 ) ||
			 ( frameContoursHierarchy[i][2] > 0 ) ||
			 ( frameContoursHierarchy[i][3] < 0 ) )
		{
			result = i;
			break;
		}
	}

	return result;

}

OculusPraticus* CreatePraticusQuaero( OculusPraefectus* _praefectus, PraticusType _praticusType, string _praticusName )
{
	cout << __FUNCTION__ << endl;

	PraticusQuaero* quaero;

	OculusPraticus* praticus = quaero->PraticusQuaero::CreatePraticus( _praefectus, _praticusType, _praticusName );

	return praticus;
}



