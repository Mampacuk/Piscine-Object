#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BANK_INITIAL_DEPOSIT 1000

#include "Bank.hpp"

template <class T>
static void expect_eq(T a, T b)
{
    if (!(a == b))
        std::cerr << RED "FAILURE: " << a << " != " << b << RESET << std::endl;
    else
        std::cout << GREEN "SUCCESS: " << a << " == " << b << RESET << std::endl;
}

#define EXPECT_THROW(x) try \
{ \
    x; \
    std::cerr << RED "FAILURE: no throw happened!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
    std::cout << GREEN "SUCCESS: caught an exception: " << e.what() << RESET << std::endl; \
}

int main()
{
    Bank bank0;
    Bank bank1(BANK_INITIAL_DEPOSIT);

    expect_eq(bank0.get_liquidity(), 0);
    expect_eq(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT);
    
    // // shouldn't compile
    // bank0 = bank1;
    // Bank bank2(bank1);

    EXPECT_THROW(Bank bank3(-10))

    EXPECT_THROW(bank0.credit_account(0, 10))

    const Bank::Account &acc0 = bank0.create_account();

    expect_eq(acc0.get_id(), 0);

    const Bank::Account &acc1 = bank1.create_account(100);
    
    expect_eq(acc1.get_id(), 1);
    expect_eq(acc1.get_value(), 95);
    expect_eq(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT + 5);

    bank0.credit_account(acc0.get_id(), 1000);

    expect_eq(acc0.get_value(), 950);
    expect_eq(bank0.get_liquidity(), 50);

    bank0.debit_account(acc0.get_id(), 50);
    expect_eq(acc0.get_value(), 900);

    EXPECT_THROW(bank0.give_loan(acc0.get_id(), 1000000))

    bank1.give_loan(acc1.get_id(), 5);
    expect_eq(acc1.get_value(), 100);
    expect_eq(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT);

    bank0.delete_account(acc0.get_id());
    EXPECT_THROW(bank0.credit_account(0, 500))
}
