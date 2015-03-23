#include <gud/db.hpp>

using namespace gud;

sql::Driver * db::driver_ = get_driver_instance();
std::unique_ptr<sql::Connection> db::con_(nullptr);

void db::connect(
    std::string const & host,
    unsigned int const port,
    std::string const & database,
    std::string const & username,
    std::string const & password
) {
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

db::results::results(sql::ResultSet * result) : result_(std::shared_ptr<sql::ResultSet>(result))
{ }

std::size_t db::results::count() const
{
    return result_->rowsCount();
}

bool db::results::next()
{
    return result_->next();
}

void db::results::each(std::function<void (db::results)> const & fn)
{ while(result_->next()) fn(*this); }

db::results::proxy::proxy(std::shared_ptr<sql::ResultSet> result, std::string const & field)
: result_(result)
, field_(field)
{}

db::results::proxy db::results::operator[](std::string const & field) const
{
    return db::results::proxy(result_, field);
}

db::results::proxy::operator bool() const
{
    return result_->getBoolean(field_);
}

db::results::proxy::operator double() const
{
    return result_->getDouble(field_);
}

db::results::proxy::operator std::int32_t() const
{
    return result_->getInt(field_);
}

db::results::proxy::operator std::uint32_t() const
{
    return result_->getUInt(field_);
}

db::results::proxy::operator std::int64_t() const
{
    return result_->getInt64(field_);
}

db::results::proxy::operator std::uint64_t() const
{
    return result_->getUInt64(field_);
}

db::results::proxy::operator std::string() const
{
    return result_->getString(field_);
}

db::results::proxy::operator std::istream*() const
{
    return result_->getBlob(field_);
}