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


void my_mouse_callback( int event, int x, int y, int flags, void* param );
Point getPoint(int x, int y, const Mat* homo);    //<! used to retrieve point*homography
void drawPointOnBoth(Point pos);

Mat homo;
Mat pattern, captor;

int main(int argc, const char * argv[])
{

    string resources="/Users/Gaston/dev/RDC/resources/";
    cout << "init" << endl;
    pattern = imread(resources + "chessboard65.jpg");
    captor = imread(resources + "chesspic2.jpg");
    int width = pattern.cols;
    
    
    Size boardSize(5, 4);
    
    vector<Point2f> patternCorners;
    bool patternFound = findChessboardCorners(pattern, boardSize, patternCorners);
    
    vector<Point2f> picCorners;
    bool picFound = findChessboardCorners(captor, boardSize, picCorners);
    
    drawChessboardCorners(pattern, boardSize, patternCorners, patternFound);
    drawChessboardCorners(captor, boardSize, picCorners, picFound);
    Mat result;
    

    
    if(patternFound && picFound)
    {
        homo = (findHomography(patternCorners, picCorners));
        warpPerspective(pattern, // input image
                        result,         // output image
                        homo,      // homography
                        Size(result.cols,
                             result.rows));
    }
    
    
    

    
    while(1)
    {
        Mat pattern_, captor_, result_;
        Size renderSize(width, width*pattern.rows/pattern.cols);
        resize(pattern, pattern_, renderSize);
        resize(captor, captor_, renderSize);
        resize(result, result_, renderSize);
        
        imshow("pattern", pattern_);
        //imshow("result", result);
        imshow("pic", captor_);
        setMouseCallback("pic", my_mouse_callback);
        
        if(waitKey(20) > 0)
        {
            break;
        }
    }
    destroyAllWindows();
    return 0;
}

void my_mouse_callback( int event, int x, int y, int flags, void* param ){
    
    switch( event ){
        case CV_EVENT_MOUSEMOVE:
            
            break;
            
        case CV_EVENT_LBUTTONDOWN:
            cout << "clicked at " << x << ", " << y << endl;
            drawPointOnBoth(Point(x, y));
            break;

    }
};

Point getPoint(Point pos, const Mat* homo) 
{
    Mat h = *homo;
    cout << h << endl;
    cout << h.ptr<double>(2)[0] << endl;
    double x = pos.x;
    double y = pos.y;
    double Z = 1./(h.ptr<double>(2)[0]*x + h.ptr<double>(2)[1]*y + h.ptr<double>(2)[2]);
    double px = (double)((h.ptr<double>(0)[0]*x + h.ptr<double>(0)[1]*y + h.ptr<double>(0)[2])*Z);
    double py = (double)((h.ptr<double>(1)[0]*x + h.ptr<double>(1)[1]*y + h.ptr<double>(1)[2])*Z);
    Point pt(px, py);
    cout << pt<<endl;;
    return pt;
};

void drawPointOnBoth(Point pos)
{
    circle( pattern,
           pos,
           10.0,
           Scalar( 0, 0, 255 ),
           -1,
           8 );
    Point dstPoint(getPoint(pos, &homo));
    circle( captor,
           dstPoint,
           10.0,
           Scalar(0,0,255),
           -1,
           8.0);
};
