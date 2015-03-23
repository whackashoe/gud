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
        class proxy
        {
        private:
            std::shared_ptr<sql::ResultSet> result_;
            std::string field_;
        public:
            proxy(std::shared_ptr<sql::ResultSet> result, std::string const & field)
             : result_(result)
             , field_(field)
             {}

            operator bool() const
            {
                return result_->getBoolean(field_);
            }

            operator double() const
            {
                return result_->getDouble(field_);
            }

            operator std::int32_t() const
            {
                return result_->getInt(field_);
            }

            operator std::uint32_t() const
            {
                return result_->getUInt(field_);
            }

            operator std::int64_t() const
            {
                return result_->getInt64(field_);
            }

            operator std::uint64_t() const
            {
                return result_->getUInt64(field_);
            }

            operator std::string() const
            {
                return result_->getString(field_);
            }

            operator std::istream *() const
            {
                return result_->getBlob(field_);
            }
        };
    private:
        std::shared_ptr<sql::ResultSet> result_;
    public:
        typedef typename std::shared_ptr<sql::ResultSet> iterator;
        typedef typename std::shared_ptr<const sql::ResultSet> const_iterator;

        results(sql::ResultSet * result);

        proxy operator[](std::string const & field) const;
        std::size_t count() const;
        bool next();
        void each(std::function<void (db::results)> const & fn);
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
