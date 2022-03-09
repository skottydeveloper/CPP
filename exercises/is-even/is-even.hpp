class IsEven {
	private:
		int myNum;
	public:
		// constructors
		IsEven();
		IsEven(int);        
		
		// getter and setter
		void set_value(int); // assigns the argument to myNum
		int get_value();     // returns myNum 
		
		// more methods
		int sum_up(int);     // returns the sum of myNum and the argument
		bool is_even();      // checks if myNum is even
};