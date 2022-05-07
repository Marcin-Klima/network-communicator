//
// Created by Marcin on 5/7/2022.
//

#pragma once


#include <memory>
#include <string>

class Session;

class ServerInterface
{
    using SessionPtr = std::shared_ptr<Session>;
    using MessagePtr = std::shared_ptr<std::string>;

public:
    virtual void notifyMessageSubmittalToNetworkStack(const SessionPtr& sender, MessagePtr message) = 0;

    virtual void deliverMessage(const SessionPtr& sender, MessagePtr message) = 0;

    virtual void closeSession(const SessionPtr& currentSession) = 0;
};
