#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include <string.h>
using namespace std;

int main()
{
    Py_Initialize(); // ��ʼ�������Ǳ���ģ�������ʼ��python����Ļ���
    if (!Py_IsInitialized())
        return -1;
    // ����ģ��
    PyObject* pModule = NULL;
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    pModule = PyImport_ImportModule("myclass");
    if (!pModule) {
        printf("Cant open python file!/n");
        return -1;
    }
    // ģ����ֵ��б�
    PyObject* pDict = PyModule_GetDict(pModule);
    if (!pDict) {
        printf("Cant find dictionary./n");
        return -1;

        // ��������
        cout << "calling python program..." << endl;
        PyObject* pFunHi = PyDict_GetItemString(pDict, "hi_function");
        // ����python��������hi_class�ࣨhi_function��������hi_class�࣬����python����
        PyObject* phi_class = PyObject_CallFunction(pFunHi, NULL, NULL);
        if (!phi_class) {
            printf("Cant find phi_class class./n");
            return -1;
        }
        //����hi_class��ʵ��
        PyObject* pInstance_hi_class = PyInstance_New(phi_class, NULL, NULL);
        if (!pInstance_hi_class) {
            printf("Cant create instance./n");
            return -1;
        }
        //����hi_class��ʵ��pInstance_hi_class����ķ���
        PyObject_CallMethod(phi_class, "sayHi", "O", pInstance_hi_class);
        //�ͷ�
        Py_DECREF(phi_class);
        Py_DECREF(pInstance_hi_class);
        Py_DECREF(pFunHi);
        Py_DECREF(pModule);
        Py_Finalize(); // ���ʼ����Ӧ
        system("pause");
        return 0;
    }

#!/usr/bin/env python
# -*- coding:utf8 -*-

    class hi_class :
        def sayHi(self) :
        print 'Hi! I am a python class!'

        def hi_function() :
        py_class = hi_class()
        return py_class



#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include <string.h>
        using namespace std;

    int main()
    {
        Py_Initialize(); // ��ʼ�������Ǳ���ģ�������ʼ��python����Ļ���
        if (!Py_IsInitialized())
            return -1;
        // ����ģ��
        PyObject* pModule = NULL;
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')");
        pModule = PyImport_ImportModule("myclass");
        if (!pModule) {
            printf("Cant open python file!/n");
            return -1;
        }
        // ģ����ֵ��б�
        PyObject* pDict = PyModule_GetDict(pModule);
        if (!pDict) {
            printf("Cant find dictionary./n");
            return -1;

            // ��ʾ��������
            cout << "calling python function..." << endl;
            PyObject* pFunHi = PyDict_GetItemString(pDict, "hi_function");
            PyObject_CallFunction(pFunHi, NULL, NULL);
            Py_DECREF(pFunHi);

            //��ʾ�����
            cout << "calling python class..." << endl;
            // ��ʾ����һ��Python���󣬲�����Class�ķ���
            // ��ȡhi_class��
            PyObject* phi_class = PyDict_GetItemString(pDict, "hi_class");
            if (!phi_class) {
                printf("Cant find phi_class class./n");
                return -1;
            }
            //����hi_class��ʵ��
            PyObject* pInstance_hi_class = PyInstance_New(phi_class, NULL, NULL);
            //���python�����г�ʼ����������ô����ʵ����ʱ����Ҫ����ʼ��������Ԫ����ʽ���ݽ�ȥ���ײ���ã�PyObject* pInstance_hi_class = PyInstance_New(phi_class , PyObject*���͵�Ԫ�飨��Ҫ��C++�ﴴ��pythonԪ�飩, NULL);
            //C++�д�������ʼ��pythonԪ��ʾ���������У�
            //PyObject *pArgs3 = PyTuple_New(1);
            //PyTuple_SetItem(pArgs3, 0, Py_BuildValue("i", 3));
            if (!pInstance_hi_class) {
                printf("Cant create instance./n");
                return -1;
            }
            //����hi_class��ʵ��pInstance_hi_class����ķ���
            PyObject_CallMethod(phi_class, "sayHi", "O", pInstance_hi_class);
            //�ͷ�
            Py_DECREF(phi_class);
            Py_DECREF(pInstance_hi_class);
            Py_DECREF(pModule);
            Py_Finalize(); // ���ʼ����Ӧ
            system("pause");
            return 0;
        }


#!/usr/bin/env python
# -*- coding:utf8 -*-

        class hi_class :
            def sayHi(self) :
            print 'Hi! I am a python class!'

            def hi_function() :
            print 'Hi! I am a python function!'

