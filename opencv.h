#ifndef OPENCV_H
#define OPENCV_H

#include <QObject>

#include <QDebug>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <array>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <onnxruntime_cxx_api.h>
using namespace cv;
using namespace std;


class opencv : public QObject
{
    Q_OBJECT
public:
    explicit opencv(QObject *parent = nullptr);
    static int run(QString,opencv* signaler);
signals:
    void ImgResult(QString imgPath,size_t type,float result);
private:


};

static std::vector<float> loadImage(const std::string& filename, int sizeX = 128, int sizeY = 128);
static std::vector<std::string> loadLabels(const std::string& filename);

#endif // OPENCV_H
