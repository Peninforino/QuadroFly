//============================================================================
// Name        : ObjectRecognitionAndControlSystem.cpp
// Author      : Alexey Marchuk
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Includes/OculusDefinitions.hpp"

#include <boost/thread/thread.hpp>


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

extern OculusParameters baseOculusParam;

int main() {

	string winName = "TestForSource";

	namedWindow(winName, CV_WINDOW_AUTOSIZE);

	hOculus hPraefectus;

	cout << "Going to create Oculus " << hPraefectus << endl;

	CreateOculus( OC_PRAEFECTUS_TYPE_DEFAULT, hPraefectus );

	ConfigOculus( hPraefectus, &baseOculusParam );

	hPraefectus->OculusDumpAllPraticuses();

	RunOculus( hPraefectus );

	cout << "type q to terminate programm" << endl;

	while (true)
	{
		char c = (char)waitKey(10);
		switch (c)
		{
			case 'q':
			case 'Q':
				{
					cout << "Terminate" << endl;
					return 1;
				}
		}

	}

}
