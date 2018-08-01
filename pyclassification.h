// PyClassification class: parts classification using external Python method
// Author: @ZC
// Date: created on 31 JuL 2018
#ifndef PYCLASSIFICATION_H
#define PYCLASSIFICATION_H

#include <iostream>
#include <QDebug>
#include <QString>

// To handle SLOTs error
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

#include "numpy/ndarrayobject.h"

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "py_cv_wrapper/pycvconverter.h"

using namespace cv;
using namespace std;

class PyClassification
{
public:
    PyClassification();

private:
    void PyInit();

};

#endif // PYCLASSIFICATION_H