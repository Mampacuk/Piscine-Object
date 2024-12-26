#ifndef BANK_HPP
# define BANK_HPP

# include <iostream>
# include <map>

struct Bank
{
	public:
		struct Account
		{
			private:
				const int _id;
				int _value;
				static int _count;
				Account();
				Account(const int value);
				Account(const Account&);
				Account &operator=(const Account&);
			public:
				~Account();
				int get_id() const;
				int get_value() const;
				friend struct Bank;
		};
		typedef std::map<int, Account*> accounts;
	private:
		int _liquidity;
		accounts _client_accounts;

		// deleted {
		Bank(const Bank&);
		Bank &operator=(const Bank&);
		// } deleted

		int charge_commission(const int inflow);
		Account &operator[](const int id);
	public:
		Bank();
		Bank(int liquidity);
		~Bank();
		int get_liquidity() const;
		const Account &operator[](const int id) const;
		const Account &create_account(const int initial_deposit = 0);
		int delete_account(const int id);
		const Account &give_loan(const int id, const int loan);
		const Account &debit_account(const int id, const int debit);
		const Account &credit_account(const int id, const int credit);
};

std::ostream &operator<<(std::ostream &stream, const Bank::Account &account);

#endif
