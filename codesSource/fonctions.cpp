#include "fonctions.h"

void displayWelcomeMessage(){
    cout << "--------------------------------------------------------------------------";
    cout << "\n WELCOME IN OUR PROGRAM.\n ENTER THE PATH"<<endl;
    cout << "--------------------------------------------------------------------------\n IMAGE NAME :\t";
}
void imageVerification(Mat image_initiale){
    if (!image_initiale.data) {
		cout << "L'image fournie n'est pas valide\n" << endl;
		exit(EXIT_FAILURE);
	}
}

  void display(string windowName, Mat image){
    imshow(windowName, image);
  }

  void recorgingImage(string imageName, Mat image){
	if (!imwrite(imageName, image))
		cout << "Echec de l'enregistrement" << endl;
  }

  vector<Vec3b> generatAleatorColor(vector<vector<Point> > contours){
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++) {
		int blue = theRNG().uniform(0, 255);
		int green = theRNG().uniform(0, 255);
		int red = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar) blue, (uchar) green, (uchar) red));
	}
	return colors;
  }

  void etiquetter(Mat markers,vector<vector<Point> > contours){
    for (size_t i = 0; i < contours.size(); i++)
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1), -1);
  }


  void coloringOfRegions(Mat image3, Mat markers,vector<Vec3b> colors,vector<vector<Point> > contours){
     for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; j < markers.cols; j++) {
			int index = markers.at<int>(i, j);
			if (index > 0 && index <= static_cast<int>(contours.size()))
				image3.at<Vec3b>(i, j) = colors[index - 1];
			else
				image3.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
		}
	}
  }
