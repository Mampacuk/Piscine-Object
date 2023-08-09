#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BANK_INITIAL_DEPOSIT 1000

#define EXPECT_EQ(x, y) \
    if (!(x == y)) \
        std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
    else \
        std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

#define EXPECT_THROW(x) try \
{ \
    x; \
    std::cerr << RED "FAILURE: " RESET #x RED " didn't throw!" RESET << std::endl; \
} \
catch (const std::exception &e) \
{ \
    std::cout << GREEN "SUCCESS: caught an exception from " RESET #x GREEN ": " << e.what() << RESET << std::endl; \
}

#include "Bank.hpp"

int main()
{
    Bank bank0;
    Bank bank1(BANK_INITIAL_DEPOSIT);

    EXPECT_EQ(bank0.get_liquidity(), 0)
    EXPECT_EQ(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT)
    
    // // shouldn't compile
    // bank0 = bank1;
    // Bank bank2(bank1);

    EXPECT_THROW(Bank bank3(-10))

    EXPECT_THROW(bank0.credit_account(0, 10))

    const Bank::Account &acc0 = bank0.create_account();

    EXPECT_EQ(acc0.get_id(), 0);

    const Bank::Account &acc1 = bank1.create_account(100);
    
    EXPECT_EQ(acc1.get_id(), 1)
    EXPECT_EQ(acc1.get_value(), 95)
    EXPECT_EQ(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT + 5)

    bank0.credit_account(acc0.get_id(), 1000);

    EXPECT_EQ(acc0.get_value(), 950)
    EXPECT_EQ(bank0.get_liquidity(), 50)

    bank0.debit_account(acc0.get_id(), 50);
    EXPECT_EQ(acc0.get_value(), 900)

    EXPECT_THROW(bank0.give_loan(acc0.get_id(), 1000000))

    bank1.give_loan(acc1.get_id(), 5);
    EXPECT_EQ(acc1.get_value(), 100)
    EXPECT_EQ(bank1.get_liquidity(), BANK_INITIAL_DEPOSIT)

    bank0.delete_account(acc0.get_id());
    EXPECT_THROW(bank0.credit_account(0, 500))
}
