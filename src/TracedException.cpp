#include "TracedException.h"

#ifdef __linux__
#include <execinfo.h>
#elif _WIN32
#include <windows.h>
#include <dbghelp.h>
#endif

#include <sstream>

#include "ErrorCodes.h"

static const uint32_t STACK_BUFFER_SIZE = 100;
static const uint32_t STACK_MAX_FUNCTION_NAME_LEN = 100;

TracedException::TracedException(int32_t code, const std::string& message)
	: _code(code), _message(message), _stackTrace(), _embeddedException(nullptr)
{
#ifdef __linux__
	void* buffer[STACK_BUFFER_SIZE];
	int nptrs = backtrace(buffer, STACK_BUFFER_SIZE);
	char** strings = backtrace_symbols(buffer, nptrs);
	if (strings != nullptr)
	{
		std::stringstream ss;
		for (int j = 0; j < nptrs; j++)
		{
			ss << strings[j] << std::endl;
		}
		_stackTrace = ss.str();
		free(strings);
	}
#elif _WIN32
	void* stack[STACK_BUFFER_SIZE];
	HANDLE process = GetCurrentProcess();
	SymInitialize(process, NULL, TRUE);
	WORD numberOfFrames = CaptureStackBackTrace(0, STACK_BUFFER_SIZE, stack, NULL);
	SYMBOL_INFO symbol[sizeof(SYMBOL_INFO) + (STACK_MAX_FUNCTION_NAME_LEN - 1) * sizeof(TCHAR)];
	symbol->MaxNameLen = STACK_MAX_FUNCTION_NAME_LEN;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	IMAGEHLP_LINE64 line[sizeof(IMAGEHLP_LINE64)];
	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
	std::stringstream ss;
	for (int i = 0; i < numberOfFrames; i++)
	{
		DWORD displacement;
		DWORD64 address = (DWORD64)(stack[i]);
		SymFromAddr(process, address, NULL, symbol);
		if (SymGetLineFromAddr64(process, address, &displacement, line))
		{
			ss << line->FileName << "(" << symbol->Name << ") [0x" << std::hex << symbol->Address << "]" << std::endl;
		}
		else
		{
			ss << "unknown symbol at [" << symbol->Address << "]" << std::endl;
		}
	}
	_stackTrace = ss.str();
#endif
}

TracedException::TracedException(int32_t code, const std::string& message, const TracedException& ex)
	: _code(code), _message(message), _stackTrace(), _embeddedException(new TracedException(ex))
{
}

TracedException::TracedException(const std::exception& ex)
	: TracedException(UNKNOWN_ERROR, std::string(ex.what()) + " - " + typeid(ex).name())
{
}

TracedException::~TracedException() throw()
{
}

const char* TracedException::what() const throw()
{
	return _message.c_str();
}

const std::string& TracedException::GetStackTrace() const throw()
{
	return _stackTrace;
}

const std::shared_ptr<TracedException> TracedException::GetEmbeddedException() const throw()
{
	return _embeddedException;
}
