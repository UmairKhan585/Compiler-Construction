#include<iostream>
#include<sstream>
#include<fstream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

bool s_check = false;
bool switch_check = false;
bool do_check = false;
bool if_check = false;
bool ifelse_check = false;
bool while_check = false;
bool multiline = false;
string  ASSIGNMENT = "<->";
string tilt = "~";
string res;
//for goto tac
int j = 0;

string RemoveComments(string s)
{
	int size = s.length();
	string restofprogram = "";
	bool singleline = false;
	for (int i = 0; i < size; i++)
	{
		//termination of single line
		if (singleline == true && s[i] == '\n') { singleline = false; }
		//termination of multiline Rule(>>)
		else if (multiline == true && s[i] == '>' && s[i + 1] == '>') { multiline = false, i++; }
		//continue if comment
		else if (singleline || multiline) { continue; }
		//starting of single line Rule(# Comment)
		else if (s[i] == '#') { singleline = true, i++; }
		//starting of multiline Rule(<<)
		else if (s[i] == '<' && s[i + 1] == '<') { multiline = true, i++; }
		else { restofprogram += s[i]; }
	}
	return restofprogram;
}
string removeSpace(string line) {
	string ansLine;//	     this is line ;
	int i = 0;
	if (line == "")
	{
		return "";
	}
	while (line[i] == ' ' || line[i] == '\t') {
		i++;
	}
	for (i; i < line.length(); i++)
	{
		ansLine += line[i];
	}
	return ansLine;
}
void writeFile(string f_Name, string data)
{
	fstream file;
	file.open(f_Name + ".txt", ios::out);
	if (file.is_open()) {
		file << data << endl;
	}
	else {
		cout << "File not found" << endl;
	}
	file.close();
}
vector<string> readFile(string f_Name) {
	fstream file;
	vector<string>minstructs;
	string line;
	file.open(f_Name + ".txt", ios::in);
	if (file.is_open()) {
		while (!file.eof())
		{
			getline(file, line);
			if (line.length() > 0) {

				line = RemoveComments(line);
				line = removeSpace(line);
				if (line != "") {
					minstructs.push_back(line);
					/*cout << line << endl;*/
				}

			}
		}
		return minstructs;
	}
	else {
		cout << "File not found" << endl;
	}
}
bool isDigit(char st)
{
	if (st >= 48 && st <= 57)
	{
		return true;
	}
	return false;
}
bool isDigit1(string st)
{
	for (int i = 0; i < st.length(); i++)
	{

		if (!(st[i] >= 48 && st[i] <= 57))
		{
			return false;
		}
	}
	return true;
}
bool isAlpha(char st)
{
	if (st >= 65 && st <= 90 || st >= 95 && st <= 122)
	{
		return true;
	}
	return false;
}
bool isAlpha1(string st)
{
	for (int i = 0; i < st.length(); i++)
	{

		if (!(st[i] >= 65 && st[i] <= 90 || st[i] >= 95 && st[i] <= 122))
		{
			return false;
		}
	}
	return true;
}
bool isOperator(char op)
{
	char operators[] = { '=', '<=', '>=', '+', '-', '*', '/', '%', '++', '--', '!=' };
	int size = sizeof(operators) / sizeof(operators[0]);
	for (int i = 0; i < size; i++)
	{
		if (operators[i] == op)
		{
			return true;
		}
	}
	return false;
}
bool isOperator1(string st)
{
	return ((st == "+" || st == "-" || st == "*" || st == "/" || st == "%" || st == "++" || st == "--" || st == "+=" ||
		st == "<->" || st == "-=" || st == "==" || st == ">=" || st == "<=" || st == ">" || st == "<" || st == "||" || st == "&&" || st == "=")) ? true : false;
}
bool isSpecial(string st)
{
	return ((st == "[" || st == "]" || st == "{" || st == "}" || st == "(" || st == ")" || st == "^" || st == "!" ||
		st == "@" || st == "_" || st == "$" || st == "#" || st == "`" || st == ":" || st == ";" || st == "?")) ? true : false;
}
bool isDataType(string st) {
	string dataTypes[] = { "double", "int", "long", "char", "char*", "float", "void", "bool", "string" };
	int size = sizeof(dataTypes) / sizeof(dataTypes[0]);
	for (int i = 0; i < size; i++)
	{
		if (st == dataTypes[i])
		{
			return true;
		}
	}
	return false;
}
bool isKeyWord(string st)
{

	string Keyword[13] = { "if", "else", "else_if", "switch", "for", "while", "do", "case", "return", "class", "main", "true", "false" };
	for (int i = 0; i < 13; i++)
	{
		if (st == Keyword[i] && st != "" && st != " ")
		{
			return true;
		}
	}
	return false;
}
bool isDot(string st)
{
	return st == "." ? true : false;
}
bool isIdentifier(string id)
{

	if ((isAlpha(id[0]) || id[0] == '@' || id[0] == '$' || id[0] == '^') && !isKeyWord(id))
	{
		for (int i = 1; i < id.size(); i++)
		{
			if (!(isAlpha(id[i]) || isDigit(id[i]) || id[i] == '_'))
			{
				return false;
			}
		}
		return true;
	}
	return false;

	//int abs@d;

}
class Node {
	string dataType, identifier, value, type;
	int lineNo;
	Node* reference;
public:
	Node* next;
	Node()
	{
		dataType = identifier = value = "";
		lineNo = 0;
		next = NULL;
		reference = NULL;
	}
	int getLine()
	{
		return lineNo;
	}
	string Identifier()
	{
		return identifier;
	}
	int LineNo()
	{
		return lineNo;
	}
	void setVal(string val)
	{
		value = val;
	}
	Node(string dat, string ty, string id, string val, int line, Node* ref)
	{
		dataType = dat;
		identifier = id;
		value = val;
		lineNo = line;
		reference = ref;
		type = ty;
	}
	void Print()
	{
		if (type == "Conditional")
		{
			cout << "    " << "\t\t|" << type << "\t\t|" << identifier << "\t\t|" << "  " << "\t\t|" << lineNo << "\t\t|" << reference << endl;
		}
		else if (type == "Declaration" || type == "Dec Def" || type == "Definition")
		{
			cout << dataType << "\t\t|" << type << "\t\t|" << identifier << "\t\t|" << value << "\t\t|" << lineNo << "\t\t|" << reference << endl;
		}
		else if (type == "Loop")
		{
			cout << "    " << "\t\t|" << type << "\t\t\t|" << identifier << "\t\t|" << "  " << "\t\t|" << lineNo << "\t\t|" << reference << endl;
		}

	}

};
class Token
{
	string mToken;
	bool mValid;
public:
	Token()
	{
		mToken = "";
		mValid = false;
	}
	Token(string mtok, bool valid)
	{
		mToken = mtok;
		mValid = valid;
	}
	void setVal(string value)
	{
		mToken = value;
	}
	string getToken()
	{
		return mToken;
	}
	bool isValid()
	{
		return mValid;
	}
	void setValidity(bool pvalid)
	{
		mValid = pvalid;
	}
};
vector<Token>tokenizeationInstructions(string pInst)
{
	vector<Token>tokens = {};
	string token = "";
	for (auto x : pInst)
	{
		if (x == ' ')
		{
			Token t(token, false);
			tokens.push_back(t);
			token = "";
		}
		else
		{
			token += x;
		}
	}
	if (token != "")
	{
		Token t(token, false);
		tokens.push_back(t);
		token = "";
	}
	return tokens;
}
class Lexer
{
	vector<string>mInstructions;
public:
	Lexer()
	{
		mInstructions = {};
	}
	Lexer(vector<string>pInst)
	{
		mInstructions = pInst;
	}
	bool validateToken(Token ptok)
	{

		string tok = ptok.getToken();
		if (isDataType(tok))
		{
			cout << "Datatype::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isIdentifier(tok))
		{
			cout << "Identifier::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isKeyWord(tok)) {
			cout << "Keyword::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isOperator1(tok)) {
			cout << "Operator::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isDigit1(tok)) {
			cout << "Digit::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isDot(tok))
		{
			cout << "Dot::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (tok == "~")
		{
			cout << "Tilt::" << tok << endl;
			ptok.setValidity(true);
			return true;
		}
		else if (isSpecial(tok))
		{
			cout << "Special::" << tok << endl;
			ptok.setValidity(true);
			return true;

		}
		return false;
	}
	vector<string>lexicalAnalysis()
	{
		cout << "-----------------------------------------------------------------" << endl;
		cout << "                             TOKEN VALIDATION                   |" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		bool checkLine = false;
		vector<string>resultIns;
		for (auto ins : mInstructions)
		{
			vector<Token> token = tokenizeationInstructions(ins);
			for (auto t : token)
			{
				if (validateToken(t))
				{
					checkLine = true;
				}
				else
				{
					checkLine = false;
					break;
				}
			}
			if (checkLine)
			{
				resultIns.push_back(ins);
			}
		}
		return resultIns;
	}
};
class ST
{
	Node* head;
public:
	ST()
	{
		head = NULL;
	}
	void insert(string dat, string ty, string id, string val, int line, Node* ref)
	{
		Node* node = new Node(dat, ty, id, val, line, ref);
		if (head == NULL)
		{
			head = node;
		}
		else
		{
			Node* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = node;
		}
	}
	bool search(string id)
	{

		if (head == NULL)
		{
			return false;
		}
		else
		{
			Node* temp = head;
			while (temp->next != NULL)
			{
				if (temp->Identifier() == id)
				{
					return true;
				}
				temp = temp->next;
			}
			if (temp->Identifier() == id)
			{
				return true;
			}
			return false;
		}
	}
	bool searchUpdate(string id, string val)
	{
		if (head == NULL)
		{
			return false;
		}
		else
		{
			Node* temp = head;
			while (temp->next != NULL)
			{
				if (temp->Identifier() == id)
				{
					temp->setVal(val);
					return true;
				}
				temp = temp->next;
			}
			if (temp->Identifier() == id)
			{
				temp->setVal(val);
				return true;
			}
			return false;
		}
	}
	void showTable()
	{
		cout << "-----------------------------------------------------------------" << endl;
		cout << "                             SYMBOL TABLE                       |" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "DATATYPE\tTYPE\t\t\tIDENTIFIER\tVALUE\t\tLINE.NO\t\tREFERENCE" << endl;
		Node* node = head;
		while (node != NULL)
		{
			node->Print();
			node = node->next;
		}
	}
	Node* returnNode(string id, int line)
	{
		if (head == NULL)
		{
			return 0;
		}
		else
		{
			Node* temp = head;
			while (temp->next != NULL)
			{
				if (temp->Identifier() == id || temp->LineNo() == line)
				{
					return temp;

				}
				temp = temp->next;
			}
			if (temp->Identifier() == id || temp->LineNo() == line)
			{
				return temp;
			}
			return 0;
		}
	}
};
class Semantic
{
	vector<string>mInstructions;
	ST obj;
public:
	Semantic()
	{
		mInstructions = {};
	}
	Semantic(vector<string>pInst)
	{
		mInstructions = pInst;
	}
	bool isDeclaration(string pinst)
	{
		vector<Token> t = tokenizeationInstructions(pinst);
		int DFA = 0;
		for (auto x : t)
		{
			if (DFA == 0 && isDataType(x.getToken()))
			{
				DFA = 1;
			}
			else if (DFA == 1 && isIdentifier(x.getToken()))
			{
				DFA = 2;
			}
			else if (DFA == 2)
			{
				if (isDot(x.getToken()))
				{
					DFA = 0;
					return true;
				}
				else if (x.getToken() == tilt)
				{
					DFA = 1;
				}
				else
				{
					DFA = 0;
					return false;
				}
			}
			else
				return false;
		}
		return false;
	}
	bool isDeclaration_Definition(string pinst)
	{
		vector<Token>tok = tokenizeationInstructions(pinst);
		int DFA = 0;
		string ob = "";
		for (auto x : tok)
		{
			if (DFA == 0 && isDataType(x.getToken()))
			{
				DFA = 1;
			}
			else if (DFA == 1 && isIdentifier(x.getToken()))
			{
				DFA = 2;
			}
			else if (DFA == 2 && x.getToken() == ASSIGNMENT)
			{
				DFA = 3;
			}
			else if (DFA == 3 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
			{
				ob = x.getToken();
				DFA = 4;
			}
			else if (DFA == 4)
			{
				if (isDot(x.getToken()))
				{
					DFA = 0;
					return true;
				}
				else if (x.getToken() == tilt)
				{
					DFA = 1;
				}
				else if (x.getToken() == ASSIGNMENT && !isDigit1(ob))
				{
					DFA = 3;
				}
				else
				{
					DFA = 0;
					return false;
				}
			}
			else
			{
				return false;

			}
		}
		return false;
	}
	bool isDefinition(string pInst) {
		vector<Token>mTokens = tokenizeationInstructions(pInst);
		int DFA = 0;
		string ob;
		for (auto x : mTokens) {
			if (DFA == 0 && isIdentifier(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == ASSIGNMENT) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) ||
				isDigit1(x.getToken()))) {
				ob = x.getToken();
				DFA = 3;
			}
			else if (DFA == 3) {
				if (isDot(x.getToken())) {
					DFA = 4;
					return true;
				}
				else if (x.getToken() == tilt) {
					DFA = 0;
				}
				else if (!isDigit1(ob) && (x.getToken() == ASSIGNMENT)) {
					DFA = 2;
				}
				else
					return false;
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;
	}
	bool isManupulation(string pInst) {

		vector<Token>mTokens = tokenizeationInstructions(pInst);
		int DFA = 0;
		string ob;
		for (auto x : mTokens) {
			if (DFA == 0 && isIdentifier(x.getToken())) {
				DFA = 1;
			}
			else if (DFA == 1 && x.getToken() == ASSIGNMENT) {
				DFA = 2;
			}
			else if (DFA == 2 && (isIdentifier(x.getToken()) ||
				isDigit1(x.getToken()))) {
				ob = x.getToken();
				DFA = 3;
			}
			else if (DFA == 3 && isOperator1(x.getToken())) {

				if (x.getToken() == ASSIGNMENT && isDigit1(ob))
				{
					return false;
				}
				DFA = 4;
			}
			else if (DFA == 4 && (isIdentifier(x.getToken()) ||
				isDigit1(x.getToken()))) {
				ob = x.getToken();
				DFA = 5;
			}
			else if (DFA == 5) {
				if (isDot(x.getToken())) {
					DFA = 0;
					return true;
				}
				else if (x.getToken() == tilt)
				{
					DFA = 0;
				}
				else if (isOperator1(x.getToken())) {
					if (x.getToken() == ASSIGNMENT && isDigit1(ob))
					{
						return false;
					}
					DFA = 4;
				}
				else {
					DFA = 0;
					return false;
				}
			}
			else {
				DFA = 0;
				return false;
			}
		}
		return false;

	}
	bool isConditionalStatement(string pInst)
	{
		vector<Token>mTokens = tokenizeationInstructions(pInst);
		ifelse_check = false;
		if (if_check == false)
		{
			int DFA = 0;
			for (auto x : mTokens)
			{
				//if Keyword Part
				if (DFA == 0 && x.getToken() == "if")
				{
					DFA = 1;
				} //[ Part
				else if (DFA == 1 && x.getToken() == "[")
				{
					DFA = 2;
				}
				else if (DFA == 2 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
				{
					DFA = 3;
				}
				else if (DFA == 3 && isOperator1(x.getToken()))
				{
					DFA = 4;
				}
				else if (DFA == 4 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
				{
					DFA = 5;
				}
				else if (DFA == 5 && (x.getToken() == "||" || x.getToken() == "&&"))
				{
					DFA = 2;
				}
				else if (DFA == 5 && x.getToken() == "]") //]
				{
					DFA = 6;
				}
				else if (DFA == 6 && x.getToken() == "{")//{
				{
					DFA = 7;
				}
				else if (DFA == 7 && x.getToken() == "}")
				{

					if_check = true;
					return true;
				}

			}
			return false;
		}

		else
		{
			int DFA2 = 0;
			for (auto x : mTokens)
			{
				if (DFA2 == 0 && x.getToken() == "else") //else
				{
					DFA2 = 1;
				}
				else if (DFA2 == 0 && x.getToken() == "else_if")   //else if
				{
					DFA2 = 4;
				}
				else if (DFA2 == 1 && x.getToken() == "{") //else {
				{
					DFA2 = 2;
				}
				else if (DFA2 == 2 && x.getToken() == "}") //else { }
				{
					if_check = false;
					return true;
				}
				else if (DFA2 == 4 && x.getToken() == "[")  //esle if [
				{
					DFA2 = 5;
				}
				else if (DFA2 == 5 && (isIdentifier(x.getToken()) || isDigit1(x.getToken()))) //else if [ @b
				{
					DFA2 = 6;
				}
				else if (DFA2 == 6 && isOperator1(x.getToken())) //else if [ @b >
				{
					DFA2 = 7;
				}
				else if (DFA2 == 7 && (isIdentifier(x.getToken()) || isDigit1(x.getToken()))) //else if ( @b > 2
				{
					DFA2 = 8;
				}
				else if (DFA2 == 8 && (x.getToken() == "||" || x.getToken() == "&&")) //else if [ @b > 2 || @b > 2
				{
					DFA2 = 5;
				}
				else if (DFA2 == 8 && x.getToken() == "]") //else if [ @b > 2 || @b > 2 ] 
				{
					DFA2 = 9;
				}
				else if (DFA2 == 9 && x.getToken() == "{") //else if ( @b > 2 || @b > 2 ) { 
				{
					DFA2 = 10;
				}
				else if (DFA2 == 10 && x.getToken() == "}") //else if ( @b > 2 || @b > 2 ) { }
				{

					ifelse_check = true;
					return true;
				}
			}

		}
		return false;

	}
	bool DoWhile(string pInst)
	{
		vector<Token> tokens = tokenizeationInstructions(pInst);
		int DFA = 0;
		while_check = false;
		if (do_check == false)
		{
			for (auto x : tokens)
			{
				if (DFA == 0 && x.getToken() == "do")
				{
					DFA = 1;
				}
				else if (DFA == 1 && x.getToken() == "{")
				{
					DFA = 2;
				}
				else if (DFA == 2 && x.getToken() == "}")
				{
					do_check = true;
					return true;
				}
			}
		}
		else
		{
			int DFA2 = 0;
			for (auto x : tokens)
			{
				if (DFA2 == 0 && x.getToken() == "while")
				{
					DFA2 = 1;
				}
				else if (DFA2 == 1 && x.getToken() == "[")
				{
					DFA2 = 2;
				}
				else if (DFA2 == 2 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
				{
					DFA2 = 3;
				}
				else if (DFA2 == 3 && isOperator1(x.getToken()))
				{
					DFA2 = 4;
				}
				else if (DFA2 == 4 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
				{
					DFA2 = 5;
				}
				else if (DFA2 == 5 && (x.getToken() == "||" || x.getToken() == "&&"))
				{
					DFA2 = 2;
				}
				else if (DFA2 == 5 && x.getToken() == "]")
				{
					while_check = true;
					do_check = false;
					return true;
				}
			}
		}
		return false;
	}
	bool while_(string pInst)
	{
		vector<Token> tokens = tokenizeationInstructions(pInst);
		int DFA2 = 0;
		for (auto x : tokens)
		{
			if (DFA2 == 0 && x.getToken() == "while")
			{
				DFA2 = 1;
			}
			else if (DFA2 == 1 && x.getToken() == "[")
			{
				DFA2 = 2;
			}
			else if (DFA2 == 2 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
			{
				DFA2 = 3;
			}
			else if (DFA2 == 3 && isOperator1(x.getToken()))
			{
				DFA2 = 4;
			}
			else if (DFA2 == 4 && (isIdentifier(x.getToken()) || isDigit1(x.getToken())))
			{
				DFA2 = 5;
			}
			else if (DFA2 == 5 && (x.getToken() == "||" || x.getToken() == "&&"))
			{
				DFA2 = 2;
			}
			else if (DFA2 == 5 && x.getToken() == "]")
			{
				DFA2 = 6;
			}
			else if (DFA2 == 6 && x.getToken() == "{")
			{
				DFA2 = 7;
			}
			else if (DFA2 == 7 && x.getToken() == "}")
			{
				return true;
			}

		}
		return false;

	}
	bool switch_(string pInst)
	{

		vector<Token> tokens = tokenizeationInstructions(pInst);
		int DFA = 0;
		if (switch_check == false)
		{
			for (auto x : tokens)
			{
				if (DFA == 0 && x.getToken() == "switch")
				{
					DFA = 1;
				}
				else if (DFA == 1 && x.getToken() == "[")
				{
					DFA = 2;
				}
				else if (DFA == 2 && isIdentifier(x.getToken()))
				{
					DFA = 3;
				}
				else if (DFA == 3 && x.getToken() == "]")
				{
					DFA = 4;
				}
				else if (DFA == 4 && x.getToken() == "{")
				{
					switch_check = true;
					return true;
				}

			}
		}
		else
		{

			int DFA2 = 0;
			for (auto x : tokens)
			{
				if (DFA2 == 0 && x.getToken() == "case")
				{
					DFA2 = 1;
				}
				else if (DFA2 == 1 && (isDigit1(x.getToken()) || isIdentifier(x.getToken())))
				{
					DFA2 = 2;
				}
				else if (DFA2 == 2 && x.getToken() == ":")
				{

					DFA2 = 3;
				}
				else if (DFA2 == 3 && isDot(x.getToken()))
				{
					DFA2 = 4;
				}
				else if (DFA2 == 4 && x.getToken() == "break")
				{
					DFA2 = 5;
				}
				else if (DFA2 == 5 && isDot(x.getToken()))
				{

					return true;
				}

			}


		}

		return false;

	}
	bool bracket(string pInst)
	{
		vector<Token> tokens = tokenizeationInstructions(pInst);
		for (auto x : tokens)
		{
			if (x.getToken() == "}")
			{
				return true;
			}
		}
		return false;
	}
	void SemanticAnalysis()
	{
		cout << "-----------------------------------------------------------------" << endl;
		cout << "|                            SEMANTIC ANALYSIS                  |" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		for (auto ins : mInstructions)
		{

			if (isDeclaration(ins))
			{
				cout << "Verifired ::" << ins << endl;
			}
			else if (isDefinition(ins))
			{
				cout << "Verifired ::" << ins << endl;

			}
			else if (isDeclaration_Definition(ins))
			{
				cout << "Verifired ::" << ins << endl;
			}
			else if (isManupulation(ins))
			{
				cout << "Verifired ::" << ins << endl;
			}
			else if (isConditionalStatement(ins))
			{
				cout << "Verifired ::" << ins << endl;

			}
			else if (DoWhile(ins))
			{
				cout << "Verified ::" << ins << endl;
			}
			else if (while_(ins))
			{
				cout << "Verified ::" << ins << endl;
			}
			else if (switch_(ins))
			{
				s_check = true;
				res = res + ins + "\n";
			}
			else if (s_check == true && bracket(ins))
			{
				res = res + ins + "\n";
				cout << "Verified ::" << res << endl;
			}
			else
			{
				cout << "Wrong Input ::" << ins << endl;
			}
		}
	}
	ST SymbolTable(vector<string>pInst)
	{
		int line = 1;
		int ifline;
		if_check = false;
		for (auto x : pInst)
		{

			if (isDeclaration(x))
			{
				vector<Token>token = tokenizeationInstructions(x);
				string dt = token[0].getToken();
				for (int i = 0; i < token.size(); i++)
				{
					int a, b;
					if (i % 2 != 0)
					{
						if (!obj.search(token[i].getToken()))
						{
							obj.insert(dt, "Declaration", token[i].getToken(), "", line, NULL);
						}
					}
				}
			}
			else if (isDeclaration_Definition(x))
			{
				vector<Token>token = tokenizeationInstructions(x);
				string dt = token[0].getToken();
				string id, val;
				for (int i = 0; i < token.size(); i++)
				{
					if (i % 2 != 0)
					{
						if (isIdentifier(token[i].getToken()))
						{
							id = token[i].getToken();
						}
						else if (isDigit1(token[i].getToken()))
						{
							val = token[i].getToken();
						}
					}
					if (token[i].getToken() == tilt || isDot(token[i].getToken()))
					{
						if (!obj.search(id))
						{
							obj.insert(dt, "Dec Def", id, val, line, NULL);
						}
					}
				}
			}
			else if (isDefinition(x))
			{
				vector<Token>token = tokenizeationInstructions(x);
				string id, val;
				for (int i = 0; i < token.size(); i++)
				{
					if (i % 2 == 0)
					{
						if (isIdentifier(token[i].getToken()))
						{
							id = token[i].getToken();
						}
						else if (isDigit1(token[i].getToken()))
						{
							val = token[i].getToken();
						}
					}
					else
					{
						if (token[i].getToken() == tilt || isDot(token[i].getToken()))
						{
							Node* L = obj.returnNode(id, 0);
							if (L != NULL)
							{
								obj.insert("", "Definition", L->Identifier(), val, line, L);
							}
							else if (L == NULL)
							{
								cout << "Identifier is not declared::" << id << endl;
							}

						}
					}
				}
			}
			else if (isConditionalStatement(x))
			{

				vector<Token>token = tokenizeationInstructions(x);
				if (token[0].getToken() == "if")
				{
					obj.insert("", "Conditional", token[0].getToken(), "", line, NULL);
					ifline = line;
				}
				else
				{
					Node* L = obj.returnNode("", ifline);
					if (L != NULL)
					{
						obj.insert("", "Conditional", token[0].getToken(), "", line, L);
					}
					else if (L == NULL)
					{
						cout << "No related if found !!" << endl;
					}
				}


			}
			else if (DoWhile(x))
			{

				vector<Token>token = tokenizeationInstructions(x);
				if (token[0].getToken() == "do")
				{
					obj.insert("", "Loop", token[0].getToken(), "", line, NULL);
					ifline = line;
				}
				else
				{
					Node* L = obj.returnNode("", ifline);
					if (L != NULL)
					{
						obj.insert("", "Loop", token[0].getToken(), "", line, L);
					}
					else if (L == NULL)
					{
						cout << "No related if found !!" << endl;
					}
				}

			}
			else if (while_(x))
			{


				vector<Token>token = tokenizeationInstructions(x);
				if (token[0].getToken() == "while")
				{
					obj.insert("", "Loop", token[0].getToken(), "", line, NULL);
				}


			}


			line++;
		}
		return obj;
	}

};
class TAC {
	Token operand1;
	Token operand2;
	Token op;
	Token op1;
	TAC* reference;
	Token Register;
	Semantic obj;
public:
	TAC() { reference = NULL; }
	TAC(Token oper1, Token oper2, Token opP, TAC* ref)
	{
		operand1 = oper1;
		operand2 = oper2;
		op = opP;
		reference = ref;
	}
	TAC(Token oper1, Token oper2, Token opP, TAC* ref, Token reg)
	{
		operand1 = oper1;
		operand2 = oper2;
		op = opP;
		reference = ref;
		Register = reg;
	}
	TAC(Token oper1, Token oper2, Token opP, Token opp1, TAC* ref)
	{
		operand1 = oper1;
		operand2 = oper2;
		op = opP;
		op1 = opp1;
		reference = ref;
	}
	void display_assignment_tac()
	{
		cout << Register.getToken() << "\t\t" << operand1.getToken() << "\t\t" << op.getToken() << "\t\t" << operand2.getToken() << "\t\t" << reference;

	}
	void display_tac()
	{
		cout << operand1.getToken() << "\t\t" << op.getToken() << "\t\t" << operand2.getToken() << "\t\t" << op1.getToken() << "\t\t" << reference;
	}

	int Precedence(string tok)
	{
		if (tok == "+" || tok == "-")
		{
			return 1;
		}
		else if (tok == "*" || tok == "/")
		{
			return 2;
		}
		else if (tok == "^")
		{
			return 3;
		}
		else if (tok == "=")
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	string infixToPostfix(string infx)
	{
		stack<string> st;
		vector<Token>mtokens = tokenizeationInstructions(infx);
		string postfix = "";
		for (auto x : mtokens)
		{
			if (isIdentifier(x.getToken()))
			{
				postfix += x.getToken() + " ";
			}
			else if (x.getToken() == "(")
			{
				st.push(x.getToken());
			}
			else if (isOperator1(x.getToken()))
			{
				while (!st.empty() && Precedence(st.top()) >= Precedence(x.getToken()))
				{
					postfix += st.top() + " ";
					st.pop();
				}
				st.push(x.getToken());
			}
			else if (x.getToken() == ")")
			{
				while (!st.empty() && st.top() != "(")
				{
					postfix += st.top() + " ";
					st.pop();
				}
				st.pop();
			}

		}
		return postfix;
	}
	Token retToken(string s, string s1, string op)
	{
		Token res;
		string x = s + op + s1;
		res.setVal(x);
		return res;
	}
	string adding_bracket(string str)
	{
		string concat, res;
		for (int i = 7; i < str.size(); i++)
		{
			concat += str[i];
		}
		res = "( " + concat + " )";

		cout << "After Adding Brackets :: " << res << endl;
		return res;
	}
	//for Assignment / manipulation:
	vector<TAC>ASSIGNMENT_TAC(string original_str)
	{
		string Assignment_Part;
		for (int i = 0; i < 2; i++)
		{
			Assignment_Part += original_str[i];
		}
		cout << "Assingment Part :: " << Assignment_Part << endl;
		string BRACKETS, POSTFIX;
		BRACKETS = adding_bracket(original_str);
		POSTFIX = infixToPostfix(BRACKETS);
		cout << "PostFix Equation :: " << POSTFIX << endl;
		vector<Token> tokens = tokenizeationInstructions(POSTFIX);
		Token operand1 = tokens[0];
		Token operand2 = tokens[1];
		Token oper = tokens[2];
		stack<Token> st1;
		stack<TAC*> st2;
		vector <TAC> list;
		int i = -1;
		Token res;
		string s;
		for (auto x : tokens)
		{

			if (isIdentifier(x.getToken()))
			{
				st1.push(x);

			}
			else if (isOperator1(x.getToken()))
			{
				i++;
				Token a, b, c;
				a = st1.top();
				st1.pop();

				b = st1.top();
				st1.pop();

				s = "t" + to_string(i);
				Token t(s, true);

				if (st2.empty())
				{
					TAC ob(b, a, x, NULL, t);
					st2.push(&ob);
					list.push_back(ob);
				}
				else
				{
					TAC* ref = st2.top();
					st2.pop();
					Token ab;
					TAC ob1(b, a, x, ref, t);
					st2.push(&ob1);

					list.push_back(ob1);
				}
				res = retToken(b.getToken(), a.getToken(), x.getToken());
				cout << t.getToken() << " :: " << res.getToken() << endl;
				st1.push(res);

			}

		}
		cout << Assignment_Part << "  :: " << s;
		return list;
	}
	//for Conditional statement :
	vector<TAC>Conditional_Jump_TAC(string jump_str)
	{
		vector<Token> tokens = tokenizeationInstructions(jump_str);
		vector<TAC>test;
		stack<TAC*>reff;
		int i = 0;
		Token temp;
		Token temp1;
		stack<Token>Tstack;
		string str;
		string str1;
		string str2;
		j++;

		if (tokens[0].getToken() == "if")
		{
		c:
			while (tokens[i].getToken() != "{")
			{

				str += tokens[i].getToken();
				if (isIdentifier(tokens[i].getToken()) || isDigit1(tokens[i].getToken()))  //Incase of Identifiers
				{

					if (!Tstack.empty())
					{

						Token x;
						x = Tstack.top();
						Tstack.pop();

						if (tokens[i + 1].getToken() == "||" || tokens[i + 1].getToken() == "&&")   /* @a > @b || @c > @d*/
						{

							temp1 = tokens[i + 1];
							if (!reff.empty())
							{

								TAC* z = reff.top();
								reff.pop();
								TAC obj(x, tokens[i], temp, temp1, z);
								test.push_back(obj);
								reff.push(&obj);

							}
							else
							{

								TAC obj(x, tokens[i], temp, temp1, NULL);
								test.push_back(obj);
								reff.push(&obj);
							}
						}
						else
						{

							if (temp1.getToken() == "||" || temp1.getToken() == "&&")
							{

								TAC* z = reff.top();
								reff.pop();
								TAC obj(x, tokens[i], temp, z);
								test.push_back(obj);
								reff.push(&obj);

							}
							else
							{

								TAC obj(x, tokens[i], temp, temp1, NULL);
								test.push_back(obj);
							}

						}
					}
					else
					{
						Tstack.push(tokens[i]);
					}
				}
				else if (isOperator1(tokens[i].getToken()))
				{
					temp = tokens[i];

				}
				i++;
			}

			i++;
			while (tokens[i].getToken() != "}")
			{

				str1 += tokens[i].getToken();  //if Body { }
				i++;
			}
			i++;
			if (tokens[0].getToken() == "if" || tokens[0].getToken() == "else_if")
			{
				cout << str << " goto " << j << endl;
				cout << j << " : " << str1 << endl;
			}
		}
		else if (tokens[0].getToken() == "else_if")
		{

			goto c;

		}
		return test;
	}
	void TACS(vector<string>ins)
	{
		vector<TAC>list;
		vector<TAC>list1;

		for (auto x : ins)
		{

			if (obj.isManupulation(x))
			{
				cout << "\t\tTHREE ADDRESS CODE FOR MANIPULATION / ASSIGNMENT" << endl;
				list = ASSIGNMENT_TAC(x);
				cout << endl;
				cout << "REGISTERS \t|OPERAND1 \t|OPERATOR  \t|OPERAND2  \t|REFRENCES" << endl;
				for (auto x : list)
				{
					x.display_assignment_tac();
					cout << endl;
				}
				cout << endl;
			}
			else if (obj.isConditionalStatement(x))
			{
				//if_check=false;
				list = Conditional_Jump_TAC(x);
				cout << "\t\t          THREE ADDRESS CODE" << endl;
				cout << "OPERAND1 \tOPERATOR  \tOPERAND2  \tOPERATOR  \tREFRENCES" << endl;
				for (auto x : list)
				{
					x.display_tac();
					cout << endl;
				}
				cout << endl;

			}
		}
	}
};
vector<TAC> EXTRACTPOSTFIX(string postfix)
{
	vector<Token> tokens = tokenizeationInstructions(postfix);
	Token operand1 = tokens[0];
	Token operand2 = tokens[1];
	Token oper = tokens[2];
	stack<Token> st1;
	stack<TAC*> st2;
	vector <TAC> list;

	for (auto x : tokens)
	{


		if (isIdentifier(x.getToken()))
		{
			st1.push(x);

		}
		else if (isOperator1(x.getToken()))
		{
			Token a, b, c;
			Token res;
			a = st1.top();
			st1.pop();

			b = st1.top();
			st1.pop();
			if (st2.empty())
			{
				TAC ob(b, a, x, NULL);
				st2.push(&ob);
				list.push_back(ob);
			}
			else
			{
				TAC* ref = st2.top();
				st2.pop();
				Token ab;
				TAC ob1(b, a, x, ref);
				st2.push(&ob1);

				list.push_back(ob1);
			}
			/*res = retToken(b.getToken(), a.getToken(), x.getToken());*/
			st1.push(res);

		}
	}
	return list;
}
int main()
{
	vector<string>file;
	/*writeFile("Project", "Test File");*/
	file = readFile("Project");
	Lexer lex(file);
	vector<string>lexresult;
	lexresult = lex.lexicalAnalysis();
	Semantic sem(lexresult);
	sem.SemanticAnalysis();
	ST b = sem.SymbolTable(file);
	b.showTable();

	/*string BRACKETS;
	BRACKETS = adding_bracket("c = a * b + c + d + e");
	string POSTFIX = infixToPostfix(BRACKETS);
	cout<<"PostFix Equation :: "<< POSTFIX;
	cout << endl;*/

	TAC obj;
	obj.TACS(file);

	/*vector<TAC>listTAC = EXTRACTPOSTFIX(POSTFIX);
	cout << "\t\tTHREE ADDRESS CODE" << endl;
	cout << " Operand1 \t Operator \t Operand2  \t reference" << endl;
	for (auto x : listTAC)
	{
	x.displayTAC();
	cout << endl;
	}*/



	/*vector<TAC>listTAC = ASSIGNMENT_TAC("c = a * b + c + d + e");
	cout << endl;
	cout << "\t\t          THREE ADDRESS CODE" << endl;
	cout << "REGISTERS \tOPERAND1 \tOPERATOR  \tOPERAND2  \tREFRENCES" << endl;
	for (auto x : listTAC)
	{
	x.displayTAC();
	cout << endl;
	}*/

	system("pause");
	return 0;
}



