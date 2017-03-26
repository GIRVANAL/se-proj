#include "std_lib_facilities.h"
const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = ">";
const string result = "=";

int JC(int n)         //help function: calculate n!  JieCheng
{
	if (n == 0)return 1;    //0!=1
	if (n > 0) 
	{
		int a = 1;
		for (int i = 1;i < n + 1;i++)
			a *= i;
		return a;
	}
}

class Token
{
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

class Token_stream
{
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
	void ignore(char c);      // discard characters up to and including a c
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};
Token_stream::Token_stream()
	:full(false), buffer(0)    // no Token in buffer
{
}
void Token_stream::ignore(char c)			//c preasents the kind of Token
{									
	if (full&&c == buffer.kind) 
	{
		full = false;
		return;
	}
	full = false;
	// check input
	char ch = 0;
	while (cin >> ch)
		if (ch == c)return;
}
void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}
Token Token_stream::get()
{
	if (full) {       
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case print:    // for "print"
	case quit:    // for "quit"
	case '(':
	case ')': 
	case '+': 
	case '-': 
	case '*':
	case '/':
	case '%':
	case '!':     //for n!  Jiecheng
		return Token(ch);        // let each character represent itself
	case '.':					 //a float-point-literal can start with a dot
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case'8':case '9': // numeric literal
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token(number, val);   // using const char number ='8'represents the kind of number
	}
	default:
		error("Bad token");
	}
}

Token_stream ts;        // provides get() and putback() 
double expression();    // declaration so that primary() can call expression()
double term();
double primary();

double expression()	// deal with + and -
{
	double left = term();
	Token t = ts.get();	     // get the next token from a ¡°token stream¡±
	while (true) {
		switch (t.kind) {
		case '+':	    
			left += term(); 
			t = ts.get();
			break;
		case '-':	    
			left -= term(); 
			t = ts.get();
			break;
		default:	    
			ts.putback(t);  // put the unused token back
			return left;
		}
	}
}
double term()	// deal with * ,/ and %
{
	double left = primary();
	Token t = ts.get();	// get the next Token from input
	while (true) {
		switch (t.kind) 
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
			// deal with *
		case '/': 
		{
			double d = primary();
			if (d == 0) error("division by 0");
			left /= d;
			t = ts.get();
			break;
			// deal with /
		}
		case'%': 
		{
			double d = primary();
			int i1 = int(left);
			if (i1 != left)error("left-hand operand of % not int");
			int i2 = int(d);
			if (i2 != d)error("right-hand operand of % not int");
			if (i2 == 0)error("%:divide by 0");
			left = i1 % i2;
			t = ts.get();
			break;
			//deal with %
		}
		default:
			ts.putback(t);	// put unused token back into input stream
			return left;
		}
	}
}
double primary()	// Number or ¡®(¡® Expression ¡®)¡¯ or Experssion! or '('experssion¡®)'!
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':			       // handle ¡®(¡¯expression ¡®)¡¯
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') 
		{ 
		ts.putback(t);
		error("')' expected"); 
		}
		else                //handle '('experssion¡®)'!
		{
			int n = int(d);
			t = ts.get();
			if (t.kind == '!') {
				if(d != n)error("left-hand of operand ! not int");
				if (d < 0)error("left-hand of operand ! < 0");
				return JC(n);
			}
			ts.putback(t);
			return d;
		}
	}
	case number:             
	{	double val = t.value;
		int n = int(val);
		t = ts.get();
		if (t.kind == '!')    //handle  Experssion!
		{
			if (val != n)error("left-hand of operand ! not int");
			if (val < 0)error("left-hand of operand ! < 0");
			return JC(n);
		}
		else				//handle number
		{
			ts.putback(t);
			return val;	// return the number¡¯s value
		}
	}
	case'-':
		return -primary();    //handle '-'
	case'+':
		return primary();
	default:
		error("primary expected");
	}
}
void clean_up_mess() 
{
	ts.ignore(print);  //dicard char by char until meet a print';'
}
void calculate() 
{
	while (cin) 
	try{
		cout << prompt;
		Token t = ts.get();	
		while (t.kind == print)t = ts.get();			// first discard all "prints"
		if (t.kind == quit) return;						//quit
		ts.putback(t);									// put a token back into the input stream
		cout << result << expression() << '\n' ;		// print result
	}	
	catch(exception& e){
		cerr << e.what() << endl;						//write error message 
		clean_up_mess();								
	}
}
int main()
try 
{
	calculate();

	keep_window_open();
	return 0;
}
catch (runtime_error& e)
{
		cerr << e.what() << endl;
		keep_window_open("~~");        //enter ~~ to quit
		return 1;
	}
catch (...)
{
		cerr << "exception \n";
		keep_window_open("~~");
		return 2;
}
