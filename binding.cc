#include "napi.h"
#include <Python.h>
#include <string>
#include <boost/dll.hpp>

const char *executableFolder() {
    static std::string folderPath = boost::dll::program_location().parent_path().string();
    return folderPath.c_str();
}

// Define a constant for the default/error value
const double DEFAULT_ERROR_VALUE = 0.0;

// Global variables to hold Python objects and initialization state
static PyObject* analyser = NULL;
static bool isPythonInitialized = false;

void InitializePython() {
    if (!isPythonInitialized) {
        Py_Initialize();

        PyObject *pName = PyUnicode_DecodeFSDefault("importlib");
        PyObject *importlib = PyImport_Import(pName);
        Py_DECREF(pName);
        if (!importlib) {
            PyErr_Print();
            fprintf(stderr, "Failed to load \"importlib\" module\n");
            return;
        }

        PyObject *pModule2 = PyImport_Import(PyUnicode_DecodeFSDefault("sys"));
        PyObject *pArgs2 = PyTuple_New(2);
        PyTuple_SET_ITEM(pArgs2, 0, PyLong_FromLong(0));
        PyTuple_SET_ITEM(pArgs2, 1, PyUnicode_DecodeFSDefault(executableFolder()));

        PyObject *pModule2_path = PyObject_GetAttrString(pModule2, "path");
        PyObject *pModule2_path_insert = PyObject_GetAttrString(pModule2_path, "insert");
        PyObject *insertResult = PyObject_CallObject(pModule2_path_insert, pArgs2);
        Py_DECREF(insertResult);
        Py_DECREF(pArgs2);
        Py_DECREF(pModule2_path_insert);
        Py_DECREF(pModule2_path);
        Py_DECREF(pModule2);

        PyObject *importlib__import_module = PyObject_GetAttrString(importlib, "import_module");
        PyObject *importlib__import_module__args = PyTuple_New(1);
        PyTuple_SET_ITEM(importlib__import_module__args, 0, PyUnicode_DecodeFSDefault("vaderSentiment-master.vaderSentiment.vaderSentiment"));

        PyObject *vaderSentiment = PyObject_CallObject(importlib__import_module, importlib__import_module__args);
        Py_DECREF(importlib__import_module__args);
        Py_DECREF(importlib__import_module);
        Py_DECREF(importlib);

        if (vaderSentiment) {
            PyObject *pFunc = PyObject_GetAttrString(vaderSentiment, "SentimentIntensityAnalyzer");
            if (pFunc && PyCallable_Check(pFunc)) {
                PyObject *pArgs = PyTuple_New(0);
                analyser = PyObject_CallObject(pFunc, pArgs);
                Py_DECREF(pArgs);
            }
            Py_XDECREF(pFunc);
            Py_DECREF(vaderSentiment);
        }

        if (!analyser) {
            PyErr_Print();
            fprintf(stderr, "Failed to create SentimentIntensityAnalyzer\n");
        }

        isPythonInitialized = true;
    }
}

double MainFunc(const char *arg) {
    if (!isPythonInitialized) {
        InitializePython();
    }

    if (!analyser) {
        return DEFAULT_ERROR_VALUE;
    }

    PyObject *result = PyObject_CallMethod(analyser, "polarity_scores", "(s)", arg);
    if (!result) {
        PyErr_Print();
        fprintf(stderr, "Call to polarity_scores failed\n");
        return DEFAULT_ERROR_VALUE;
    }

    double score = PyFloat_AsDouble(PyDict_GetItemString(result, "compound"));
    Py_DECREF(result);
    return score;
}

Napi::Value Method(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Missing argument").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Wrong argument type").ThrowAsJavaScriptException();
        return env.Null();
    }

    return Napi::Number::New(env, MainFunc(info[0].As<Napi::String>().Utf8Value().c_str()));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports = Napi::Function::New(env, Method);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
