#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main()
{

	string filepath = "Resources/face_rotating.mp4";
	
	VideoCapture video(filepath);

	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

	Mat img;

	while (true)
	{
		for(int skip = 0; skip < 10 && video.isOpened(); skip++)
			video.read(img);

		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for (size_t i = 0; i < faces.size(); i++)
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);

		imshow("Image", img);
		waitKey(1);
	}
}