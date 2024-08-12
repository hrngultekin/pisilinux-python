/*
* Copyright (c) 2005, TUBITAK/UEKAE
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version. Please read the COPYING file.
*/

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <X11/Xlib.h>


PyDoc_STRVAR(isOn__doc__,
"isOn()\n"
"\n"
"method checked if CapsLock is on\n");

PyObject*
capslock_isOn(PyObject *self, PyObject *args)
{
    int capsLocked;
    unsigned int lmask;
    Window dummy1, dummy2;
    int dummy3, dummy4, dummy5, dummy6;
    Display *display;

    display = XOpenDisplay(0);
    XQueryPointer(display, DefaultRootWindow(display),
           &dummy1, &dummy2, &dummy3, &dummy4, &dummy5, &dummy6,
           &lmask);
    capsLocked = lmask & LockMask;
    XCloseDisplay(display);

    if (capsLocked)
    {
        Py_INCREF(Py_True);
        return Py_True;
    }

    Py_INCREF(Py_False);
    return Py_False;
}

static PyMethodDef capslock_methods[] = {
    // {"isOn",  (PyCFunction)capslock_isOn,  METH_NOARGS,  isOn__doc__},
    {"isOn",  capslock_isOn,  METH_NOARGS,  isOn__doc__},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef capslock_module = {
    PyModuleDef_HEAD_INIT,
    "capslock",   /* name of module */
    "pardus capslock module", /* module doc*/
    -1,
    capslock_methods
};

PyMODINIT_FUNC
PyInit_capslock(void)
{
    return PyModuleDef_Init(&capslock_module);
}

