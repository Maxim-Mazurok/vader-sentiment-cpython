// TODO: handle errors, add Py_DECREFs

#include <Python.h>
#include <string>
#include <boost/dll.hpp>

const char* executableFolder() {
    return (new std::string(boost::dll::program_location().parent_path().string()))->c_str();
}

int main(int argc, char *argv[]) {
    (void)argc; // hack to suppress unused warning

    PyObject *pName, *importlib, *importlib__import_module, *vaderSentiment, *pFunc;
    PyObject *pArgs, *pArgs2, *pModule2, *importlib__import_module__args, *analyser, *result;

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault("importlib");

    importlib = PyImport_Import(pName);
    // Py_DECREF(pName);

    pModule2 = PyImport_Import(PyUnicode_DecodeFSDefault("sys"));

    pArgs2 = PyTuple_New(2);
    PyTuple_SET_ITEM(pArgs2, 0, PyLong_FromLong(0));
    PyTuple_SET_ITEM(pArgs2, 1, PyUnicode_DecodeFSDefault(executableFolder()));

    PyObject_CallObject(PyObject_GetAttrString(PyObject_GetAttrString(pModule2, "path"), "insert"), pArgs2);

    if (importlib != NULL) {
        importlib__import_module = PyObject_GetAttrString(importlib, "import_module");

        importlib__import_module__args = PyTuple_New(1);
        PyTuple_SET_ITEM(importlib__import_module__args, 0, PyUnicode_DecodeFSDefault("vaderSentiment-master.vaderSentiment.vaderSentiment"));
        vaderSentiment = PyObject_CallObject(importlib__import_module, importlib__import_module__args);

        pFunc = PyObject_GetAttrString(vaderSentiment, "SentimentIntensityAnalyzer");
        // /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(0);
            analyser = PyObject_CallObject(pFunc, pArgs);
            result = PyObject_CallMethod(analyser, "polarity_scores", "(s)", argv[1]);
            // Py_DECREF(pArgs);
            if (result != NULL) {
                printf("Result of call: %f\n", PyFloat_AsDouble(PyDict_GetItemString(result, "compound")));
                // Py_DECREF(result);
            } else {
                // Py_DECREF(pFunc);
                // Py_DECREF(vaderSentiment);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                return 1;
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "SentimentIntensityAnalyzer");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(vaderSentiment);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", "importlib");
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}