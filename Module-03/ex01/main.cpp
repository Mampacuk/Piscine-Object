#include "packageReductionDiscount.hpp"
#include "tuesdayDiscount.hpp"

#include <iostream>

#define RED "\033[31m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

#define EXPECT_EQ(x, y) \
	if (!(x == y)) \
		std::cerr << RED "FAILURE: " RESET #x RED " != " RESET #y << std::endl; \
	else \
		std::cout << GREEN "SUCCESS: " RESET #x GREEN " == " RESET #y << std::endl;

Command::order_date create_order_date(int wday = 0)
{
	Command::order_date date;
	date.tm_wday = wday;
	return (date);
}

int main()
{
	Command *tdc_monday = new TuesdayDiscountCommand(1, create_order_date(1), "Daenerys Targaryen");
	Command *tdc_tuesday = new TuesdayDiscountCommand(2, create_order_date(2), "Rhaenyra Targaryen");
	Command *prd_small = new PackageReductionDiscount(3, create_order_date(), "Alicent Hightower");
	Command *prd_big = new PackageReductionDiscount(4, create_order_date(), "Viserys I Targaryen");

	tdc_monday->add_article(Article(15, 1));
	tdc_monday->add_article(Article(30, 2));

	EXPECT_EQ(tdc_monday->get_total_price(), 75);

	tdc_tuesday->add_article(Article(15, 1));
	tdc_tuesday->add_article(Article(30, 2));

	EXPECT_EQ(tdc_tuesday->get_total_price(), 75 * 0.9f);

	prd_small->add_article(Article(15, 9));

	EXPECT_EQ(prd_small->get_total_price(), 15 * 9);

	prd_big->add_article(Article(15, 10));
	prd_big->add_article(Article(1, 1));

	EXPECT_EQ(prd_big->get_total_price(), 141);
}
