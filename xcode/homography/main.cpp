//
//  main.cpp
//  homography
//
//  Created by Gaston on 1/23/13.
//
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    Mat pattern, captor;
    string resources="/Users/Gaston/dev/RDC/resources/";
    pattern = imread(resources + "chessboard65.jpg");
    captor = imread(resources + "chesspic2.jpg");
    resize(captor, captor, Size(pattern.cols, pattern.cols*captor.rows/captor.cols));
    
    Size boardSize(5, 4);
    
    vector<Point2f> patternCorners;
    bool patternFound = findChessboardCorners(pattern, boardSize, patternCorners);

    vector<Point2f> picCorners;
    bool picFound = findChessboardCorners(captor, boardSize, picCorners);
    


    Mat homo = findHomography(patternCorners, picCorners);
    
    drawChessboardCorners(pattern, boardSize, patternCorners, patternFound);
    drawChessboardCorners(captor, boardSize, picCorners, picFound);
    
    Mat result;
    warpPerspective(pattern, // input image
                    result,         // output image
                    homo,      // homography
                    Size(captor.cols,
                             captor.rows));
    
    imshow("pattern", pattern);
    imshow("result", result);
    imshow("pic", captor);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

