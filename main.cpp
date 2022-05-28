#include<bits/stdc++.h>
using namespace std;
string error="";
unordered_map<string,pair<int,char>> prio={};

struct node{
	char val;
	node* next;
	node* left;
	node* right;
};

void make_node (node*& ptr, char val, node* next, node* left, node* right){
	ptr->val=val;
	ptr->next=next;
	ptr->left=left;
	ptr->right=right;
	return;
}

void del_chain_head(node*& head){
	node* ptr=head;
	node* ptr2;
	while(ptr!=nullptr){
		if(ptr->val=='(' or ptr->val==')'){
			ptr2=ptr->right;
			delete ptr;
			ptr=ptr2;
		}
		else if(ptr->next!=nullptr){
			ptr2=ptr->next;
			delete ptr;
			ptr=ptr2;
		}
		else{
			ptr2=ptr->right;
			delete ptr;
			ptr=ptr2;
		}
	}
	return;
}

void del_chain_tail(node*& tail){
	node* ptr=tail;
	node* ptr2;
	while(ptr!=nullptr){
		if(ptr->val=='(' or ptr->val==')'){
			ptr2=ptr->left;
			delete ptr;
			ptr=ptr2;
		}
		else if(ptr->next!=nullptr){
			ptr2=ptr->next;
			delete ptr;
			ptr=ptr2;
		}
		else{
			ptr2=ptr->left;
			delete ptr;
			ptr=ptr2;
		}
	}
	return;
}

void add_segment_to_chain(node*& tail, string& str, stack<node*>& stk){
	if(str=="") return;
	node* new_tail=new node;
	make_node(new_tail,0,nullptr,tail,nullptr);
	if(str=="("){
		tail->val='(';
		tail->right=new_tail;
		stk.push(tail);
	}
	else if(str==")"){
		tail->val=')';
		tail->right=new_tail;
		if(stk.empty()){
			error="Invalid expression. Too many ')'s.";
			return;
		}
		tail->next=stk.top();
		stk.top()->next=tail;
		stk.pop();
	}
	else{
		node* ptr=tail;
		for(int i=0,len=str.size();i<len;i++){
			ptr->val=str.at(i);
			ptr->left=tail->left;
			ptr->right=new_tail;
			if(i<len-1){
				ptr->next=new node;
				ptr=ptr->next;
			}
			else ptr->next=nullptr;
		}
	}
	tail=new_tail;
	return;
}

void get_segments (string& str, vector<string>& seg, vector<string>& dict){
	if(str=="") return;
	else if(str.at(0)=='('){
		seg.push_back("(");
		str=str.substr(1);
		get_segments(str,seg,dict);
		return;
	}
	else if(str.at(0)==')'){
		seg.push_back(")");
		str=str.substr(1);
		get_segments(str,seg,dict);
		return;
	}
	else if(str.at(0)==' '){
		str=str.substr(1);
		get_segments(str,seg,dict);
		return;
	}
	else if(str.at(0)=='_'){
		if(seg.empty()){
			error="Can't start with '_'.";
			return;
		}
		if(seg.back()=="("){
			error="Can't tag '('.";
			return;
		}
		if(seg.back()==")"){
			error="Can't tag ')'.";
			return;
		}
		str=str.substr(1);
		seg.back()+="_";
		int temp=0;
		for(auto& i:str){
			if(i=='_' or i=='(' or i==')'){
				error="Invalid expression. Can't use '(', '_', or ')' in subsctripts.";
			       return;
			}
	 		if(i==' ')
				break;
			(temp)++;
			seg.back()+=i;
		}
		str=str.substr(temp);
		get_segments(str,seg,dict);
		return;
	}
	else{
		for(auto const& word:dict){
			try{
				if(str.substr(0,word.size())==word){
					seg.push_back(word);
					str=str.substr(word.size());
					get_segments(str,seg,dict);
					return;
				}

			}
			catch(std::out_of_range& e){}
		}
		seg.push_back(str.substr(0,1));
		str=str.substr(1);
		get_segments(str,seg,dict);
		return;
	}
	return;
}

void  make_chain (node*& head, string& str){
	if(str=="" or str==" ") return;
	stack<node*> stk;
	vector<string> seg;
	vector<string> dict;

	for(const auto& i:prio) dict.push_back(i.first);
	sort(dict.begin(),dict.end());
	reverse(dict.begin(),dict.end());

	get_segments(str,seg,dict);
	if(!stk.empty()) error="Invalid expression. Too many '(''s.";
	for(auto i:seg) if(error=="") add_segment_to_chain(head,i,stk);
	return;
}

string make_str (node* head){
	string str="";
	bool handle=false;
	if(head==nullptr) return str;
	node* ptr=head;
	for(int i=1;head!=nullptr;i++){
		if(head->val=='(' or head->val==')'){
			str+=head->val;
			head=head->right;
			continue;
		}
		ptr=head;
		while(ptr!=nullptr){
			if(!handle and ptr->val=='_') handle=true;
			str+=ptr->val;
			ptr=ptr->next;
		}
		if(handle){
			str+=" ";
			handle=false;
		}
		head=head->right;
	}
	return str;
}

void disp_chain_debug(node* head){
	node* ptr=head;
	while(head!=nullptr){
		if(head->val=='(' or head->val==')'){
			cout<<head->val<<endl;
			head=head->right;
			continue;
		}
		ptr=head;
		while(ptr!=nullptr){
			cout<<ptr->val;
			ptr=ptr->next;
			if(ptr!=nullptr) cout<<"->";
		}
		cout<<endl;
		head=head->right;
	}
	return;
}

void restore_para(node* head){
	node* ptr=head;
	string lookup="";
	ifstream file;
	int len=0;
	string dummy;
	file.open("./Precedence/main.txt");
	while(getline(file,dummy)) if(dummy!="") len++;
	file.close();
	vector<int> Que(len);
	cout<<Que.size();


	return;
}

bool strings_disjoint (const string& a, const string& b){
	unordered_map<char,bool> map;
	for(const auto& i:a) map[i]=true;
	for(const auto& i:b) if(map.find(i)!=map.end()) return false;
	return true;
}

bool strings_joint (const string& a, const string& b){
	unordered_map<char,bool> map;
	for(const auto& i:a) map[i]=true;
	for(const auto& i:b) if(map.find(i)==map.end()) return false;
	return true;
}

bool dir_hasfile(const string& str){
	fstream file;
	file.open(str);
	if(file.is_open()){
		file.close();
		return true;
	}
	file.close();
	return false;
}

void help(const string& tag){
	if(tag==""){
		cout<<"'_quit' returns one layer in the program.\n";
		cout<<"'show logs' shows logs.\n";
		cout<<"'show prec' shows precedence map.\n";
		cout<<"'show sig' shows signature.\n";
		cout<<"'add prec' adds an element to the precedence map.\n";
		cout<<"'del prec' deletes an element from the precedence map.\n";
		cout<<"'add axm <file>' adds an axiom file.\n";
		cout<<"'help <command>' shows more info about '<command>'.\n";
		cout<<">> ";
		return;
	}
	if(tag== " _quit"){
		cout<<"Exits current loop, deleting any progress, and returns user to the preious loop.\nAt the lowest loop, '_quit' closes the program.\n>> ";
		return;
	}
	if(tag==" show logs"){
		cout<<"Shows the chonological order of all added axioms, definitions, laws, and theorems.\n>> ";
		return;
	}
	if(tag==" show prec"){
		cout<<"The precedence map assigns strings to a <int,char> pair.\n";
		cout<<"<int>  refers to priority; the lowest values are resolved first.\n";
		cout<<"<char> refers to semantical type; precedence restores parantheses in ways particular to type.\n";
	       	cout<<"'Q' refers to a quantifier shape;\n";
		cout<<"'B/b' refers to a second/first-order binary shape;\n";
		cout<<"'U/u' refers to a second/first-order unary shape;\n";
		cout<<"'N/n' refers to a second/first-order nullary shape.\n>> ";
		return;
	}
	if(tag==" show sig"){
		cout<<"The signature consists of all free variables in the principle branch of the theory.\n";
	       	cout<<"It is only appended through adding axioms or definitions.\n>> ";
		return;
	}
	if(tag==" add prec"){
		cout<<"Adds element, in format '<str>_<int>_<char>', to './Precedence/main.txt'.\n";
		cout<<"<str> refers to a new unmapped string;\n";
		cout<<"<int> refers to the row the string '<str> <char>' is placed; a leading 0 inserts a new row;\n";
		cout<<"<char> refers to its semantic type.\n>> ";
		return;
	}
	if(tag==" del prec"){
		cout<<"Deletes element from './Precedence/main.txt'.\n";
		cout<<"Only accepts mapped string inputs.\n";
		return;
	}
	if(tag==" add axm <file>"){
		cout<<"Creates './Axioms/<file>.txt' and waits for user to input an axiom.\n";
		cout<<"Axioms are assertions of the theory-- ie. they are not followed by proof.\n>> ";
	       	return;
	}
	cout<<"'"<<tag.substr(1,tag.size())<<"'"<<" is not a recognized command.\n>> ";
	return;
}

void make_prio(){
	prio.clear();
	fstream file;
	file.open("./Precedence/main.txt",ios::in);
	string str="",line;
	bool found_space=false;
	for(int row=0;getline(file, line);row++){
		for(int i=0, len=line.size();i<len;i++){
			switch(line.at(i)){
			case ' ':
				if(!found_space) found_space=true;
				else{
					error="File Error: './Precedence/main.txt' has consecutive spaces";
					return;
				}
				break;
			default:
				switch(found_space){
				case false:
					str+=line.at(i);
					break;
				case true:
					if(str==""){
						error="File Error: './Precedence/main.txt' is missing <char>.";
						return;
					}
					string semtypes="QBbUuNn";
					if(semtypes.find_first_of(line.at(i))==string::npos){
						error="File Error: './Precedence/main.txt' has wrong semantical types.";
					       	return;
					}
					for(const auto& ch:str) if(ch=='(' or ch==')' or ch=='_'){
						error="File Error: './Precedence/main.txt' has wrong strings.";
					       	return;
					}
					if(prio.find(str)!=prio.end()){
						error="File Error: './Precedence/main.txt' has duplicate strings.";
						return;
					}
					prio[str]=make_pair(row,line.at(i));
					str="";
					found_space=false;
					break;
				}
				break;
			}
		}
	}
	file.close();
	return;
}

void Startup(){
	remove("./root/buffer.txt");
	ofstream("./root/buffer.txt")<<"";
	cout<<"\nNaive Digital Implementation of TOB.\nLoading Theory...\n";
	fstream file;

	file.open("./root/main.txt");
	if(!file.is_open()){
		error="File Error: can't find './root/main.txt'.\n Critical error, restore backup.";
		ofstream("./root/main.txt")<<"";
		return;
	}
	getline(file,error);
	file.close();

	file.open("./root/sig.txt");
	if(!file.is_open()){
		error="File Error: can't find './root/sig.txt'.\nCreated empty file.\n'make sig' to re-make signature.\n";
		ofstream("./root/sig.txt")<<"";
		return;
	}

	file.open("./root/logs.txt");
	if(!file.is_open()) {
		cout<<"File Error: can't find './root/logs.txt'.\nCreated initialized file.\n'make theory' to re-validfy files.\n";
		ofstream("./root/logs.txt")<<"Axioms: 0\nDefinitions: 0\n Laws: 0\nTheorems: 0";
	}
	file.close();
	
	file.open("./Precedence/main.txt");
	if(!file.is_open()){
		cout<<"File Error: can't find './Precedence/main.txt'.\nCreated empty file.\n'add prec' to re-build precedence.\n";
		ofstream("./Precedence/main.txt")<<"";
	}
	file.close();

	if(error=="") error="File Error: './root/main.txt' is missing first line.";
	cout<<"Theory of "<<error<<".\n";
	error="";
	make_prio();
	if(error=="") cout<<">> ";
	return;
}

void del_prec(){

	string str;
	string prio_str;
	int prio_int;
	char prio_char;
	cout<<"Delete map element '<str>'.\n$$ ";
	while(getline(cin,str) and str!="_quit"){
		if(prio.find(str)==prio.end()){
			cout<<"Invalid <str>. Precedence does not map "<<str<<".\n$$ ";
			continue;
		}
		prio_str=str;
		prio_int=prio[str].first;
		prio_char=prio[str].second;
		break;
	}
	if(str=="_quit"){
		cout<<">> ";
		return;
	}

	prio.erase(prio_str);
	ifstream file ("./Precedence/main.txt");
	vector<string> file_lines;
	while(getline(file,str)) file_lines.push_back(str);
	file.close();
	str=prio_str+" "+prio_char;
	file_lines[prio_int].erase(file_lines[prio_int].find(str),str.size());

	ofstream new_file ("./Precedence/main.txt",ofstream::trunc);
	str="";
	if(file_lines[prio_int]!="") {
		for(int i=0,len=file_lines.size();i<len;i++) new_file<<file_lines[i]<<endl;
		new_file.close();
	}
	else{
		for(int i=0;i<prio_int;i++) new_file<<file_lines[i]<<endl;
	    for(int i=prio_int+1,len=file_lines.size();i<len;i++) new_file<<file_lines[i]<<endl;
		str="(removed row)";
		new_file.close();
		make_prio();
	}
	cout<<"Deleted "<<prio_str<<"\t-->\t("<<prio_int<<", "<<prio_char<<") "<<str<<"\n>> ";
	return;
}

void add_prec(){
	string str,str1,str2;
	string prio_str;
	int prio_int;
	char prio_char;
	bool insert=false;
	vector<string> file_lines;
	ifstream file;

	cout<<"Add map element in format '<str>_<int>_<char>' (trailing 0 inserts).\n$$ ";
	while(getline(cin,str) and str!="_quit"){
		file_lines.clear();
		if(str.find_first_of('_')==string::npos){
			cout<<"Invalid expression. Missing '_'.\n$$ ";
			continue;
		}
		else if(str.find_first_of('_')==str.size()-1){
			cout<<"Invalid expression. Missing content after first '_'\n$$ ";
			continue;
		}
		str2=str;
		str=str2.substr(0,str2.find_first_of('_'));
		str1=str2.substr(str2.find_first_of('_')+1);

		if(!strings_disjoint("()_ ",str)){
			cout<<"Invalid expression. <str> is wrong.\n$$ ";
			continue;
		}
		prio_str=str;
		str=str1;
		if(prio.find(prio_str)!=prio.end()){
			cout<<"Invalid expression. <str> is already mapped.\n$$ ";
			continue;
		}

		if(str.find_first_of('_')==string::npos){
			cout<<"Invalid expression. Missing second '_'.\n$$ ";
			continue;
		}
		else if(str.find_first_of('_')==str.size()-1){
			cout<<"Invalid expression. Missing content after second '_'.\n$$ ";
			continue;
		}
		str2=str;
		str=str2.substr(0,str2.find_first_of('_'));
		str1=str2.substr(str2.find_first_of('_')+1);

		if(!strings_joint("0123456789",str) or str==""){
			cout<<"Invalid expression. <int> must be written in base-10.\n$$ ";
			continue;
		}
		prio_int=stoi(str);
		if(str=="0") insert=false;
		else if(str.at(0)=='0') insert=true;
		if(prio_int<0){
			cout<<"Invalid expression. <int> must be non-negative.\n$$ ";
			continue;
		}
		str=str1;

		for(auto&i :{"Q","B","b","U","u","N","n"}){
			if(i==str){
				prio_char=str.at(0);
				file.open("./Precedence/main.txt");
				while(getline(file,str)) file_lines.push_back(str);
				file.close();
				break;
			}
		}
		if(prio_int>file_lines.size()-1 and !insert){
			cout<<"Invalid expression. <int> exceeds range "<<file_lines.size()-1<<"\n$$ ";
			continue;
		}
		if(prio_int>file_lines.size() and insert){
			cout<<"Invalid expression. <int> exceeds range "<<file_lines.size()<<"\n$$ ";
			continue;
		}
		if(str!=""){
			cout<<"Invalid expression. <char> is not a valid semantical type.\n$$ ";
			continue;
		}

		break;
	}
	if(str=="_quit") return;
	prio[prio_str]=make_pair(prio_int,prio_char);
	if(!insert) file_lines[prio_int]+=prio_str+" "+prio_char;
	ofstream new_file("./Precedence/main.txt",ofstream::trunc);
	if(!insert) for(int i=0, len=file_lines.size();i<len;i++) new_file<<file_lines[i]<<endl;
	else{
	for(int i=0;i<prio_int;i++) new_file<<file_lines[i]<<endl;
	new_file<<prio_str+" "+prio_char<<endl;
	for(int i=prio_int,len=file_lines.size();i<len;i++) new_file<<file_lines[i]<<endl;
	}
	new_file.close();
	str="";
	if(insert) make_prio();str="(inserted row)";
	cout<<"Added "<<prio_str<<"\t-->\t("<<prio_int<<", "<<prio_char<<") "<<str<<"\n";
	cout<<">> ";
	return;
}

void add_axm(){
	string str;
	node* tail=new node;
	make_node(tail,0,nullptr,nullptr,nullptr);
	node* head=tail;
	while(getline(cin,str) and str!="_quit" and error==""){
		make_chain(tail,str);
		if(error!=""){
			cout<<error<<"\n$$ ";
			error="";
			del_chain_tail(tail);
			tail=new node;
			make_node(tail,0,nullptr,nullptr,nullptr);
			head=tail;
			continue;
		}
		break;
	}
	if(str!="_quit") cout<<"MAKE FILE PLEASE!\n";
	else delete tail;
	disp_chain_debug(head);
	restore_para(head);
	cout<<"\n>> ";
	return;
}

void add_axm_name(string input){
	if(input==""){
		cout<<"Invalid expression. Needs a nonempty name.\n$$ ";
		return;
	}
	if(!strings_disjoint("/_",input)){
		cout<<"Invalid expression. Name shouldn't contain '_', '/'.\n$$ ";
		return;
	}
	input="./Axioms/"+input+".txt";
	if(dir_hasfile(input)){
		cout<<"Invalid expression. Name already taken.\n$$ ";
		return;
	}
	cout<<"Write axiom.\n$$ ";
	add_axm();
	return;
}

void show_logs(){
	ifstream file;
	string line;
	int num_axms, num_defs, num_laws, num_thms;
	file.open("./root/logs.txt");
	getline(file,line);
	num_axms=stoi(line.substr(8));
	getline(file,line);
	num_defs=stoi(line.substr(13));
	getline(file,line);
	num_laws=stoi(line.substr(6));
	getline(file,line);
	num_thms=stoi(line.substr(10));
	file.close();

	file.open("./root/main.txt");
	getline(file,error);
	file.close();

	cout<<"Theory of "<<error<<" has\n"<<num_axms<<" axioms, "<<num_defs<<" definitions, "<<num_laws<<" laws, and "<<num_thms<<" theorems.\n>> ";
	error="";
	return;
}

void main_loop(){
	string input;
	fstream file;
	while(error=="" and getline(cin,input)){
		if(input=="help" or input.rfind("help ",0)==0) help(input.substr(4));
		else if(input=="_quit") error="Program closed.";
		else if(input=="show prec"){
			for(const auto&  i:prio) cout<<i.first<<"\t-->\t("<<i.second.first<<", "<<i.second.second<<")\n";
		       	cout<<">> ";
		}
		else if(input=="show sig"){
			file.open("./root/sig.txt");
			getline(file,input);
			cout<<"Signature: "<<input<<"\n>> ";
			file.close();
		}
		else if(input=="show logs") show_logs();
		else if(input=="add prec") add_prec();
		else if(input=="del prec") del_prec();
		else if(input.rfind("add axm ",0)==0) add_axm_name(input.substr(8));
		else cout<<"Invalid command. Type 'help' for more.\n>> ";
	}
	cout<<error;
	return;
}

int main (){
	Startup();
	main_loop();
	return 0;
}
