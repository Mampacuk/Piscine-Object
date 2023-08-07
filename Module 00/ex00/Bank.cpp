#include "Bank.hpp"

int Bank::Account::count = 0;

Bank::Account::Account() : id(count++), value(0) {}

Bank::Account::Account(int value) : id(count++), value(value) {}

int Bank::Account::get_id() const
{
	return (id);
}

int Bank::Account::get_value() const
{
	return (value);
}

std::ostream &operator<<(std::ostream &stream, const Bank::Account &account)
{
	stream << "[" << account.get_id() << "] - [" << account.get_value() << "]";
	return (stream);
}

Bank::Bank() : liquidity(0), client_accounts() {}

Bank::Bank(int liquidity) : liquidity(liquidity), client_accounts() {}

