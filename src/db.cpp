#include <gud/db.hpp>

using namespace gud;

sql::Driver * db::driver_ = get_driver_instance();
std::unique_ptr<sql::Connection> db::con_(nullptr);

db::results::results(sql::ResultSet * result) : result_(std::unique_ptr<sql::ResultSet>(result))
{ result_->next(); }

/*
db::results::iterator db::results::begin()
{

}

db::results::const_iterator db::results::begin() const
{

}

db::results::const_iterator db::results::begin() const
{

}

db::results::iterator db::results::end()
{

}

db::results::const_iterator db::results::end() const
{

}

db::results::const_iterator db::results::cend() const
{

}

bool db::results::operator==(db::results const & rhs)
{
    return &rhs == this;
}

bool db::results::operator!=(db::results const & rhs)
{
    return &rhs != this;
}

db::results operator++(cdb::results & result)
{
    result.result_->next();
    return (*result);
}

db::results operator--(db::results & result)
{
    result.result_->previous();
    return (*result);
}
*/

namespace gud
{
    template <>
    bool db::results::get<bool>(std::string const & field)
    {
        return result_->getBoolean(field);
    }

    template <>
    int db::results::get<int>(std::string const & field)
    {
        return result_->getInt(field);
    }

    template <>
    unsigned int db::results::get<unsigned int>(std::string const & field)
    {
        return result_->getUInt(field);
    }

    template <>
    long db::results::get<long>(std::string const & field)
    {
        return result_->getInt64(field);
    }

    template <>
    unsigned long db::results::get<unsigned long>(std::string const & field)
    {
        return result_->getUInt64(field);
    }

    template <>
    std::string db::results::get<std::string>(std::string const & field)
    {
        return result_->getString(field);
    }

    template <>
    std::istream * db::results::get<std::istream *>(std::string const & field)
    {
        return result_->getBlob(field);
    }

    template <>
    std::string db::results::operator[]<std::string>(std::string const & field)
    {
        return result_->getString(field);
    }
}

void db::connect(std::string const & host, unsigned int port, std::string const & database, std::string const & username, std::string const & password)
{
    db::con_.reset(db::driver_->connect("tcp://" + host + ":" + std::to_string(port), username, password));
    db::con_->setSchema(database);
    log::info("connected to mysql server {}:{}", host, port);
}

db::results db::query(std::string const & query)
{
    std::unique_ptr<sql::Statement> stmt(db::con_->createStatement());
    return db::results(stmt->executeQuery(query));
}

void db::execute(std::string const & query)
{
    std::unique_ptr<sql::Statement> stmt(db::con_->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));

    stmt->execute(query);
}
