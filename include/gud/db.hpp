 #if !defined(GUD_DB_H_INCLUDED_)
#define GUD_DB_H_INCLUDED_

#include <string>
#include <iostream>
#include <memory>
#include <functional>
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
    public:
        /**
         * Helper class for extracting results from db
         */
        class proxy
        {
        private:
            std::shared_ptr<sql::ResultSet> result_;
            std::string field_;
        public:
            proxy(std::shared_ptr<sql::ResultSet> result, std::string const & field);

            /**
             * These are functions to automatically convert your data.
             * They will be invoked from operator[] on results
             * To use correct one, ensure left hand side of assignment is correct!
             */
            operator bool() const;
            operator double() const;
            operator std::int32_t() const;
            operator std::uint32_t() const;
            operator std::int64_t() const;
            operator std::uint64_t() const;
            operator std::string() const;
            operator std::istream*() const; //blob
        };
    private:
        std::shared_ptr<sql::ResultSet> result_;
    public:
        /**
          * Don't bother calling this manually
          * You will get back results from calling db::query
          */
        results(sql::ResultSet * result);

        /**
         * Access / extract per column data
         * make left hand side be correct datatype
         * ie: std::string name = result["name"]; //assuming name is string
         */
        proxy operator[](std::string const & field) const;

        /**
         * Number of rows
         */
        std::size_t count() const;

        /**
         * Increases internal pointer to next row
         * Returns true if successful
         */
        bool next();

        /**
         * Preferred way to iterate through results of query
         * Pass a function in, it will be called as long as `next()` is true
         */
        void each(std::function<void (db::results)> const & fn);
    };
private:
    static sql::Driver * driver_;
    static std::unique_ptr<sql::Connection> con_;

public:
    /**
     * Performs initial connection
     * this will automatically be called if app.db.connect is set to true in config
     */
    static void connect(
        std::string const & host,
        unsigned int const port,
        std::string const & database,
        std::string const & username,
        std::string const & password
    );

    /**
     * Execute a query on the database
     * Returns results
     */
    static db::results query(std::string const & query);

    /**
     * Execute a query on the database
     */
    static void execute(std::string const & query);
};

} /* /namespace gud */

#endif /* GUD_DB_H_INCLUDED_ */
