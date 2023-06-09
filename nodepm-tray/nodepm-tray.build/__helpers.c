// This file contains helper functions that are automatically created from
// templates.

#include "nuitka/prelude.h"

extern PyObject *callPythonFunction(PyObject *func, PyObject *const *args, int count);


PyObject *CALL_FUNCTION_WITH_ARGS11(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 11); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 11 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 11; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 11 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 11 * sizeof(PyObject *));
            memcpy(python_pars + 11, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 11);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 11);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 11 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[11 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 11; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 11 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 11 * sizeof(PyObject *));
                memcpy(python_pars+1 + 11, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 11);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (11 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (11 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 11);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 11);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 11, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 11);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 11);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 11);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            11
        );
#else
    return _PyFunction_Vectorcall(called, args, 11, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 11);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 11);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS11(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 11);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 11);
        } else {
            result = CALL_FUNCTION_WITH_ARGS11(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 11, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 11);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS12(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 12); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 12 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 12; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 12 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 12 * sizeof(PyObject *));
            memcpy(python_pars + 12, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 12);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 12);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 12 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[12 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 12; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 12 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 12 * sizeof(PyObject *));
                memcpy(python_pars+1 + 12, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 12);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (12 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (12 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 12);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 12);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 12, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 12);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 12);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 12);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            12
        );
#else
    return _PyFunction_Vectorcall(called, args, 12, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 12);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 12);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS12(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 12);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 12);
        } else {
            result = CALL_FUNCTION_WITH_ARGS12(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 12, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 12);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS13(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 13); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 13 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 13; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 13 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 13 * sizeof(PyObject *));
            memcpy(python_pars + 13, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 13);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 13);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 13 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[13 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 13; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 13 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 13 * sizeof(PyObject *));
                memcpy(python_pars+1 + 13, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 13);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (13 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (13 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 13);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 13);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 13, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 13);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 13);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 13);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            13
        );
#else
    return _PyFunction_Vectorcall(called, args, 13, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 13);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 13);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS13(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 13);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 13);
        } else {
            result = CALL_FUNCTION_WITH_ARGS13(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 13, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 13);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS14(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 14); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 14 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 14; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 14 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 14 * sizeof(PyObject *));
            memcpy(python_pars + 14, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 14);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 14);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 14 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[14 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 14; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 14 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 14 * sizeof(PyObject *));
                memcpy(python_pars+1 + 14, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 14);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (14 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (14 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 14);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 14);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 14, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 14);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 14);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 14);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            14
        );
#else
    return _PyFunction_Vectorcall(called, args, 14, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 14);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 14);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS14(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 14);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 14);
        } else {
            result = CALL_FUNCTION_WITH_ARGS14(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 14, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 14);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS15(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 15); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 15 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 15; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 15 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 15 * sizeof(PyObject *));
            memcpy(python_pars + 15, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 15);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 15);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 15 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[15 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 15; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 15 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 15 * sizeof(PyObject *));
                memcpy(python_pars+1 + 15, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 15);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (15 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (15 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 15);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 15);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 15, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 15);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 15);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 15);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            15
        );
#else
    return _PyFunction_Vectorcall(called, args, 15, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 15);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 15);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS15(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 15);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 15);
        } else {
            result = CALL_FUNCTION_WITH_ARGS15(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 15, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 15);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS16(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 16); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 16 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 16; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 16 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 16 * sizeof(PyObject *));
            memcpy(python_pars + 16, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 16);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 16);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 16 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[16 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 16; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 16 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 16 * sizeof(PyObject *));
                memcpy(python_pars+1 + 16, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 16);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (16 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (16 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 16);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 16);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 16, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 16);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 16);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 16);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            16
        );
#else
    return _PyFunction_Vectorcall(called, args, 16, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 16);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 16);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS16(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 16);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 16);
        } else {
            result = CALL_FUNCTION_WITH_ARGS16(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 16, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 16);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS17(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 17); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 17 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 17; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 17 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 17 * sizeof(PyObject *));
            memcpy(python_pars + 17, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 17);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 17);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 17 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[17 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 17; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 17 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 17 * sizeof(PyObject *));
                memcpy(python_pars+1 + 17, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 17);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (17 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (17 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 17);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 17);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 17, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 17);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 17);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 17);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            17
        );
#else
    return _PyFunction_Vectorcall(called, args, 17, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 17);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 17);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS17(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 17);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 17);
        } else {
            result = CALL_FUNCTION_WITH_ARGS17(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 17, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 17);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS18(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 18); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 18 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 18; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 18 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 18 * sizeof(PyObject *));
            memcpy(python_pars + 18, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 18);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 18);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 18 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[18 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 18; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 18 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 18 * sizeof(PyObject *));
                memcpy(python_pars+1 + 18, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 18);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (18 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (18 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 18);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 18);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 18, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 18);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 18);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 18);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            18
        );
#else
    return _PyFunction_Vectorcall(called, args, 18, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 18);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 18);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS18(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 18);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 18);
        } else {
            result = CALL_FUNCTION_WITH_ARGS18(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 18, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 18);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS19(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 19); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 19 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 19; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 19 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 19 * sizeof(PyObject *));
            memcpy(python_pars + 19, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 19);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 19);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 19 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[19 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 19; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 19 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 19 * sizeof(PyObject *));
                memcpy(python_pars+1 + 19, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 19);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (19 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (19 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 19);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 19);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 19, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 19);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 19);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 19);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            19
        );
#else
    return _PyFunction_Vectorcall(called, args, 19, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 19);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 19);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS19(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 19);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 19);
        } else {
            result = CALL_FUNCTION_WITH_ARGS19(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 19, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 19);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS21(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 21); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 21 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 21; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 21 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 21 * sizeof(PyObject *));
            memcpy(python_pars + 21, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 21);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 21);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 21 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[21 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 21; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 21 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 21 * sizeof(PyObject *));
                memcpy(python_pars+1 + 21, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 21);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (21 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (21 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 21);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 21);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 21, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 21);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 21);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 21);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            21
        );
#else
    return _PyFunction_Vectorcall(called, args, 21, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 21);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 21);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS21(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 21);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 21);
        } else {
            result = CALL_FUNCTION_WITH_ARGS21(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 21, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 21);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}
PyObject *CALL_FUNCTION_WITH_ARGS26(PyObject *called, PyObject *const *args) {
    CHECK_OBJECT(called);
     CHECK_OBJECTS(args, 26); 

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 26 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 26; i++) {
                Py_INCREF(args[i]);
            }
            result = function->m_c_code(function,  (PyObject **)args );
        } else if (function->m_args_simple && 26 + function->m_defaults_given == function->m_args_positional_count) {
            NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

            memcpy(python_pars, args, 26 * sizeof(PyObject *));
            memcpy(python_pars + 26, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
            result = Nuitka_CallFunctionPosArgs(function, args, 26);
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        if (method->m_object == NULL) {
            PyObject *self = args[0];

            int res = PyObject_IsInstance(self, method->m_class);

            if (unlikely(res < 0)) {
                return NULL;
            } else if (unlikely(res == 0)) {
                PyErr_Format(PyExc_TypeError,
                             "unbound compiled_method %s%s must be called with %s instance as first argument (got %s "
                             "instance instead)",
                             GET_CALLABLE_NAME((PyObject *)method->m_function),
                             GET_CALLABLE_DESC((PyObject *)method->m_function), GET_CLASS_NAME(method->m_class),
                             GET_INSTANCE_CLASS_NAME((PyObject *)self));

                return NULL;
            }

            return Nuitka_CallFunctionPosArgs(method->m_function, args, 26);
        } else {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 26 + 1 == function->m_args_positional_count) {
                PyObject *python_pars[26 + 1];

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 26; i++) {
                    python_pars[i + 1] = args[i];
                    Py_INCREF(args[i]);
                }
                result = function->m_c_code(function, python_pars);
            } else if (function->m_args_simple && 26 + 1 + function->m_defaults_given == function->m_args_positional_count) {
                NUITKA_DYNAMIC_ARRAY_DECL(python_pars, PyObject *, function->m_args_positional_count);

                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 26 * sizeof(PyObject *));
                memcpy(python_pars+1 + 26, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
                result = Nuitka_CallMethodFunctionPosArgs(function, method->m_object, args, 26);
            }

            Py_LeaveRecursiveCall();

            return result;
        }
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_CFUNCTION_CALL_OPT)
    } else if (PyCFunction_CheckExact(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (unlikely(flags & METH_NOARGS)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(
                PyExc_TypeError,
                "%s() takes no arguments (26 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (unlikely(flags & METH_O)) {
            SET_CURRENT_EXCEPTION_TYPE0_FORMAT1(PyExc_TypeError,
                "%s() takes exactly one argument (26 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
        } else if (flags & METH_VARARGS) {
            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *result;

#if PYTHON_VERSION < 0x360
            PyObject *pos_args = MAKE_TUPLE(args, 26);
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }

            Py_DECREF(pos_args);
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
            PyObject *pos_args = MAKE_TUPLE(args, 26);
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            Py_DECREF(pos_args);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 0x370
                result = (*(_PyCFunctionFast)method)(self, (PyObject **)args, 26, NULL);
#else
            PyObject *pos_args = MAKE_TUPLE(args, 26);
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 26);
            Py_DECREF(pos_args);
#endif
            } else {
            PyObject *pos_args = MAKE_TUPLE(args, 26);
                result = (*method)(self, pos_args);
            Py_DECREF(pos_args);
            }
#endif


#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_UNCOMPILED_FUNCTION_CALL_OPT)
    } else if (PyFunction_Check(called)) {
#if PYTHON_VERSION < 0x3b0
        return callPythonFunction(
            called,
            args,
            26
        );
#else
    return _PyFunction_Vectorcall(called, args, 26, NULL);
#endif
#endif
#if !defined(_NUITKA_EXPERIMENTAL_DISABLE_TYPE_CREATION_OPT)
    } else if (PyType_Check(called)) {
        PyTypeObject *type = Py_TYPE(called);

        if (type->tp_call == PyType_Type.tp_call) {
            PyTypeObject *called_type = (PyTypeObject *)(called);


            if (unlikely(called_type->tp_new == NULL)) {
                PyErr_Format(PyExc_TypeError, "cannot create '%s' instances", called_type->tp_name);
                return NULL;
            }

            PyObject *pos_args = NULL;
            PyObject *obj;

            if (called_type->tp_new == PyBaseObject_Type.tp_new) {
                if (unlikely(called_type->tp_flags & Py_TPFLAGS_IS_ABSTRACT)) {
                    formatCannotInstantiateAbstractClass(called_type);
                    return NULL;
                }

                obj = called_type->tp_alloc(called_type, 0);
                CHECK_OBJECT(obj);
            } else {
                pos_args = MAKE_TUPLE(args, 26);
                obj = called_type->tp_new(called_type, pos_args, NULL);
            }

            if (likely(obj != NULL)) {
                if (!Nuitka_Type_IsSubtype(obj->ob_type, called_type)) {
                    Py_DECREF(pos_args);
                    return obj;
                }

                // Work on produced type.
                type = Py_TYPE(obj);

                if (NuitkaType_HasFeatureClass(type) && type->tp_init != NULL) {
                    if (type->tp_init == default_tp_init_wrapper) {
                        Py_XDECREF(pos_args);
                        pos_args = NULL;

                        PyObject *init_method = Nuitka_TypeLookup(type, const_str_plain___init__);

                        // Not really allowed, since we wouldn't have the default wrapper set.
                        assert(init_method != NULL);

                        bool is_compiled_function = false;
                        bool init_method_needs_release = false;

                        if (likely(init_method != NULL)) {
                            descrgetfunc func = Py_TYPE(init_method)->tp_descr_get;

                            if (func == Nuitka_Function_Type.tp_descr_get) {
                                is_compiled_function = true;
                            } else if (func != NULL) {
                                init_method = func(init_method, obj, (PyObject *)(type));
                                init_method_needs_release = true;
                            }
                        }

                        if (unlikely(init_method == NULL)) {
                            if (!ERROR_OCCURRED()) {
                                SET_CURRENT_EXCEPTION_TYPE0_VALUE0(PyExc_AttributeError, const_str_plain___init__);
                            }

                            return NULL;
                        }

                        PyObject *result;
                        if (is_compiled_function) {
                            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 26);
                        } else {
                            result = CALL_FUNCTION_WITH_ARGS26(init_method, args);
                            if (init_method_needs_release) {
                                Py_DECREF(init_method);
                            }
                        }


                        if (unlikely(result == NULL)) {
                            Py_DECREF(obj);
                            return NULL;
                        }

                        Py_DECREF(result);

                        if (unlikely(result != Py_None)) {
                            Py_DECREF(obj);

                            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
                            return NULL;
                        }
                    } else {
                        if (pos_args == NULL) {
                            pos_args = MAKE_TUPLE(args, 26);
                        }

                        if (unlikely(type->tp_init(obj, pos_args, NULL) < 0)) {
                            Py_DECREF(obj);
                            Py_XDECREF(pos_args);
                            return NULL;
                        }
                    }
                }
            }

            Py_XDECREF(pos_args);
            return obj;
        }
#endif
#if PYTHON_VERSION < 0x300
    } else if (PyClass_Check(called)) {
        PyObject *obj = PyInstance_NewRaw(called, NULL);

        PyObject *init_method = FIND_ATTRIBUTE_IN_CLASS((PyClassObject *)called, const_str_plain___init__);

        if (unlikely(init_method == NULL)) {
            if (unlikely(ERROR_OCCURRED())) {
                Py_DECREF(obj);
                return NULL;
            }

            Py_DECREF(obj);

            SET_CURRENT_EXCEPTION_TYPE0_STR(PyExc_TypeError, "this constructor takes no arguments");
            return NULL;
        }

        bool is_compiled_function = false;

        descrgetfunc descr_get = Py_TYPE(init_method)->tp_descr_get;

        if (descr_get == NULL) {
            Py_INCREF(init_method);
        } else if (descr_get == Nuitka_Function_Type.tp_descr_get) {
            is_compiled_function = true;
        } else if (descr_get != NULL) {
            PyObject *descr_method = descr_get(init_method, obj, called);

            if (unlikely(descr_method == NULL)) {
                return NULL;
            }

            init_method = descr_method;
        }

        PyObject *result;
        if (is_compiled_function) {
            result = Nuitka_CallMethodFunctionPosArgs((struct Nuitka_FunctionObject const *)init_method, obj, args, 26);
        } else {
            result = CALL_FUNCTION_WITH_ARGS26(init_method, args);
            Py_DECREF(init_method);
        }
        if (unlikely(result == NULL)) {
            return NULL;
        }

        Py_DECREF(result);

        if (unlikely(result != Py_None)) {
            SET_CURRENT_EXCEPTION_TYPE_COMPLAINT("__init__() should return None, not '%s'", result);
            return NULL;
        }

        return obj;
#endif
#if PYTHON_VERSION >= 0x380 && !defined(_NUITKA_EXPERIMENTAL_DISABLE_VECTORCALL_USAGE)
    } else if (PyType_HasFeature(Py_TYPE(called), _Py_TPFLAGS_HAVE_VECTORCALL)) {
        vectorcallfunc func = *((vectorcallfunc *)(((char *)called) + Py_TYPE(called)->tp_vectorcall_offset));

        if (likely(func != NULL)) {
            PyObject *result = func(called, args, 26, NULL);

            return Nuitka_CheckFunctionResult(called, result);
        }
#endif
    }

#if 0
    PRINT_NEW_LINE();
    PRINT_STRING("FALLBACK");
    PRINT_ITEM(called);
    PRINT_NEW_LINE();
#endif

    PyObject *pos_args = MAKE_TUPLE(args, 26);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}