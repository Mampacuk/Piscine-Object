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
				int id;
				int value;
				static int count;
				Account();
				Account(int value);
			public:
				int get_id() const;
				int get_value() const;
				friend class Bank;
		};
	private:
		int liquidity;
		std::map<int, Account*> client_accounts;
		Bank(const Bank&);
		Bank &operator=(const Bank&);
	public:
		Bank();
		Bank(int liquidity);
		~Bank();
		const Account &operator[](int id) const;
		
};

std::ostream &operator<<(std::ostream &stream, const Bank::Account &account);

#endif
