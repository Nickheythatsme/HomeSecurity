#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <Python.h>
#include "../networking/listener.h"

using namespace BASE_SERVICE;
using namespace NETWORKING;

extern "C" {

const char* baseservice_doc = "this is a baseservice doc!";
static PyObject *BaseserviceError;

static PyObject *
baseservice_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyObject *
baseservice_init(PyObject *self, PyObject *args)
{
    Listener *listener = new Listener();
    Py_RETURN_NONE;
}

static PyMethodDef BaseserviceMethods[] = {
    {"system",  baseservice_system, METH_VARARGS,
     "Execute a shell command."},
    {"init",  baseservice_init, METH_VARARGS,
     "Use a cpp class."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef baseservicemodule = {
    PyModuleDef_HEAD_INIT,
    "baseservice",   /* name of module */
    baseservice_doc, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    BaseserviceMethods
};

PyMODINIT_FUNC
PyInit_baseservice(void)
{
    PyObject *m;

    m = PyModule_Create(&baseservicemodule);
    if (m == NULL)
        return NULL;

    BaseserviceError = PyErr_NewException("baseservice.error", NULL, NULL);
    Py_XINCREF(BaseserviceError);
    if (PyModule_AddObject(m, "error", BaseserviceError) < 0) {
        Py_XDECREF(BaseserviceError);
        Py_CLEAR(BaseserviceError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

}