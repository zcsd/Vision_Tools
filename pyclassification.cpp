#include "pyclassification.h"

PyClassification::PyClassification()
{
    PyInit();
}

void PyClassification::PyInit()
{
    Py_Initialize();

    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    //PyObject* pParam = NULL;
    PyObject* pNDArray = NULL;
    PyObject* pResult = NULL;
    const char* resLabel = NULL;
    float resConfidence = 0.0;

    qDebug() << "Python Initialized";

    // set system path to find correct python script
    string chdir_cmd = string("sys.path.append(\'/home/zichun/pylon_cv/python\')");
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    // import module(classification.py), it's a python script file name
    pModule = PyImport_ImportModule("classification");

    if (!pModule)
    {
        qDebug() << "get module failed!";
        //exit (0);
    }

    // import function from the module
    pFunc = PyObject_GetAttrString(pModule, "main");

    if (!pFunc)
    {
        qDebug() << "get func failed!";
        //exit (0);
    }

    cv::Mat img = cv::imread("../images/test.jpg", 1);
    cv::Mat small_img;
    cv::resize(img, small_img, Size(224, 224), 0, 0);

    // python-opencv version must be v3.1.0
    // Native-opencv version must be v3.0.0 ~ v3.4.0
    pNDArray = pycvt::fromMatToNDArray(small_img);

    // counld add more PyObj arguments before "NULL" indicator
    pResult = PyObject_CallFunctionObjArgs(pFunc, pNDArray, NULL);

    /* This method is to pass non-object para
    pParam = Py_BuildValue("(s)", "MSG from QT");
    pResult = PyEval_CallObject(pFunc, pParam);
    */

    if(pResult)
    {
        if(PyArg_Parse(pResult, "(sf)", &resLabel, &resConfidence))
        {
            qDebug() << resLabel << ":" << resConfidence;
        }
    }

    // Decrement the reference count for python object, prevent memory leak
    // PyObject must NOT be NULL.
    Py_DECREF(pModule);
    //Py_DECREF(pParam);
    Py_DECREF(pFunc);
    Py_DECREF(pNDArray);
    Py_DECREF(pResult);

    Py_Finalize();
}