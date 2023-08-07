#include "Bank.hpp"

int Bank::Account::count = 0;

Bank::Account::Account() : id(count++), value(0) {}

int Bank::Account::get_id() const
{
	return (id);
}

int Bank::Account::get_value() const
{
	return (value);
}

Bank::Bank() : liquidity(0), client_accounts() {}

