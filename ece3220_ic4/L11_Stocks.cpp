#include <iostream>
#include <cstring>
#include <cstdio>

class Stock{
	private:
		char company[30];
		int shares;
		double share_val;
		double total_val;
		void set_tot(){total_val = shares * share_val; }
		void acquire(const char * co, int n, double pr);
		void acquire(const char *co);
	public:

		void buy(int num, double price);
		void sell(int num, double price);
		void update(double price);
		void display(void);
		// Constructors
		Stock(const char *);
};


Stock::Stock(const char *co) {
  // Constructor takes only company name, sets everything else to 0.
  acquire(co, 0, 0.0);
  set_tot();
}

void Stock::acquire(const char * co, int n, double pr){
	std::strncpy(company, co, 29);
	company[29] = '\0';
	
	if(n < 0){
		std::cerr << "Number of shares can't be negative; "
				  << company << " shares set to 0.\n";
		shares = 0;
	}
	else{
		shares = n;
		std::cout << "Updated shares." << std::endl;
	}
	
	share_val = pr;
	set_tot();
}

void Stock::acquire(const char *co) {
	std::strncpy(company, co, 29);
	company[29] = '\0';
	shares = 0;
	share_val = 0.0;
	set_tot();
}

void Stock::buy(int num, double price) {

	if(num < 0){
		shares += 0;
		std::cout << "Number of shares can't be negative." << std::endl;
		std::cout << "Buying 0 shares." << std::endl;
	}
	else{
		shares += num;
		share_val += (price * num); 
		std::cout << "Bought " << num << " share(s)"
			     " of " << company << " for $"
			     << price << " per share." << std::endl;
	}

	set_tot();

}

void Stock::sell(int num, double price) {
	if(num < 0){
		shares -= 0;
		std::cout << "Number of shares can't be negative." << std::endl;
		std::cout << "Selling 0 shares." << std::endl;
	}
	else{
		shares -= num;
		share_val -= (price * num); 
		std::cout << "Sold " << num << " share(s)"
			     " of " << company << " for $"
			     << price << " per share." << std::endl;
	}


	set_tot();
}

void Stock::update(double price) {
	if(price < 0.0)
	{
		share_val = 0.0;
		std::cout << "Share price can't be negative." << std::endl;
		std::cout << "Setting share value to $0.00" << std::endl;
	}
	else
	{
		share_val = price;
		std::cout << "Setting share price to $" << price << std::endl;
	}

	set_tot();
}

void Stock::display(void) {
		// Used printf intentionally instead of cout 
		// b/c personal preference
		printf("\nCompany: %s\n", company);
		printf("Number of Shares: %d\n", shares);
		printf("Share Value: $%0.4lf\n", share_val);
		printf("Total Value: $%0.4lf\n\n", total_val);
}

int main(){
	using std::cout;
	using std::endl;

	// Use new constructor to call private method acquire()
	Stock stock1 = Stock("Nanosmart");
	stock1.display();
	stock1.buy(1, 2.99);
	stock1.display();
	stock1.sell(1, 5.99);
	stock1.update(24.00);
	stock1.display();

	Stock stock2 = Stock("Amazon");
	stock2.display();
	stock2.buy(1, 900.57);
	stock2.display();

	return 0;
}
