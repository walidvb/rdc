//
//  Homo.cc
//  RDC
//
//  Created by Gaston on 1/29/13.
//
//

#include "Homo.h"

Homo::Homo(){
    boardSize = Size(5, 4);
}

Homo::Homo(Size boardSize_) : boardSize(boardSize)
{}


void Homo::addImages(Image src, Image trg){
    int successes = 0;
    // Get the chessboard corners
    vector<Point2f> srcCorners;
    bool srcFound = cv::findChessboardCorners(src.getPixels(), boardSize, srcCorners);
    vector<Point2f> trgCorners;
    bool trgFound = findChessboardCorners(trg.getPixels(), boardSize,trgCorners);

    if(!srcFound)
    {
        cout << "no ";
    }
    cout << "corners found" << endl;
    
    if(srcFound && trgFound)
    {
        // Get subpixel accuracy on the corners
        cornerSubPix(src.getPixels(), srcCorners,
                     Size(5,5),
                     Size(-1,-1),
                     TermCriteria(TermCriteria::MAX_ITER +
                                  TermCriteria::EPS,
                                  30,      // max number of iterations
                                  0.1));  // min accuracy
        // Get subpixel accuracy on the corners
        cornerSubPix(trg.getPixels(), trgCorners,
                     Size(5,5),
                     Size(-1,-1),
                     TermCriteria(TermCriteria::MAX_ITER +
                                  TermCriteria::EPS,
                                  30,      // max number of iterations
                                  0.1));  // min accuracy
        
        //If we have a good correspondance, add it to our data
        if (srcCorners.size() == trgCorners.size()) {
            // Add src and trg points to our total of points, point by point
            for(int i = 0; i < srcPoints.size(); i++)
            {
                srcPoints.push_back(srcCorners[i]);
                trgPoints.push_back(trgCorners[i]);
            }
            successes++;
        }
    }

}


Mat Homo::computeHomo(){
    homo = findHomography(srcPoints, trgPoints);
    return homo;
}


Point Homo::getPoint(int x, int y, Mat h) const{
    double Z = 1./(h.ptr<double>(2)[0]*x + h.ptr<double>(2)[1]*y + h.ptr<double>(2)[2]);
    double px = (double)((h.ptr<double>(0)[0]*x + h.ptr<double>(0)[1]*y + h.ptr<double>(0)[2])*Z);
    double py = (double)((h.ptr<double>(1)[0]*x + h.ptr<double>(1)[1]*y + h.ptr<double>(1)[2])*Z);
    Point pt(px, py);
    return pt;
}

Point Homo::getTargetPoint(int x, int y) const{
    return getPoint(x, y, homo);
}

Point Homo::getSourcePoint(int x, int y) const{
    return getPoint(x, y, homoInv);
}

Point Homo::getSourcePoint(const Point pos) const{
    return getSourcePoint(pos.x, pos.y);
}

Point Homo::getTargetPoint(const Point pos) const{
    return getTargetPoint(pos.x, pos.y);
}


//Getters
Mat Homo::getHomo() const{
    return homo;
}

Mat Homo::getHomoInv() const{
    return homoInv;
}

void Homo::setPattern(Image* pattern){}

