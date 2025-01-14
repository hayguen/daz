#include <Python.h>

#if defined(__SSE__)
#include <xmmintrin.h>
#endif

static PyObject* set_daz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  mxcsr |= (1<<6);
  _mm_setcsr(mxcsr);
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* set_ftz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  mxcsr |= (1<<15);
  _mm_setcsr(mxcsr);
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* get_daz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  if((1<<6)&mxcsr)
    Py_RETURN_TRUE;
#endif
  Py_RETURN_FALSE;
}

static PyObject* get_ftz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  if((1<<15)&mxcsr)
    Py_RETURN_TRUE;
#endif
  Py_RETURN_FALSE;
}

static PyObject* unset_daz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  mxcsr &= ~(1<<6);
  _mm_setcsr(mxcsr);
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* unset_ftz(void)
{
#if defined(__SSE__)
  unsigned int mxcsr = _mm_getcsr();
  mxcsr &= ~(1<<15);
  _mm_setcsr(mxcsr);
#endif
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef methods[] = {
  {"set_ftz", (PyCFunction)set_ftz, METH_NOARGS, 0},
  {"set_daz", (PyCFunction)set_daz, METH_NOARGS, 0},
  {"get_ftz", (PyCFunction)get_ftz, METH_NOARGS, 0},
  {"get_daz", (PyCFunction)get_daz, METH_NOARGS, 0},
  {"unset_ftz", (PyCFunction)unset_ftz, METH_NOARGS, 0},
  {"unset_daz", (PyCFunction)unset_daz, METH_NOARGS, 0},
  {NULL, NULL, 0, NULL}
};


#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef module = {
  PyModuleDef_HEAD_INIT,
  "_core",
  NULL,
  -1,
  methods,
  NULL,
  NULL,
  NULL
};

PyMODINIT_FUNC PyInit__core(void)
{
  return PyModule_Create(&module);
}
#else
PyMODINIT_FUNC init_core(void)
{
  Py_InitModule("_core", methods);
}
#endif
