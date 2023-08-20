#include "Bank.hpp"

int Bank::Account::_count = 0;

Bank::Account::Account() : _id(_count++), _value(0) {}

Bank::Account::Account(int value) : _id(_count++), _value(value) {}

Bank::Account::~Account() {}

int Bank::Account::get_id() const
{
	return (_id);
}

int Bank::Account::get_value() const
{
	return (_value);
}

std::ostream &operator<<(std::ostream &stream, const Bank::Account &account)
{
	stream << "[" << account.get_id() << "] - [" << account.get_value() << "]";
	return (stream);
}

Bank::Bank() : _liquidity(0), _client_accounts() {}

Bank::Bank(int _liquidity) : _liquidity(_liquidity), _client_accounts()
{
	if (_liquidity < 0)
		throw std::invalid_argument("Can't start a bank with negative liquidity");
}

Bank::~Bank()
{
	for (accounts::iterator it = _client_accounts.begin(); it != _client_accounts.end(); ++it)
		delete it->second;
}

int Bank::get_liquidity() const
{
	return (_liquidity);
}

const Bank::Account &Bank::operator[](int id) const
{
	accounts::const_iterator account = _client_accounts.find(id);
	if (account == _client_accounts.end())
		throw std::out_of_range("No account with such id exists");
	return (*account->second);
}

const Bank::Account &Bank::create_account(int initial_deposit)
{
	if (initial_deposit < 0)
		throw std::invalid_argument("Initial deposit must be non-negative");
	Account *new_account = new Account(charge_commission(initial_deposit));
	_client_accounts.insert(std::make_pair(new_account->_id, new_account));
	return (*new_account);
}

int Bank::delete_account(int id)
{
	const Account &deleted = operator[](id);
	const int balance = deleted._value;
	_client_accounts.erase(deleted._id);
	delete &deleted;
	return (balance);
}

const Bank::Account &Bank::give_loan(int id, int loan)
{
	Account &loaned = operator[](id);
	if (loan > _liquidity)
		throw std::runtime_error("Not enough funds to give a loan");
	_liquidity -= loan;
	loaned._value += loan;
	return (loaned);
}

const Bank::Account &Bank::debit_account(int id, int debit)
{
	Account &debited = operator[](id);
	debited._value -= debit;
	return (debited);
}

const Bank::Account &Bank::credit_account(int id, int credit)
{
	Account &credited = operator[](id);
	credited._value += charge_commission(credit);
	return (credited);
}

int Bank::charge_commission(int inflow)
{
	const int commission = static_cast<int>(static_cast<float>(inflow) * 0.05);
	_liquidity += commission;
	return (inflow - commission);
}

Bank::Account &Bank::operator[](int id)
{
	accounts::iterator account = _client_accounts.find(id);
	if (account == _client_accounts.end())
		throw std::out_of_range("No account with such id exists");
	return (*account->second);
}
