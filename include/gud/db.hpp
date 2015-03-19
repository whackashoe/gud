 #if !defined(GUD_DB_H_INCLUDED_)
#define GUD_DB_H_INCLUDED_

#include <string>
#include <iostream>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <gud/log.hpp>

namespace gud {

/**
 * mysql db connector
 */
class db
{
public:
    class results
    {
    private:
        std::unique_ptr<sql::ResultSet> result_;
    public:
        typedef typename std::unique_ptr<sql::ResultSet> iterator;
        typedef typename std::unique_ptr<const sql::ResultSet> const_iterator;

        results(sql::ResultSet * result);

        /*
        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;
        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        bool operator==(results const &);
        bool operator!=(results const &);
        results operator++();
        results operator--();
        */

        template <typename T>
        T get(std::string const & field);

        template <typename T>
        std::string operator[](std::string const & field);
    };
private:
    static sql::Driver * driver_;
    static std::unique_ptr<sql::Connection> con_;

public:
    static void connect(std::string const & host, unsigned int port, std::string const & database, std::string const & username, std::string const & password);
    static db::results query(std::string const & query);
    static void execute(std::string const & query);
};

} /* /namespace gud */

#endif /* GUD_DB_H_INCLUDED_ */
