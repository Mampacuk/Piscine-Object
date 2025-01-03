#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <ctime>
# include <string>
# include <vector>

class Article
{
	public:
		Article() : _price(0.f), _quantity(0) {}
		Article(const float price, const unsigned int quantity) : _price(price), _quantity(quantity) {}
		Article(const Article &other) : _price(other._price), _quantity(other._quantity) {}
		Article &operator=(const Article&) { return (*this); }
		~Article() {}
		float get_price() const { return (_price); }
		unsigned int get_quantity() const { return (_quantity); }
	private:
		const float _price;
		const unsigned int _quantity;
};

// the Open-Closed Principle (OCP) states that a class should be opened for extension,
// but closed for modification. this means that when new functionality is requested for Command,
// e.g. a new way to compute price, the Command class itself will not need to be changed---the changes
// are delegated to new classes such as TuedsayDiscountCommand that inherit from Command.
// as a result, Command's source code is not changed, and its functionality can be extended by
// definition of new classes that differently implement the abstract method calculate_fair_price().
class Command
{
	public:
		typedef struct tm order_date;
		typedef std::vector<Article> article_vector;

		Command() : id(), date(), client(), articles() {}
		Command(const Command &other) : id(other.id), date(other.date), client(other.client), articles(other.articles) {}
		Command &operator=(const Command &other) { id = other.id; date = other.date; client = other.client; articles = other.articles; return (*this); }
		virtual ~Command() {}

		Command(const unsigned int id, const order_date &date, const std::string &client) : id(id), date(date), client(client), articles() {}

		unsigned int get_order_id() const { return (id); }
		const order_date &get_order_date() const { return (date); }
		const std::string &get_client_name() const { return (client); }
		const article_vector &get_articles() const { return (articles); }
		void add_article(const Article &article) { articles.push_back(article); }
		virtual float get_total_price() const = 0;
	protected:
		// return fair sum of all products (price times quantity)
		float calculate_fair_price() const
		{
			float total_price = 0.f;
			for (article_vector::const_iterator it = articles.begin(); it != articles.end(); it++)
				total_price += it->get_price() * it->get_quantity();
			return (total_price);
		}
	private:
		unsigned int id;
		order_date date;
		std::string client;
		article_vector articles;
};

#endif
