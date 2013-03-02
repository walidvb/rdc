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


bool Homo::addImages(Mat* src, Mat* trg)
{
    int successes = 0;
    
        // Get the chessboard corners
    vector<Point2f> srcCorners;
    bool srcFound = findChessboardCorners(*src, boardSize, srcCorners);
    vector<Point2f> trgCorners;
    Mat trgTmp;
    bool trgFound = findChessboardCorners(*trg, boardSize, trgCorners);

    cout<<"[Homo] srcfound: "<<srcFound<<" targFound :"<<trgFound<<endl;
    if(srcFound && trgFound)
    {
        /*FIXME: because type is not mathching expected type
        //Convert to grayscale for cornerSubPix
        src->convertTo(*src, CV_8UC1);
        trg->convertTo(*trg, CV_8UC1);
        cout << trg->type() << endl;
        
        
        // Get subpixel accuracy on the corners
        cornerSubPix(*src, srcCorners,
                     Size(5,5),
                     Size(-1,-1),
                     TermCriteria(TermCriteria::MAX_ITER +
                                  TermCriteria::EPS,
                                  30,      // max number of iterations
                                  0.1));  // min accuracy
        // Get subpixel accuracy on the corners
        cornerSubPix(*trg, trgCorners,
                     Size(5,5),
                     Size(-1,-1),
                     TermCriteria(TermCriteria::MAX_ITER +
                                  TermCriteria::EPS,
                                  30,      // max number of iterations
                                  0.1));  // min accuracy
        
        */
        //If we have a good correspondance, add it to our data
        if (srcCorners.size() == trgCorners.size())
        {
            
            cout << "[Homo] correspondence points added: ";
            // Add src and trg points to our total of points, point by point
            for(int i = 0; i < srcCorners.size(); i++)
            {
                cout << i+1 << " " ;
                srcPoints.push_back(srcCorners[i]);
                trgPoints.push_back(trgCorners[i]);
                
            }
            cout << ";" << endl;
            successes++;
        }
        return true;
    }
    else
    {
        cout << "[Homo] No chessboard points found in image" << endl;
        return false;
    }
    
}

void Homo::computeHomo(){
    if(srcPoints.size() <= 0)
    {
        std::cerr << "[Homo] Not enough corresponding points found(" << srcPoints.size() << "found, 7 needed)" << endl;
    }
    homoInv = findHomography(trgPoints, srcPoints);
    homo = homoInv.inv();
}


Point Homo::getPoint(int x, int y, Mat& h)
{
    if(h.size <= 0)
    {
        cerr << "[Homo] Homography matrix has not been computed yet" << endl;
        exit(-1);
    }
    double Z = 1./(h.ptr<double>(2)[0]*x + h.ptr<double>(2)[1]*y + h.ptr<double>(2)[2]);
    double px = (double)((h.ptr<double>(0)[0]*x + h.ptr<double>(0)[1]*y + h.ptr<double>(0)[2])*Z);
    double py = (double)((h.ptr<double>(1)[0]*x + h.ptr<double>(1)[1]*y + h.ptr<double>(1)[2])*Z);
    Point pt(px, py);
    return pt;
}

Point Homo::getTargetPoint(int x, int y)
{
    return getPoint(x, y, homo);
}

Point Homo::getSourcePoint(int x, int y)
{
    return getPoint(x, y, homoInv);
}

Point Homo::getSourcePoint(const Point pos)
{
    return getSourcePoint(pos.x, pos.y);
}

Point Homo::getTargetPoint(const Point pos)
{
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

