////************************************************************************************************************////
////             TP3 : Full image processing chain                    	            							////
////                                                                                            				////
////																											////
////		                TRINOME WORK                        												////
////             Authors: ADOUM Okim BOKA, LAMAH Henry kpakilé && CISSE Abdoulaye IFI-Promotion 21 (P21)		////
////                                                                                                            ////															////
////														////												////
////         Compilation: make    																				////			
////		 Execution programme: ./TP3 <image name>				  											////
////																////										////
////				 		 Description: This program allows to apply all treatments 							////
////						 of a complete image processing chain                 								////
////																											//// 			
////	         Sources: http://docs.opencv.org/doc/tutorials/													////
////************************************************************************************************************////

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "fonctions.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    string imageName; //Nom de l'image a fournir
    displayWelcomeMessage();
    cin >> imageName;

	Mat initiale_image = imread(imageName);
	imageVerification(initiale_image);

    Mat image1;
    cvtColor(initiale_image, image1, COLOR_RGB2GRAY);
    imshow("image_grise",image1);

	
	// Convert a color image to a greyscale image on which to apply segmentation

	// conversion of the grayscale image to a binary image with the OTSU algorithm which allows to automatically determine
	// the threshold value based on the histogram and the modal regions constituting this histogram.
	// 255 and pixels with a higher value will be set to 0.
	// Binarization is the simplest type of segmentation.

	// Application of the OTSU algorithm for segmentation
	threshold(image1, image1, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);//Application de l'algorithme de OTSU pour la segmentation

	// below the treatment phase after segmentation

	// Definition of structuring elements
	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat image2;

	// Close the contours
    dilate(image1, image2, element);//dilatation
	erode(image2, image2, element1);//erosion

	// Declaration of a vector containing the contours of the detected regions
	vector<vector<Point> > contours;

	// find contours of detected regions
	findContours(image2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	// imshow ("img_after findcontours",img2);

	// labeling regions
	Mat markers = Mat::zeros(image2.size(), CV_32SC1);
	etiquetter(markers, contours);

	// random generation of colors
	vector<Vec3b> colors=generatAleatorColor(contours);

	// regions to color with different colors
	Mat image3 = Mat::zeros(markers.size(), CV_8UC3);
	coloringOfRegions(image3, markers, colors, contours);

	// And logic between the input img and the mask obtained after the post-segmentation
	Mat image4;
	initiale_image.copyTo(image4, image3);
	// ----- END of the post-segmentation phase -----

	// Presentation of the results

    display("Initial_image", initiale_image);
    
	display("Segmented_image_with_OTSU", image1);
    recorgingImage("Image_segmentation_otsu.png",image1);

    display("Image_after_segmentation", image3);
    recorgingImage("image_after_segmentation.png",image3);

    display("Image_segmentee", image4);
    recorgingImage("Image_segmentee.png",image4);

	waitKey(0);
	return 0;
}
