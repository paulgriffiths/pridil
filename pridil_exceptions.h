/*
 *  pridil_exceptions.h
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Common exceptions for iterated prisoner's dilemma simulation.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_PRIDIL_EXCEPTIONS_H
#define PG_PRIDIL_EXCEPTIONS_H

#include <string>

namespace pridil {

//  Base exception, all custom exceptions thrown by this module
//  are derived from CmdLineException

class PridilException {
    private:
        std::string m_error_message;

    public:
        explicit PridilException(const std::string& msg =
                                 "No error message")
            : m_error_message(msg) {}
        virtual ~PridilException() {}

        const std::string& what() const { return m_error_message; }
};


//  Thrown when an unknown GameMove is encountered

class BadGameMove : public PridilException {
    public:
        explicit BadGameMove() : PridilException("Unknown game move") {};
};


//  Thrown when an unrecognized strategy is encountered

class UnknownStrategy : public PridilException {
    public:
        explicit UnknownStrategy() : PridilException("Unknown strategy") {};
};


//  Thrown when a Creature memory older than available is requested

class InvalidOpponentMemory : public PridilException {
    public:
        explicit InvalidOpponentMemory() :
            PridilException("Invalid opponent memory index") {};
};

}       //  namespace pridil

#endif      // PG_PRIDIL_EXCEPTIONS_H
