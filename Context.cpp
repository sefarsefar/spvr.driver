/*
* Copyright (c) 2016
*  Somebody
*/
#include "Context.h"

#include "ControlInterface.h"
#include "Logger.h"

#include <mutex>

namespace smartvr
{

namespace
{
static std::mutex S_oMutex{};
static std::unique_ptr<Context> S_pContext{};
} // unnamed namespace

Context::Context():
m_pControlInterface{std::make_unique<ControlInterface>()},
m_pLogger{std::make_unique<Logger>(m_pControlInterface.get())}
{
    m_pLogger->Log(std::string{"Context::Context()@"} + std::to_string(reinterpret_cast<int>(this)) + '\n');
}

//Context::~Context() = default;
Context::~Context()
{
    m_pLogger->Log(std::string{"Context::~Context()@"} + std::to_string(reinterpret_cast<int>(this)) + '\n');
}

Context &Context::GetInstance()
{
    static std::mutex S_oMutexLocal{};
    std::lock_guard<std::mutex> oLock{S_oMutex};
    if (!S_pContext)
    {
        S_pContext.reset(new Context{});
    }
    return *S_pContext;
}

void Context::Destroy()
{
    static std::mutex S_oMutexLocal{};
    std::lock_guard<std::mutex> oLock{S_oMutex};
    if (S_pContext)
    {
        //S_pContext.reset();
    }
}

ControlInterface &Context::GetControlInterface()
{
    return *m_pControlInterface;
}

Logger &Context::GetLogger()
{
    return *m_pLogger;
}

} // namespace smartvr