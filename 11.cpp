// Author: Baruch Sterin <baruchs@gmail.com>

#include <Python.h>

#include <thread>
#include <chrono>


// initialize and clean up python
struct initialize
{
    initialize()
    {
        Py_InitializeEx(1);
        PyEval_InitThreads();
    }

    ~initialize()
    {
        Py_Finalize();
    }
};

// acquire GIL
class ensure_gil_state
{
public:
    ensure_gil_state()
    {
        _state = PyGILState_Ensure();
    }

    ~ensure_gil_state()
    {
        PyGILState_Release(_state);
    }

private:
    PyGILState_STATE _state;
};

// allow other threads to run
class enable_threads
{
public:
    enable_threads()
    {
        _state = PyEval_SaveThread();
    }

    ~enable_threads()
    {
        PyEval_RestoreThread(_state);
    }

private:
    PyThreadState* _state;
};

char program[] =
    "import threading\n"
    "def loop():\n"
    "    for i in xrange(25):\n"
    "        import time\n"
    "        print \'.\'\n"
    "        time.sleep(0.1)\n"
    "t = threading.Thread(target=loop)\n"
    "t.start()\n"
;

// run in a new thread
void f()
{
    {
        // grab the GIL
        ensure_gil_state gil_scope;

        // run the Python code above
        PyRun_SimpleString(program);
    }

    // let the thread sleep a bit
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    // initialize Python with thread support
    initialize init;

    // start the new thread
    std::thread t(f);

    {
        // release the GIL
        enable_threads enable_threads_scope;

        // wait for the thread to terminate
        t.join();
    }

    // wait for the Python thread to terminate
    PyRun_SimpleString("t.join()");

    return 0;
}