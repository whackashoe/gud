#include <gud/db.hpp>

using namespace gud;

sql::Driver * db::driver_ = get_driver_instance();
std::unique_ptr<sql::Connection> db::con_(nullptr);

db::results::results(sql::ResultSet * result) : result_(std::shared_ptr<sql::ResultSet>(result))
{
    result_->next();
}

std::size_t db::results::count() const
{
    return result_->rowsCount();
}

db::results::proxy db::results::operator[](std::string const & field) const
{
    return db::results::proxy(result_, field);
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