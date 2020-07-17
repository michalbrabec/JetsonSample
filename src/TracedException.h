#ifndef TRACED_EXCEPTION_H_
#define TRACED_EXCEPTION_H_

#include <stdint.h>

#include <string>
#include <memory>

//https://stackoverflow.com/questions/22467604/how-can-you-use-capturestackbacktrace-to-capture-the-exception-stack-not-the-ca

/**
 * @brief Exception that gathers stack trace upon construction.
 * 
 * @note -rdynamic must be used under gcc to enable
 *       function names in stack trace.
 */
class TracedException : public std::exception
{
protected:
    /**
     * @brief Error code. 
     */
    int32_t _code;

    /**
     * @brief Error message.
     */
    std::string _message;

    /**
     * @brief Stack trace gathered during construction.
     */
    std::string _stackTrace;

    /**
     * @brief Embedded exception
     */
    const std::shared_ptr<TracedException> _embeddedException;

public:
    /**
     * @brief Construct a new TracedException object.
     * 
     * @param code Error code.
     * @param message Error message. The string is copied upon construction.
     */
    TracedException(int32_t code, const std::string &message);

    /**
     * @brief Construct a new TracedException object. Stack trace is not captured in this constructor.
     * 
     * @param code Error code.
     * @param message Error message. The string is copied upon construction.
     * @param ex Embedded traced exception.
     */
    TracedException(int32_t code, const std::string &message, const TracedException &ex);

    /**
     * @brief Construct a new Traced Exception object wrapping a standard exception.
     * 
     * @param ex Source standard exception.
     */
    explicit TracedException(const std::exception &ex);

    /**
     * @brief Destroy the Traced Exception object
     * 
     * Virtual to allow for subclassing.
     */
    virtual ~TracedException() throw();

    /**
     * @brief Returns a pointer to the error description.
     * 
     * @return const char* The memory is in posession of the Exception object. 
     *         Callers must not attempt to free the memory.
     */
    virtual const char *what() const throw() override;

    /**
     * @brief Returns a pointer to the stack trace gathered during construction.
     * 
     * @return const char* The memory is in posession of the Exception object. 
     *         Callers must not attempt to free the memory.
     */
    const std::string& GetStackTrace() const throw();

    /**
     * @brief Get the embedded exception if present.
     * 
     * @return const std::shared_ptr<std::exception> Can be null, if there is no embedded exception. 
     */
    const std::shared_ptr<TracedException> GetEmbeddedException() const throw();
};

#endif // HD_TRACED_EXCEPTION_H_