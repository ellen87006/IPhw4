#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include<vector>


using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...

    Mat img = imread("/Users/sovietreborn/Desktop/lena_color.jpg"),imggray;
    if(img.empty())
    {
        fprintf(stderr, "Can not load image \n");
        return -1;
    }
    Mat resultopen1;
    resultopen1.create(img.size(),imggray.type());
    Mat resultopen;
    resultopen.create(img.size(),imggray.type());
    imggray.create(img.size(),img.type());
    Mat gray;
    cvtColor(img,gray,CV_RGB2GRAY);
    imggray=gray.clone();
    imwrite("/Users/sovietreborn/Desktop/gray.jpg", imggray);
    //cout<<imggray;
    for(int j= 1; j<imggray.rows-1; ++j)

    {

        const uchar *previous = imggray.ptr<const uchar>(j-1);

        const uchar *current = imggray.ptr<const uchar>(j);

        const uchar *next = imggray.ptr<const uchar>(j+1);

        uchar *output = resultopen1.ptr<uchar>(j);
        for(int k= 1; k<imggray.cols-1; k++)
            {
            Mat open33;
            open33.create(3, 3,imggray.type());
                for(int gi=0;gi<3;gi++)
                {
                    open33.at<uchar>(gi,0)=previous[k-1+gi]-1;
                    open33.at<uchar>(gi,1)=current[k-1+gi]-1;
                    open33.at<uchar>(gi,2)=next[k-1+gi]-1;
               //     cout<<previous[k-1+gi]<<current[k-1+gi]<<next[k-1+gi]<<endl;
                }
                Point maxp,minp;
                double a ,b;
                minMaxLoc(open33, &a, &b,&minp,&maxp);
              //  cout<<open33.data<<endl<<minp;
                output[k]=open33.at<uchar>(minp.x,minp.y);
            }
    }
//    imwrite("/Users/sovietreborn/Desktop/mor.jpg", resultopen1);

    for(int j= 1; j<resultopen1.rows-1; ++j)

    {

        const uchar *previous = resultopen1.ptr<const uchar>(j-1);

        const uchar *current = resultopen1.ptr<const uchar>(j);

        const uchar *next = resultopen1.ptr<const uchar>(j+1);

        uchar *output = resultopen.ptr<uchar>(j);
        for(int k= 1; k<imggray.cols-1; k++)
        {
            Mat open33;
            open33.create(3, 3,imggray.type());
            for(int gi=0;gi<3;gi++)
            {
                open33.at<uchar>(gi,0)=previous[k-1+gi]+1;
                open33.at<uchar>(gi,1)=current[k-1+gi]+1;
                open33.at<uchar>(gi,2)=next[k-1+gi]+1;
            }
            Point maxp,minp;
            double a ,b;
            minMaxLoc(open33, &a, &b,&minp,&maxp);
             // cout<<open33.data<<endl<<minp;
            output[k]=open33.at<uchar>(maxp.x,maxp.y);

        }
    }
    imwrite("/Users/sovietreborn/Desktop/moropen.jpg", resultopen);

    Mat resultclose1;
    resultclose1.create(img.size(),imggray.type());
    Mat resultclose;
    resultclose.create(img.size(),imggray.type());
    for(int j= 1; j<imggray.rows-1; ++j)

    {

        const uchar *previous = resultopen.ptr<const uchar>(j-1);

        const uchar *current = resultopen.ptr<const uchar>(j);

        const uchar *next = resultopen.ptr<const uchar>(j+1);

        uchar *output = resultclose1.ptr<uchar>(j);
        for(int k= 1; k<imggray.cols-1; k++)
        {
            Mat open33;
            open33.create(3, 3,imggray.type());
            for(int gi=0;gi<3;gi++)
            {
                open33.at<uchar>(gi,0)=previous[k-1+gi]+1;
                open33.at<uchar>(gi,1)=current[k-1+gi]+1;
                open33.at<uchar>(gi,2)=next[k-1+gi]+1;
            }
            Point maxp,minp;
            double a ,b;
            minMaxLoc(open33, &a, &b,&minp,&maxp);
            //  cout<<open33.data<<endl<<minp;
            output[k]=open33.at<uchar>(maxp.x,maxp.y);
        }
    }
            imwrite("/Users/sovietreborn/Desktop/mor.jpg", resultclose1);
    for(int j= 1; j<resultclose1.rows-1; ++j)

    {

        const uchar *previous = resultclose1.ptr<const uchar>(j-1);

        const uchar *current = resultclose1.ptr<const uchar>(j);

        const uchar *next = resultclose1.ptr<const uchar>(j+1);

        uchar *output = resultclose.ptr<uchar>(j);
        for(int k= 1; k<imggray.cols-1; k++)
        {
            Mat open33;
            open33.create(3, 3,imggray.type());
            for(int gi=0;gi<3;gi++)
            {
                open33.at<uchar>(gi,0)=previous[k-1+gi]-1;
                open33.at<uchar>(gi,1)=current[k-1+gi]-1;
                open33.at<uchar>(gi,2)=next[k-1+gi]-1;
            }
            Point maxp,minp;
            double a ,b;
            minMaxLoc(open33, &a, &b,&minp,&maxp);
            //  cout<<open33.data<<endl<<minp;
            output[k]=open33.at<uchar>(minp.x,minp.y);
        }
    }
   // imwrite("/Users/sovietreborn/Desktop/mor.jpg", resultclose);
    Mat redhat;
    redhat=gray-resultopen;
    imwrite("/Users/sovietreborn/Desktop/redhat.jpg", redhat);

}
