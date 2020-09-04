#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <Python.h>
#include "myclass.h"

extern "C" {
const char* demo_doc = "this is a demo doc!";
static PyObject *DemoError;

static PyObject *
demo_use_class(PyObject *self, PyObject *args)
{
    MyClass mc;
    mc.set_x(4);
    return PyLong_FromLong(mc.get_x());
}


static PyObject *
demo_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}


static PyMethodDef DemoMethods[] = {
    {"system",  demo_system, METH_VARARGS,
     "Execute a shell command."},
    {"use_class",  demo_use_class, METH_VARARGS,
     "Use a cpp class."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef demomodule = {
    PyModuleDef_HEAD_INIT,
    "demo",   /* name of module */
    demo_doc, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    DemoMethods
};

PyMODINIT_FUNC
PyInit_demo(void)
{
    PyObject *m;

    m = PyModule_Create(&demomodule);
    if (m == NULL)
        return NULL;

    DemoError = PyErr_NewException("demo.error", NULL, NULL);
    Py_XINCREF(DemoError);
    if (PyModule_AddObject(m, "error", DemoError) < 0) {
        Py_XDECREF(DemoError);
        Py_CLEAR(DemoError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

}