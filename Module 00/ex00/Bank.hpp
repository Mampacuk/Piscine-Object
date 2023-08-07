#ifndef BANK_HPP
# define BANK_HPP

# include <map>

struct Bank
{
	private:
		struct Account
		{
			private:
				int id;
				int value;
				static int count;
			public:
				Account();
				int get_id() const;
				int get_value() const;
		};

		int liquidity;
		std::map<int, Account*> client_accounts;
	public:
		Bank();
		const Account &operator[](int id) const;
};

#endif
