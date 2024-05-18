#include "napi.h"
#include <Python.h>
#include <string>
#include <boost/dll.hpp>

const char *executableFolder() {
    static std::string folderPath = boost::dll::program_location().parent_path().string();
    return folderPath.c_str();
}

double MainFunc(const char *arg) {
    PyObject *pName = NULL, *importlib = NULL, *importlib__import_module = NULL;
    PyObject *vaderSentiment = NULL, *pFunc = NULL, *pArgs = NULL, *pArgs2 = NULL;
    PyObject *pModule2 = NULL, *importlib__import_module__args = NULL, *analyser = NULL;
    PyObject *result = NULL;

    double score = 0.0;

    Py_Initialize();

    pName = PyUnicode_DecodeFSDefault("importlib");
    if (!pName) goto error;

    importlib = PyImport_Import(pName);
    Py_DECREF(pName);
    if (!importlib) goto error;

    pModule2 = PyImport_Import(PyUnicode_DecodeFSDefault("sys"));
    if (!pModule2) goto error;

    pArgs2 = PyTuple_New(2);
    if (!pArgs2) goto error;

    PyTuple_SET_ITEM(pArgs2, 0, PyLong_FromLong(0));
    PyTuple_SET_ITEM(pArgs2, 1, PyUnicode_DecodeFSDefault(executableFolder()));

    if (PyObject_CallObject(PyObject_GetAttrString(PyObject_GetAttrString(pModule2, "path"), "insert"), pArgs2) == NULL) {
        goto error;
    }

    importlib__import_module = PyObject_GetAttrString(importlib, "import_module");
    if (!importlib__import_module) goto error;

    importlib__import_module__args = PyTuple_New(1);
    if (!importlib__import_module__args) goto error;

    PyTuple_SET_ITEM(importlib__import_module__args, 0,
                     PyUnicode_DecodeFSDefault("vaderSentiment-master.vaderSentiment.vaderSentiment"));
    vaderSentiment = PyObject_CallObject(importlib__import_module, importlib__import_module__args);
    if (!vaderSentiment) goto error;

    pFunc = PyObject_GetAttrString(vaderSentiment, "SentimentIntensityAnalyzer");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        if (PyErr_Occurred()) PyErr_Print();
        fprintf(stderr, "Cannot find function \"%s\"\n", "SentimentIntensityAnalyzer");
        goto error;
    }

    pArgs = PyTuple_New(0);
    if (!pArgs) goto error;

    analyser = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    if (!analyser) goto error;

    result = PyObject_CallMethod(analyser, "polarity_scores", "(s)", arg);
    if (!result) {
        PyErr_Print();
        fprintf(stderr, "Call failed\n");
        goto error;
    }

    score = PyFloat_AsDouble(PyDict_GetItemString(result, "compound"));

    Py_DECREF(result);
    Py_DECREF(analyser);
    Py_DECREF(importlib__import_module__args);
    Py_DECREF(pFunc);
    Py_DECREF(vaderSentiment);
    Py_DECREF(importlib__import_module);
    Py_DECREF(importlib);
    Py_DECREF(pModule2);
    Py_DECREF(pArgs2);

    if (Py_FinalizeEx() < 0) {
        return 120;
    }

    return score;

error:
    Py_XDECREF(result);
    Py_XDECREF(analyser);
    Py_XDECREF(importlib__import_module__args);
    Py_XDECREF(pFunc);
    Py_XDECREF(vaderSentiment);
    Py_XDECREF(importlib__import_module);
    Py_XDECREF(importlib);
    Py_XDECREF(pModule2);
    Py_XDECREF(pArgs2);

    if (Py_FinalizeEx() < 0) {
        return 120;
    }

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

NODE_API_MODULE(hello, Init);
